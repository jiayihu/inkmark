#include <QSizePolicy>
#include "button_widget.h"

ButtonWidget::ButtonWidget(QWidget *parent): QPushButton(parent) {}

ButtonWidget::ButtonWidget(QString text, QWidget *parent): QPushButton(text, parent) {
  setFixedSize(sizeHint());
}
