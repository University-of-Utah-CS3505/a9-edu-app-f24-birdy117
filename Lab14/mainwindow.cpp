#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * @brief MainWindow::MainWindow - Constructs the main window for this GUI and sets up the needed
 * variables for Box2D operations.
 * @param parent - The parent or something, I dunno.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , world(new b2World(b2Vec2(0.0f, -10.0f)))
    , bounceGoing(false)
    , timer(new QTimer(this))
    , launchForce(250, 500)
    , colors({Qt::red, Qt::yellow, Qt::blue})
{
    ui->setupUi(this);

    for (int i = 0; i < 15; ++i)
    {
        b2Body* body = makeBody();
        confetti[body] = new QRectF(300, 700, 10, 10);
    }

    connect(ui->goButton, &QPushButton::clicked, this, &MainWindow::goPushed);
    // WATCH - Not super sure what's going on with this timer anymore, but it's working so don't
        // touch it.
    connect(timer, SIGNAL(timeout()), this, SLOT(updateWorld()));

}


/**
 * @brief MainWindow::~MainWindow - A destructor for MainWindow.
 * WATCH - Dunno if we were actually supposed to delete the timer and world.
 */
MainWindow::~MainWindow()
{
    delete ui;
    delete world;
    delete timer;
}


/**
 * @brief MainWindow::updateWorld - Steps the Box2D body forward in time, then displays this change
 * to the slider.
 */
void MainWindow::updateWorld()
{
    // Instruct the world to perform a single step of simulation.
    // It is generally best to keep the time step and iterations fixed.
    float32 timeStep = 1.0f / 25.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    world->Step(timeStep, velocityIterations, positionIterations);

    b2Vec2 newPosition;

    // Move all the confetti, then update.
    for (auto it = confetti.cbegin(); it != confetti.cend(); ++it)
    {
        newPosition = it.key()->GetPosition();
        // it.value()->moveTo(300 + newPosition.x, 25 * (newPosition.y));
        it.value()->moveTo(100 + newPosition.x * 100, 690 - (newPosition.y * 50));
    }

    update();
}


/**
 * @brief MainWindow::goPushed - When the go button is pushed, the program will either start the
 * bouncing or stop the bouncing, depending on whether it was bouncing before.
 *
 * When the bounce is stopped and started again, the slider begins at the top, or "reset" position.
 */
void MainWindow::goPushed()
{
    if (bounceGoing)
    {
        bounceGoing = false;
        timer->stop();

        for (auto it = confetti.cbegin(); it != confetti.cend(); ++it)
        {
            world->DestroyBody(it.key());
        }

        for (int i = 0; i < 5; ++i)
        {
            b2Body* body = makeBody();
            confetti[body] = new QRectF(300, 10, 10, 10);
        }

    }
    else
    {
        bounceGoing = true;
        timer->start(100);

    }
}


void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QRandomGenerator rng = QRandomGenerator(4);

    for (auto it = confetti.cbegin(); it != confetti.cend(); ++it)
    {
        // painter.translate(it.value()->center());
        // painter.rotate(qRadiansToDegrees(it.key()->GetAngle()));
        // painter.translate(-(it.value()->center()));

        int rand = rng.generate();
        int absoluteValue = qFabs(rand);
        painter.fillRect(*it.value(), colors[absoluteValue % colors.size()]);
    }
}


b2Body* MainWindow::makeBody()
{
    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);
    bodyDef.angle = 0;
    b2Body* body = world->CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    // Override the default friction.
    fixtureDef.friction = 0.3f;

    // Change restitution
    fixtureDef.restitution = 0.1;

    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);

    // Apply the launch force to the body.
    // Note: applying force here instead of in updateWorld means that the force will only be
    // applied once, at the body's creation and the beginning of the world. If we apply this
    // force in updateWorld, it applies force every time the world Steps, so it just keeps
    // pushing the body. That is not what we want. We want it to launch one time, right at the
    // beginning. So YES, keep it here, or I will send you to the ghouls.

    QRandomGenerator rng = QRandomGenerator(4);

    // body->ApplyForce(launchForce, body->GetWorldPoint(b2Vec2(1, 1)), true);
    // body->ApplyForce(launchForce, b2Vec2(1, 1), true);
    // body->SetLinearVelocity(b2Vec2(-1, 15));
    // body->ApplyAngularImpulse(rng.generate() % 100, true);
    body->ApplyForce(b2Vec2(350 + rng.generate() % 50, 750 + rng.generate() % 50), body->GetWorldPoint(b2Vec2(1, 1)), true);

    return body;
}


/*
 * DOING
 * Process notes.
 *
 * Now we gotta add more confetti pieces.
 * This is gonna get interesting.
 *
 * What all will we need?
 * We'll need a list of bodies.
 * And we'll need to store the colors for each rectangle, and maybe their angles?
 * Actually, not the angle, we can just use body->GetAngle()
 * I think mostly we just need all the bodies and the rectangles, we can think of colors in a
 * little bit.
 * Would a map work for that, do you think?
 * Let's try making a map that stores bodies and the rectangles they control.
 * Body should be the key, I think, and rectangle should be the value.
 * We might have to pass a new variable into moveTheRectangle, one that lets us determine which
 * rectangle is being moved.
 * For now, we're just gonna keep the one rectangle, and implement the map with it. Once we've got
 * that straightened out, we'll add more confetti.
 * Or should I make a confetti class? It could store the body and the rectangle and everything.
 * And then we could just have a list of confetti in MainWindow. We wouldn't have to do any of the
 * actual world steps or shit in here, that's all handled by the confetti class.
 * Actually, wait, maybe we couldn't do that. We would have to step all the confetti at the same
 * time, which means we'd still have to step in mainwindow.
 * Let's see. All the bodies get added to the world, then we step the world forward, and that's
 * what we use.
 * So yeah, actually, let's just try a map and see how that goes.
 *
 * Okay! Map is implemented and it like, works. Groovy.
 * I'm gonna make a makeBody method really quick.
 *
 * Got a bunch of confetti in here. It's launching in a weird way; I'm wondering if it's because
 * we're starting them all at the same spot. Might implement some randomness in their construction.
 */
