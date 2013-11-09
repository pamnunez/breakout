/* File: main.cpp
   Author: Pamela Nunez
   Desc: Main file to start off Breakout (main.cpp)
*/

#include <QtGui>
#include "breakout.h"

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  Breakout breakout;
  breakout.show();

  return app.exec();
}
