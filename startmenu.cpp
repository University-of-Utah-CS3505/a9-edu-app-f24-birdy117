#include "startmenu.h"
#include "foolsmate.h"
#include "ui_startmenu.h"
#include <QMessageBox>
#include <QTimer>

StartMenu::StartMenu(ChessBoard *chessBoard, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartMenu)
    , chessBoard(chessBoard)
    , settings("Placeholder", "AppName")
    , world(new b2World(b2Vec2(0.0f, -10.0f)))
    , bounceGoing(false)
    , timer(new QTimer(this))
    , launchForce(250, 500)
    , colors({Qt::red, Qt::yellow, Qt::blue})
{
    fool = new Foolsmate(chessBoard);
    ui->setupUi(this);
    level = 1;
    connect(ui->level1Button, &QPushButton::clicked, this, &StartMenu::level1Start);
    connect(ui->level2Button, &QPushButton::clicked, this, &StartMenu::level2Start);
    connect(ui->level3Button, &QPushButton::clicked, this, &StartMenu::level3Start);
    connect(ui->finalQuizButton, &QPushButton::clicked, this, &StartMenu::finalQuizButton);
    connect(ui->QuitButton, &QPushButton::clicked, this, &StartMenu::quitButtonClicked);
    connect(ui->startButton, &QPushButton::clicked, this, &StartMenu::startClicked);

    connect(ui->q1option1, &QPushButton::clicked, this, &StartMenu::q1option1Clicked);
    connect(ui->q1option2, &QPushButton::clicked, this, &StartMenu::q1option2Clicked);
    connect(ui->q1option3, &QPushButton::clicked, this, &StartMenu::q1option3Clicked);
    connect(ui->q1option4, &QPushButton::clicked, this, &StartMenu::q1option4Clicked);

    connect(ui->tryAgain, &QPushButton::clicked, this, &StartMenu::tryAgainClicked);

    connect(ui->NextLevelButton, &QPushButton::clicked, this, [this]() {
        if (level == 1) {
            level2Start();
            level = 2;
        } else if (level == 2) {
            level = 3;
            level3Start();
        }
    });

    //Box2D Make Body
    for (int i = 0; i < 15; ++i)
    {
        b2Body* body = makeBody();
        confetti[body] = new QRectF(300, 700, 10, 10);
    }
    //Box2D Connection
    connect(ui->level1Button, &QPushButton::clicked, this, &StartMenu::goPushed);


    ui->firstQuestion->hide();
    ui->q1option1->hide();
    ui->q1option2->hide();
    ui->q1option3->hide();
    ui->q1option4->hide();
    ui->tryAgain->hide();
    ui->inputFoolsMate->hide();
    ui->firstQuestion->setReadOnly(true);
    currentQuestion = 1;

    buttons = {ui->level1Button, ui->level2Button, ui->level3Button};

    loadButtonStates();

    QVBoxLayout *layout = new QVBoxLayout;
    ui->chessBoardContainer->setLayout(layout);
    layout->addWidget(chessBoard);
    hideNonStartingWidgets();
}

StartMenu::~StartMenu()
{
    saveButtonStates();
    delete ui;
    delete chessBoard;
    delete fool;
    delete world;
    delete timer;
}

void StartMenu::updateWorld()
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

void StartMenu::goPushed()
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

void StartMenu::paintEvent(QPaintEvent*)
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

b2Body* StartMenu::makeBody()
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

const QString StartMenu::foolMateSetup[8][8] = {
    {":/Images/RookW.png",
     ":/Images/KnightW.png",
     ":/Images/BishopW.png",
     ":/Images/KingW.png",
     ":/Images/QueenW.png",
     ":/Images/BishopW.png",
     ":/Images/KnightW.png",
     ":/Images/RookW.png"},
    {":/Images/PawnW.png",
     ":/Images/PawnW.png",
     ":/Images/PawnW.png",
     ":/Images/PawnW.png",
     ":/Images/PawnW.png",
     ":/Images/PawnW.png",
     ":/Images/PawnW.png",
     ":/Images/PawnW.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {":/Images/PawnB.png",
     ":/Images/PawnB.png",
     ":/Images/PawnB.png",
     ":/Images/PawnB.png",
     ":/Images/PawnB.png",
     ":/Images/PawnB.png",
     ":/Images/PawnB.png",
     ":/Images/PawnB.png"},
    {":/Images/RookB.png",
     ":/Images/KnightB.png",
     ":/Images/BishopB.png",
     ":/Images/KingB.png",
     ":/Images/QueenB.png",
     ":/Images/BishopB.png",
     ":/Images/KnightB.png",
     ":/Images/RookB.png"},
    };

const QString StartMenu::backRankMateSetup[8][8] = {
    {"", "", "", "", "", "", ":/Images/KingB.png", ""},
    {"", "", "", "", ":/Images/PawnB.png", ":/Images/PawnB.png", ":/Images/PawnB.png", ":/Images/PawnB.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", ":/Images/BishopB.png", "", "", ""},
    {"", "", "", "", "", "", ":/Images/PawnW.png", ":/Images/PawnW.png"},
    {":Images/RookW.png", "", ":Images/BishopW.png", "", "", "", ":/Images/KingW.png", ""}
};

const QString StartMenu::backRankMateMove1[8][8] = {
    {"", "", "", "", "", "", ":/Images/KingB.png", ""},
    {"", "", "", "", ":/Images/PawnB.png", ":/Images/PawnB.png", ":/Images/PawnB.png", ":/Images/PawnB.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", ":Images/BishopW.png", "", "", ""},
    {"", "", "", "", "", "", ":/Images/PawnW.png", ":/Images/PawnW.png"},
    {":Images/RookW.png", "", "", "", "", "", ":/Images/KingW.png", ""}
};

const QString StartMenu::backRankMateMove2[8][8] = {
    {"", "", "", "", "", ":/Images/KingB.png", "", ""},
    {"", "", "", "", ":/Images/PawnB.png", ":/Images/PawnB.png", ":/Images/PawnB.png", ":/Images/PawnB.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", ":Images/BishopW.png", "", "", ""},
    {"", "", "", "", "", "", ":/Images/PawnW.png", ":/Images/PawnW.png"},
    {":Images/RookW.png", "", "", "", "", "", ":/Images/KingW.png", ""}
};

const QString StartMenu::backRankMateMove3[8][8] = {
    {":Images/RookW.png", "", "", "", "", ":/Images/KingB.png", "", ""},
    {"", "", "", "", ":/Images/PawnB.png", ":/Images/PawnB.png", ":/Images/PawnB.png", ":/Images/PawnB.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", ":Images/BishopW.png", "", "", ""},
    {"", "", "", "", "", "", ":/Images/PawnW.png", ":/Images/PawnW.png"},
    {"", "", "", "", "", "", ":/Images/KingW.png", ""}
};

const QString StartMenu::kingQueenMateSetup[8][8] = {
    {"", "", "", "", "", "", "", ":/Images/KingW.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", ":/Images/KingB.png", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", ":/Images/QueenB.png", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""}
};

const QString StartMenu::kingQueenMateMove1[8][8] = {
    {"", "", "", "", "", "", "", ":/Images/KingW.png"},
    {"", "", "", "", "", ":/Images/KingB.png", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", ":/Images/QueenB.png", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""}
};

const QString StartMenu::kingQueenMateMove2[8][8] = {
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", ":/Images/KingB.png", "", ":/Images/KingW.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", ":/Images/QueenB.png", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""}
};

const QString StartMenu::kingQueenCheckmateG7[8][8] = {
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", ":/Images/KingB.png", ":/Images/QueenB.png", ":/Images/KingW.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""}
};

const QString StartMenu::kingQueenCheckmateH3[8][8] = {
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", ":/Images/KingB.png", "", ":/Images/KingW.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ":/Images/QueenB.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""}
};

const QString StartMenu::kingQueenCheckmateH4[8][8] = {
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", ":/Images/KingB.png", "", ":/Images/KingW.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ":/Images/QueenB.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""}
};

const QString StartMenu::kingQueenCheckmateH5[8][8] = {
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", ":/Images/KingB.png", "", ":/Images/KingW.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ":/Images/QueenB.png"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""}
};

void StartMenu::hideNonStartingWidgets()
{
    ui->chessBoardContainer->hide();
    ui->QuitButton->hide();
    ui->NextLevelButton->hide();
    ui->CheckmateLabel->hide();

    ui->foolsMateText->hide();
    ui->BackRankText->hide();
    ui->KingQueenText->hide();
    ui->inputBox->hide();
    ui->inputBoxLabel->hide();
    ui->inputBackRank->hide();

    ui->directionsLabel->hide();
    ui->CorrectLabel->hide();

    ui->startButton->hide();
    ui->startButton->setEnabled(false);
}

void StartMenu::level1Start() {
    hideStartingScreen();
    ui->foolsMateText->show();
    ui->startButton->show();
    ui->startButton->setEnabled(true);
    ui->startButton->raise();
    chessBoard->setupPieces(foolMateSetup);

    addBorderReversed();

    ui->Title->setText("Level 1: The Fool's Mate");
    ui->inputFoolsMate->show();

    connect(fool, &Foolsmate::updateStatusLabel, this, &StartMenu::updateLabel);
    connect(ui->inputFoolsMate, &QLineEdit::returnPressed, this, &StartMenu::checkInputFirstMove);

    fool->moveFirstWhitePawn();
    fool->firstMove();
    connect(fool, &Foolsmate::updateStatusLabel, this, &StartMenu::updateLabel);
    connect(this, &StartMenu::correctInputReceived, fool, &Foolsmate::moveSecondWhitePawn);
}

void StartMenu::level2Start()
{
    quitButtonClicked();
    hideStartingScreen();
    ui->BackRankText->show();
    ui->startButton->show();
    ui->startButton->setEnabled(true);
    ui->startButton->raise();
    ui->inputBackRank->show();
    ui->directionsLabel->setText("Follow the instructions on the screen");

    connect(ui->inputBackRank, &QLineEdit::returnPressed, this, &StartMenu::checkBackRankAnswer);

    chessBoard->setupPieces(backRankMateSetup);
    ui->Title->setText("Level 2: The Back Rank Mate");
    ui->TeamCreditsLabel->hide();
    for (int i = 0; i < ui->NamesLayout->count(); ++i) {
        QWidget *widget = ui->NamesLayout->itemAt(i)->widget();
        if (widget) {
            widget->hide();
        }
    }    
    addBorder();
    backRankMateFirst();
}

void StartMenu::level3Start()
{
    ui->NextLevelButton->hide();
    quitButtonClicked();
    hideStartingScreen();
    ui->KingQueenText->show();
    ui->startButton->show();
    ui->startButton->setEnabled(true);
    ui->startButton->raise();

    connect(ui->inputBox, &QLineEdit::returnPressed, this, &StartMenu::checkQueenKingCheckmateAnswer);

    chessBoard->setupPieces(kingQueenMateSetup);
    ui->Title->setText("Level 3: The King and Queen Mate");
    ui->directionsLabel->setText("Move the Black King to corner the White King.");
    ui->TeamCreditsLabel->hide();
    for (int i = 0; i < ui->NamesLayout->count(); ++i) {
        QWidget *widget = ui->NamesLayout->itemAt(i)->widget();
        if (widget) {
            widget->hide();
        }
    }
    addBorderReversed();
    QueenKingMateFirst();
}

void StartMenu::addBorder() {
    // A to Z
    for (int col = 0; col < 8; ++col) {
        QGraphicsTextItem *colLetter = new QGraphicsTextItem(QString(QChar('A' + col)));
        colLetter->setPos(col * 50 + 50 / 2 - 28, -6);
        colLetter->setDefaultTextColor(Qt::black);
        chessBoard->scene->addItem(colLetter);
        chessBoard->border.push_back(colLetter);
    }

    // 1 - 8
    for (int row = 0; row < 8; ++row) {
        QGraphicsTextItem *rowNumber = new QGraphicsTextItem(QString::number(8 - row));
        rowNumber->setPos(-4, row * 50 + 50 / 2);
        rowNumber->setDefaultTextColor(Qt::black);
        chessBoard->scene->addItem(rowNumber);
        chessBoard->border.push_back(rowNumber);
    }
}

void StartMenu::addBorderReversed() {
    // Add row numbers on the left side of the board (1 to BOARD_SIZE)
    for (int row = 0; row < 8; ++row) {
        QGraphicsTextItem *rowNumber = new QGraphicsTextItem(QString::number(row + 1));
        rowNumber->setPos(-4, row * 50 + 50 / 2);
        rowNumber->setDefaultTextColor(Qt::black);
        chessBoard->scene->addItem(rowNumber);
        chessBoard->border.push_back(rowNumber);
    }

    // Add column letters on the top side of the board (A to Z)
    for (int col = 0; col < 8; ++col) {
        QGraphicsTextItem *colLetter = new QGraphicsTextItem(QString(QChar('H' - col)));
        colLetter->setPos(col * 50 + 50 / 2 - 28, -6);
        colLetter->setDefaultTextColor(Qt::black);
        chessBoard->scene->addItem(colLetter);
        chessBoard->border.push_back(colLetter);
    }
}

void StartMenu::startClicked()
{
    showChessBoard();
}

void StartMenu::finalQuizButton() {
    firstQuestion();
}

void StartMenu::firstQuestion(){
    ui->firstQuestion->show();
    ui->q1option1->show();
    ui->q1option2->show();
    ui->q1option3->show();
    ui->q1option4->show();
    ui->tryAgain->hide();

    hideStartingScreen();
    ui->Title->setText("Welcome to the Final Quiz");
}

void StartMenu::q1option1Clicked(){
    if(currentQuestion == 1){
        ui->q1option1->setStyleSheet("border: 3px solid green; background-color: lightgray; color: black;");
        QTimer::singleShot(3000, this, &StartMenu::secondQuestion);
        currentQuestion++;
    }
    else{
        ui->q1option1->setStyleSheet("border: 3px solid red; background-color: lightgray; color: black;");
        QTimer::singleShot(3000, this, &StartMenu::showTryAgainButton);
    }
}

void StartMenu::q1option2Clicked(){
    ui->q1option2->setStyleSheet("border: 3px solid red; background-color: lightgray; color: black;");
    QTimer::singleShot(3000, this, &StartMenu::showTryAgainButton);
}

void StartMenu::q1option3Clicked(){
    if(currentQuestion == 2){
        ui->q1option3->setStyleSheet("border: 3px solid green; background-color: lightgray; color: black;");
        QTimer::singleShot(3000, this, &StartMenu::thirdQuestion);
        currentQuestion++;
    }
    else if(currentQuestion == 3){
        ui->q1option3->setStyleSheet("border: 3px solid green; background-color: lightgray; color: black;");
        QTimer::singleShot(3000, this, &StartMenu::celebrate);
    }
    else{
        ui->q1option3->setStyleSheet("border: 3px solid red; background-color: lightgray; color: black;");
        QTimer::singleShot(3000, this, &StartMenu::showTryAgainButton);
    }
}

void StartMenu::q1option4Clicked(){
    ui->q1option4->setStyleSheet("border: 3px solid red; background-color: lightgray; color: black;");
    QTimer::singleShot(3000, this, &StartMenu::showTryAgainButton);
}

void StartMenu::showTryAgainButton() {
    if(currentQuestion == 1){
        ui->tryAgain->show();
        hideOptions();
    }
    else if(currentQuestion == 2){
        ui->tryAgain->move(420, 180);
        ui->tryAgain->show();
        hideOptions();
    }
    else if(currentQuestion == 3){
        ui->tryAgain->show();
        hideOptions();
    }
}

void StartMenu::tryAgainClicked(){
    firstQuestion();
}

void StartMenu::hideOptions(){
    ui->q1option1->hide();
    ui->q1option1->setStyleSheet("");
    ui->q1option2->hide();
    ui->q1option2->setStyleSheet("");
    ui->q1option3->hide();
    ui->q1option3->setStyleSheet("");
    ui->q1option4->hide();
    ui->q1option4->setStyleSheet("");
}

void StartMenu::secondQuestion() {
    ui->q1option1->setStyleSheet("");
    ui->q1option2->setStyleSheet("");
    ui->q1option3->setStyleSheet("");
    ui->q1option4->setStyleSheet("");

    QString imagePath = ":/Images/chessPic.png";

    QString html = QString("<img src='%1' width='130' height='130'/><br/> Question 2: In the figure above, which square should the queen move to in order to secure a checkmate in one move?").arg(imagePath);
    ui->q1option1->move(520, 150);
    ui->q1option2->move(520, 180);
    ui->q1option3->move(520, 210);
    ui->q1option4->move(520, 240);

    ui->q1option1->setText("up 3 squares");
    ui->q1option2->setText("left 1 square");
    ui->q1option3->setText("up 2 squares");
    ui->q1option4->setText("up 1 square");

    ui->firstQuestion->setHtml(html);
}

void StartMenu::thirdQuestion(){
    ui->q1option1->setStyleSheet("");
    ui->q1option2->setStyleSheet("");
    ui->q1option3->setStyleSheet("");
    ui->q1option4->setStyleSheet("");

    QString imagePath = ":/Images/brmate.png";

    QString html = QString("<img src='%1' width='130' height='130'/><br/> Question 3: You are playing as black and it's your move. What is your next possible best move to avoid a backrank checkmate?").arg(imagePath);
    ui->q1option1->setText("king to H8");
    ui->q1option2->setText("take the knight");
    ui->q1option3->setText("pawn to H6");
    ui->q1option4->setText("rook to A8");

    ui->firstQuestion->setHtml(html);
}

void StartMenu::celebrate(){
    hideOptions();
    QString imagePath = ":/Images/johnsoncelebrate.png";
    QString html = QString("<img src='%1' width='311' height='192'/>").arg(imagePath);
    ui->firstQuestion->setHtml(html);
}

void StartMenu::quitButtonClicked()
{
    if (chessBoard) {
        chessBoard->resetBoard();
    }
    hideChessBoard();
    queenKingMove1 = false;
    rankMove1 = false;
    rankMove2 = false;
}

void StartMenu::hideChessBoard()
{
    ui->chessBoardContainer->hide();
    ui->QuitButton->hide();
    ui->NextLevelButton->hide();
    ui->directionsLabel->hide();
    ui->CheckmateLabel->hide();

    ui->CorrectLabel->hide();
    ui->inputBoxLabel->hide();
    ui->inputBox->setText("");

    ui->inputBox->hide();
    ui->inputFoolsMate->hide();
    ui->inputBackRank->hide();
    ui->BackRankText->hide();

    ui->LevelsLabel->show();
    ui->level1Button->show();
    ui->level2Button->show();
    ui->level3Button->show();

    ui->GameModeLabel->show();
    ui->finalQuizButton->show();

    ui->CheckmateLabel->hide();

    ui->TeamCreditsLabel->show();

    for (int i = 0; i < ui->NamesLayout->count(); ++i) {
        QWidget *widget = ui->NamesLayout->itemAt(i)->widget();
        if (widget) {
            widget->show();
        }
    }
    disconnect(ui->inputBox, nullptr, nullptr, nullptr);
    ui->Title->setText("Welcome to Checkmate Simulator");
}

void StartMenu::hideStartingScreen()
{
    ui->LevelsLabel->hide();
    ui->level1Button->hide();
    ui->level2Button->hide();
    ui->level3Button->hide();

    ui->GameModeLabel->hide();
    ui->GameModeLabel->setDisabled(false);
    ui->finalQuizButton->hide();

    ui->TeamCreditsLabel->hide();
    for (int i = 0; i < ui->NamesLayout->count(); ++i) {
        QWidget *widget = ui->NamesLayout->itemAt(i)->widget();
        if (widget) {
            widget->hide();
        }
    }
}

void StartMenu::showChessBoard()
{
    ui->foolsMateText->hide();
    ui->BackRankText->hide();
    ui->KingQueenText->hide();
    ui->NextLevelButton->hide();

    ui->startButton->hide();
    ui->startButton->setEnabled(false);

    ui->inputBox->show();

    ui->directionsLabel->show();

    ui->chessBoardContainer->show();
    ui->QuitButton->show();
    ui->NextLevelButton->show();

    ui->inputBoxLabel->show();
}

void StartMenu::displayCorrect() {
    ui->CorrectLabel->show();

    chessBoard->resetBoard();
    addBorderReversed();
    chessBoard->setupPieces(kingQueenMateMove1);
    //move the White King Forward
    chessBoard->resetBoard();
    chessBoard->setupPieces(kingQueenMateMove1);

    //In 3000 ms move the Black King forward
    QTimer::singleShot(3000, this, [this]() {
        chessBoard->resetBoard();
        addBorderReversed();
        chessBoard->setupPieces(kingQueenMateMove2);
        ui->inputBox->setText("");
        ui->CorrectLabel->hide();
        ui->directionsLabel->setText("Move the White Queen to force a checkmate.");
        QueenKingMateSecond();
    });
}

void StartMenu::displayRankCorrect1() {
    ui->CorrectLabel->show();
    QTimer::singleShot(1000, this, [this]() {
        chessBoard->resetBoard();
        addBorder();
        chessBoard->setupPieces(backRankMateMove1);
    });
    QTimer::singleShot(2000, this, [this]() {
        ui->directionsLabel->setText("Great job! The opposing king is stuck behind a wall of pawns. "
                                     "Put the opposing king into checkmate.");
        backRankMateSecond();
    });
}

void StartMenu::displayRankCorrect2() {
    ui->CorrectLabel->show();
    QTimer::singleShot(1000, this, [this]() {
        chessBoard->resetBoard();
        addBorder();
        chessBoard->setupPieces(backRankMateMove3);
    });
    QTimer::singleShot(2000, this, [this]() {
        ui->directionsLabel->setText("You win!");
        rankMove2 = false;
        displayCheckmate();
        QMessageBox* msgBox = new QMessageBox(QMessageBox::Information
            , "Checkmate!", "Good job! You completed Level 2!", QMessageBox::Ok, this);

        connect(msgBox, &QMessageBox::finished, this, [msgBox](int result) {
            if (result == QMessageBox::Ok) {
            }
            msgBox->deleteLater();
        });
        msgBox->exec();
    });
}

void StartMenu::checkBackRankAnswer() {
    if(ui->inputBackRank->text() == "E3" || ui->inputBackRank->text() == "e3"
        || ui->inputBackRank->text() == "A8" || ui->inputBackRank->text() == "a8") {
        if(rankMove1) {
            displayRankCorrect1();
        }
        if(rankMove2) {
            displayRankCorrect2();
        }
    }
    else {
        QMessageBox::warning(this, "Incorrect Answer", "Try again! That move is not correct.");
        ui->inputBackRank->clear();
    }
}

void StartMenu::backRankMateFirst() {
    rankMove1 = true;
    rankMove2 = false;
    ui->CorrectLabel->hide();
    ui->inputBackRank->setText("");
    ui->directionsLabel->setText("Our king is in check! Get rid of the threat.");
    chessBoard->highlightSquare(2, 0, Qt::yellow);
    chessBoard->highlightSquare(4, 2, Qt::darkYellow);
}

void StartMenu::backRankMateSecond() {
    rankMove1 = false;
    ui->CorrectLabel->hide();
    ui->inputBackRank->setText("");
    chessBoard->deleteHighlights();
    chessBoard->resetBoard();
    addBorder();
    chessBoard->setupPieces(backRankMateMove2);
    backRankMateThird();
}

void StartMenu::backRankMateThird() {
    rankMove2 = true;
    ui->inputBackRank->setText("");
    chessBoard->highlightSquare(0, 0, Qt::yellow);
    chessBoard->highlightSquare(0, 7, Qt::darkYellow);
}

void StartMenu::checkQueenKingCheckmateAnswer()
{
    qDebug() << "check";
    QString userInput = ui->inputBox->text();

    if ((userInput == "C2" || userInput == "c2") && queenKingMove1 == false) {
        displayCorrect();
        queenKingMove1 = true;
    }
    else if ((userInput == "B2" || userInput == "b2") && queenKingMove1 == true) {
        QueenKingB2Checkmate();
    }
    else if ((userInput == "A4" || userInput == "a4") && queenKingMove1 == true) {
        QueenKingA4Checkmate();
    }
    else if ((userInput == "A5" || userInput == "a5") && queenKingMove1 == true) {
        QueenKingA5Checkmate();
    }
    else if ((userInput == "A6" || userInput == "a6") && queenKingMove1 == true) {
        QueenKingA6Checkmate();
    }
    else {
        QMessageBox::warning(this, "Incorrect Answer", "Try again! That move is not correct.");
    }
}

void StartMenu::QueenKingMateFirst() {
    ui->CorrectLabel->hide();
    ui->inputBox->setText("");
    chessBoard->highlightSquare(5, 5, Qt::yellow);
    chessBoard->highlightSquare(5, 6, Qt::darkYellow);
}

void StartMenu::QueenKingMateSecond() {
    ui->CorrectLabel->hide();
    ui->inputBox->setText("");
    chessBoard->highlightSquare(6, 3, Qt::yellow);
    chessBoard->highlightSquare(6, 6, Qt::darkYellow);
    chessBoard->highlightSquare(7, 2, Qt::darkYellow);
    chessBoard->highlightSquare(7, 3, Qt::darkYellow);
    chessBoard->highlightSquare(7, 4, Qt::darkYellow);
}

void StartMenu::QueenKingB2Checkmate()
{
    //In 2000 ms move the White Queen to H4
    QTimer::singleShot(2000, this, [this]() {
        chessBoard->resetBoard();
        addBorderReversed();
        chessBoard->setupPieces(kingQueenCheckmateH4);
        displayCheckmate();
        ui->finalQuizButton->isEnabled();
    });
    //move the White Queen to G7
    chessBoard->resetBoard();
    addBorderReversed();
    chessBoard->setupPieces(kingQueenCheckmateG7);
    displayCheckmate();
    ui->finalQuizButton->isEnabled();
    ui->NextLevelButton->setEnabled(false);
}

void StartMenu::QueenKingA4Checkmate()
{
    //In 2000 ms move the White Queen to H3
    QTimer::singleShot(2000, this, [this]() {
        chessBoard->resetBoard();
        addBorderReversed();
        chessBoard->setupPieces(kingQueenCheckmateH3);
        displayCheckmate();
        ui->finalQuizButton->isEnabled();
        ui->NextLevelButton->setEnabled(false);
    });
    //move the White Queen to H5
    chessBoard->resetBoard();
    addBorderReversed();
     chessBoard->setupPieces(kingQueenCheckmateH5);
    displayCheckmate();
    ui->finalQuizButton->isEnabled();
    ui->NextLevelButton->setEnabled(false);
}

void StartMenu::QueenKingA5Checkmate()
{
    //move the White Queen to H4
    chessBoard->resetBoard();
    addBorderReversed();
    chessBoard->setupPieces(kingQueenCheckmateH4);
    displayCheckmate();
    ui->finalQuizButton->isEnabled();
    ui->NextLevelButton->setEnabled(false);
}

void StartMenu::QueenKingA6Checkmate()
{
    //move the White Queen to H3
    chessBoard->resetBoard();
    addBorderReversed();
    chessBoard->setupPieces(kingQueenCheckmateH3);
    displayCheckmate();
    ui->finalQuizButton->isEnabled();
    ui->NextLevelButton->setEnabled(false);
}

void StartMenu::displayCheckmate() {
    ui->CheckmateLabel->show();
    ui->CheckmateLabel->raise();
    ui->NextLevelButton->setEnabled(1);
}

void StartMenu::saveButtonStates()
{
    settings.beginGroup("ButtonStates");
    for (QPushButton *button : buttons) {
        settings.setValue(button->objectName(), button->isEnabled());
    }
    settings.endGroup();
}

void StartMenu::loadButtonStates()
{
    settings.beginGroup("ButtonStates");
    for (QPushButton *button : buttons) {
        button->setEnabled(settings.value(button->objectName(), true).toBool());
    }
    settings.endGroup();
}

void StartMenu::updateLabel(const QString& message) {
    ui->directionsLabel->setText(message);
    ui->directionsLabel->setWordWrap(true);
}

void StartMenu::checkInputFirstMove() {
    QString userInput = ui->inputFoolsMate->text();
    QString expectedValue1 = "E5";
    QString expectedValue2 = "e5";


    if (fool && (userInput == expectedValue1|| userInput == expectedValue2)) {
        qDebug() << "Input matches the desired value!";
        fool->moveFirstBlackPawn();

        disconnect(ui->inputFoolsMate, &QLineEdit::returnPressed, this, &StartMenu::checkInputFirstMove);

        connect(ui->inputFoolsMate, &QLineEdit::returnPressed, this, &StartMenu::checkInputSecondMove);

        ui->CorrectLabel->show();
        QTimer::singleShot(2000, this, [this]() {
            ui->CorrectLabel->hide();
        });

        emit correctInputReceived();
        fool->secondMove();
    } else {
        QMessageBox::warning(this, "Incorrect Answer", "Try again! That move is not correct.");
        disconnect(ui->inputFoolsMate, &QLineEdit::returnPressed, this, &StartMenu::checkInputFirstMove);
        connect(ui->inputFoolsMate, &QLineEdit::returnPressed, this, &StartMenu::checkInputFirstMove);

    }
    ui->inputFoolsMate->clear();
}

void StartMenu::checkInputSecondMove() {
    QString userInput = ui->inputFoolsMate->text();
    QString expectedValue1 = "H4";
    QString expectedValue2 = "h4";

    if (fool && (userInput == expectedValue1 || userInput == expectedValue2)) {
        qDebug() << "Input matches the desired value!";
        fool->moveBlackQueen();

        ui->CorrectLabel->setText("Correct!");
        ui->CorrectLabel->setStyleSheet("color: green;");
        ui->CorrectLabel->show();

        QTimer::singleShot(2000, this, [this]() {
            ui->CorrectLabel->hide();
            displayCheckmate();
        });

    } else {
        QMessageBox::warning(this, "Incorrect Answer", "Try again! That move is not correct.");
    }
    ui->inputBox->clear();
}

void StartMenu::checkInputThirdMove() {
    QString userInput = ui->inputFoolsMate->text();
    QString expectedValue1 = "H4";
    QString expectedValue2 = "h4";

    if (fool && (userInput == expectedValue1|| userInput == expectedValue2)) {
        qDebug() << "Input matches the desired value!";
        fool->moveBlackQueen();

        ui->CorrectLabel->setText("Correct!");
        ui->CorrectLabel->setStyleSheet("color: green;");
        ui->CorrectLabel->show();

        QTimer::singleShot(2000, this, [this]() {
            ui->CorrectLabel->hide();
            displayCheckmate();
        });

    } else {
        qDebug() << "Input does not match. User entered:" << userInput;
        QMessageBox::warning(this, "Incorrect Answer", "Try again! That move is not correct.");
    }

    ui->inputFoolsMate->clear();
}
