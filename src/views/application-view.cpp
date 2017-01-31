#include "application-view.h"

ApplicationView::ApplicationView(QWidget *parent): QWidget(parent) {
  setWindowTitle("Inkmark");
  resize(300, 300);

  QPushButton *quit = new QPushButton("Quit", this);
  QObject::connect(quit, SIGNAL(clicked()), this, SIGNAL(clickedQuit()));
}
