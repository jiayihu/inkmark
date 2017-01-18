#include <iostream>
#include <QApplication>
#include <QDebug>

int main() {
  std::cout << "Hello, World!" << std::endl;
  qDebug() << QT_VERSION_STR;
  return 0;
}
