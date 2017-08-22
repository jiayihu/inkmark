#include "utilities.h"

QWidget* wrap(QLayout* layout) {
  QWidget* wrapper = new QWidget();
  wrapper->setLayout(layout);

  return wrapper;
}

QWidget* createSpacer() {
  QWidget *spacer = new QWidget();
  spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  spacer->setStyleSheet("background-color: transparent;");

  return spacer;
}
