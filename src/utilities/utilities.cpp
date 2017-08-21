#include "utilities.h"

QWidget* wrap(QLayout* layout) {
  QWidget* wrapper = new QWidget();
  wrapper->setLayout(layout);

  return wrapper;
}
