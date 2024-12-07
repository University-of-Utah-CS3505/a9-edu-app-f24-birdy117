#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Box2D/Box2D.h>
#include <QMainWindow>
#include <QPainter>
#include <QRandomGenerator>
#include <QTimer>

using std::pair;


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void paintEvent(QPaintEvent* event);

    b2Body* makeBody();


public slots:
    void updateWorld();

    void goPushed();

private:
    Ui::MainWindow *ui;
    b2World* world;
    bool bounceGoing;
    QTimer *timer;
    b2Vec2 const launchForce;
    QMap<b2Body*, QRectF*> confetti;
    QList<QColor> colors;


};
#endif // MAINWINDOW_H
