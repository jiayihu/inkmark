#include <iostream>
#include <QApplication>
#include "inkmark.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  Inkmark inkmark;
  inkmark.init();

  return app.exec();
}
