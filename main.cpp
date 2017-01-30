#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QStringListModel>
#include <QListView>
#include "src/model/model.h"

int main(int argc, char* argv[]) {
  Model model;
  QApplication app(argc, argv);
  QWidget window;
  window.setWindowTitle("I'm a QWidget");
  window.resize(300, 300);

  QStringList numbers;
  numbers << "One" << "Two" << "Three" << "Four" << "Five";
  QAbstractItemModel *model = new QStringListModel(numbers);

  QListView *view = new QListView(&window);
  view->setModel(model);

  window.show();
  return app.exec();
}
