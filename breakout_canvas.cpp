/* Author: Pamela Nunez
   Desc: Defines the behavior of the Breakout game (breakout_canvas.cpp)
*/

#include <QtGui>
#include "breakout_canvas.h"

BreakoutCanvas::BreakoutCanvas(QWidget* parent)
: QWidget(parent) { // This passes the constructor parameter to the superclass

    timer = new QTimer(this);
    timer->setInterval(5); // an interval of 5ms
    connect(timer, SIGNAL(timeout()), this, SLOT(timerTicked()));

    setFixedSize(WIDTH, HEIGHT);
    remainingBricks = TOTAL_BRICKS;
    reset();
}

void BreakoutCanvas::buttonPress() {
    switch(state) {
    case BEFORE_PLAY:
        timer->start();
        needsButtonChange("Pause");
//        needsStatusChange(TOTAL_BRICKS);
        state = PLAYING;
        break;

    case PLAYING:
        timer->stop();
        needsButtonChange("Resume");
//        needsStatusChange(remainingBricks);
        state = PAUSED;
        break;

    case PAUSED:
        timer->start();
        needsButtonChange("Pause");
//        needsStatusChange(remainingBricks);
        state = PLAYING;
        break;

    case AFTER_PLAY:
        reset();
        needsButtonChange("Start");
//        needsStatusChange(remainingBricks);
        state = BEFORE_PLAY;
        break;
    }

    setFocus(Qt::OtherFocusReason); // make sure that the canvas gets keystrokes
}

void BreakoutCanvas::reset() {
    // center paddles and ball
    playerX = compX = WIDTH / 2 - (PADDLE_WIDTH / 2);
//    playerX = WIDTH / 2 - (PADDLE_WIDTH / 2);
    ball = QPoint(WIDTH / 2, HEIGHT / 2);

    // moving up and right
    goingDown = false;
    goingRight = true;

    // player's paddle is not moving
    paddleLeft = false;
    paddleRight = false;

    state = BEFORE_PLAY;

    // update() forces a repaint of the canvas
    update();
}

// we ignore the QPaintEvent* parameter, so we omit the name to avoid getting
// a warning
// TODO: Add drawing for bricks.
void BreakoutCanvas::paintEvent(QPaintEvent*) {
    // create painting context -- the painting context does all the work
    QPainter p(this);

    // draw a frame around the field:
    p.drawRect(0, 0, WIDTH-1, HEIGHT-1);

    // draw the paddles
    p.fillRect(playerX, HEIGHT - PADDLE_HEIGHT,
         PADDLE_WIDTH, PADDLE_HEIGHT, Qt::blue);
    p.fillRect(compX, 0, PADDLE_WIDTH, PADDLE_HEIGHT, Qt::blue);



    // no fillEllipse... so we need to set the brush and use drawEllipse
    p.setBrush(Qt::red); // use implicit QBrush constructor
    p.drawEllipse(ball.x() - BALL_RADIUS, ball.y() - BALL_RADIUS,
        BALL_RADIUS * 2, BALL_RADIUS * 2);

    // show that the user lost if necessary
    if(state == AFTER_PLAY) {
    // this will draw the text centered in the play area
        p.drawText(QRect(0, 0, WIDTH, HEIGHT), Qt::AlignCenter, "Game over!");
    }
}
// TODO: Add functionality for removing bricks when ball bounces.
// TODO: Change end game check to include win for all bricks gone.
void BreakoutCanvas::timerTicked() {
    // this will get called every 50 milliseconds

    // first, move the ball:
    if(goingRight) {
        ball.rx()++;
    } else {
        ball.rx()--;
    }

    if(goingDown) {
        ball.ry()++;
    } else {
        ball.ry()--;
    }

    // should the ball bounce?
    if(ball.x() + BALL_RADIUS >= WIDTH) {
        goingRight = false;
    }

    if(ball.x() - BALL_RADIUS <= 0) {
        goingRight = true;
    }

    // the computer paddle is always in the right spot
    if(ball.y() - BALL_RADIUS <= PADDLE_HEIGHT) {
        goingDown = true;
    }

    // but the player's paddle might not be -- check
    if(ball.y() + BALL_RADIUS >= HEIGHT - PADDLE_HEIGHT &&
     ball.x() >= playerX &&
     ball.x() <= playerX + PADDLE_WIDTH) {
        goingDown = false;
    }

    // move the computer's paddle:
    compX = ball.x() - PADDLE_WIDTH / 2;
    if(compX <= 0) {
        compX = 0;
    }

    if(compX + PADDLE_WIDTH >= WIDTH) {
        compX = WIDTH - PADDLE_WIDTH;
    }

    // move the player's paddle:
    if(paddleLeft) {
        playerX--;
    }

    if(paddleRight) {
        playerX++;
    }

    if(playerX <= 0) {
        playerX = 0;
    }

    if(playerX + PADDLE_WIDTH >= WIDTH) {
        playerX = WIDTH - PADDLE_WIDTH;
    }

    // did the player lose?
    if(ball.y() >= HEIGHT) {
        timer->stop();
        state = AFTER_PLAY;
        needsButtonChange("Restart");
    }

    update(); // force a redraw
}

// TODO: Add functionality for Spacebar to start/pause game.
void BreakoutCanvas::keyPressEvent(QKeyEvent* event){
    if(event->key() == Qt::Key_Left) {
        paddleLeft = true;
    }

    if(event->key() == Qt::Key_Right) {
        paddleRight = true;
    }
    if(event->key() == Qt::Key_Space) {
        if (state == PLAYING) {
            timer->stop();
            state = PAUSED;
            needsButtonChange("Resume");
        } else if (state == PAUSED) {
            timer->start();
            state = PLAYING;
            needsButtonChange("Pause");
        } else if (state == AFTER_PLAY) {
            reset();
            needsButtonChange("Start");
        } else if (state == BEFORE_PLAY) {
            timer->start();
            state = PLAYING;
            needsButtonChange("Pause");

        }
    }
    if(event->key() == Qt::Key_Q) {
        exit(0);
    }
}

void BreakoutCanvas::keyReleaseEvent(QKeyEvent*) {
    paddleLeft = paddleRight = false;
}
