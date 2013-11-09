/* Author: Pamela Nunez
   Desc: Defines the Breakout game (breakout.cpp)
*/

#include <QtGui>
#include "breakout.h"
#include "breakout_canvas.h"

Breakout::Breakout() {
    setWindowTitle("Breakout!");

    // TODO: Add widget for game status showing bricks remaining, number of wins?
    // there are only two widgets, and they're stacked vertically
    QVBoxLayout* layout = new QVBoxLayout(this);
    canvas = new BreakoutCanvas(this);
    layout->addWidget(canvas);

//    QHBoxLayout* statusBox = new QHBoxLayout(this);

//    QLabel *status = new QLabel("Remaining Bricks: ", this);
//    status->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
//    layout->addWidget(status);

//    QLabel *total = new QLabel(this);
//    total->setNum(0);
//    total->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
//    layout->addWidget(total);
//    layout->addWidget(status);

//    QGridLayout* grid = new QGridLayout(this);
//    layout->addLayout(grid);
//    layout->addWidget(canvas);

    controlButton = new QPushButton("Start", this);
    layout->addWidget(controlButton);

    // the button directly controls the canvas
    connect(controlButton, SIGNAL(clicked()), canvas, SLOT(buttonPress()));

    // the canvas can control the button
    connect(canvas, SIGNAL(needsButtonChange(QString)),
      this, SLOT(changeButtonText(QString)));
    connect(canvas, SIGNAL(needsStatusChange(int)), this,
      SLOT(changeStatusInt(int)));

}

void Breakout::changeButtonText(QString str) {
    controlButton->setText(str);
}

void Breakout::changeStatusInt(int tot) {
    total->setNum(tot);
}
