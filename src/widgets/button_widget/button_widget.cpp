#include "button_widget.h"

QSizePolicy ButtonWidget::sizePolicy = QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

void ButtonWidget::init() {
  setStyleSheet(
    "ButtonWidget {"
      "background-color: #e3e1e1;"
      "border-radius: 3px;"
      "color: #737373;"
      "padding: 8px 12px;"
    "}"
    "ButtonWidget:hover {"
      "background-color: #767373;"
      "color: #ffffff;"
    "}"
  );
  setCursor(Qt::PointingHandCursor);
  setSizePolicy(sizePolicy);
}

ButtonWidget::ButtonWidget(QWidget *parent): QPushButton(parent) { init(); }

ButtonWidget::ButtonWidget(QString text, QWidget *parent): QPushButton(text, parent) { init(); }
