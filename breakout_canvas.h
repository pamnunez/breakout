/* File: breakout_canvas.h
   Author: Pamela Nunez
   Desc: header file for Breakout canvas. The game logic goes here.
    (breakout_canvas.h)
*/

#ifndef BREAKOUT_CANVAS_H_
#define BREAKOUT_CANVAS_H_

#include <QtGui>

class BreakoutCanvas : public QWidget {

    Q_OBJECT

    public:
    BreakoutCanvas(QWidget* parent);

    signals:
    void needsButtonChange(QString str);
    void needsStatusChange(int total);

    public slots:
    void buttonPress();

    protected:
    void paintEvent(QPaintEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

    private slots:
    void timerTicked();

    private:
    void reset(); // reset playing field

    enum State { BEFORE_PLAY, PLAYING, PAUSED, AFTER_PLAY } state;

    QTimer* timer;

    // coordinates of the left sides of the paddles
    int playerX;
    int compX;
    int brickX;
    int brickY;
    int remainingBricks;

    QPoint ball; // coordinates of center of ball

    // direction of ball
    bool goingRight;
    bool goingDown;

    // movement of player paddle
    bool paddleLeft;
    bool paddleRight;

    static const int WIDTH = 400;
    static const int HEIGHT = 400;

    static const int PADDLE_WIDTH = 40;
    static const int PADDLE_HEIGHT = 10;

    static const int BALL_RADIUS = 5;

    static const int TOTAL_BRICKS = 24;
};

#endif
