#include "utilities.h"

QWidget* wrapInWidget(QLayout *layout) {
  QWidget* wrapper = new QWidget();
  wrapper->setLayout(layout);

  return wrapper;
}

QLayout *wrapInLayout(QWidget *widget) {
  QVBoxLayout *layout = new QVBoxLayout();
  layout->setContentsMargins(0, 0, 0, 0);
  layout->addWidget(widget);

  return layout;
}

QWidget* createSpacer() {
  QWidget *spacer = new QWidget();
  spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  spacer->setStyleSheet("background-color: transparent;");

  return spacer;
}
