#include <cmath>
#include "button_widget.h"

QSizePolicy ButtonWidget::sizePolicy = QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

void ButtonWidget::init() {
  setStyleSheet(
    "ButtonWidget {"
      "background-color: #ffffff;"
      "border: 1px solid #e3e1e1;"
      "border-radius: 3px;"
      "color: #4C5052;"
      "padding: 8px 12px;"
    "}"
    "ButtonWidget:hover {"
      "border-color: #54C0C0;"
      "background-color: #54C0C0;"
      "color: #ffffff;"
    "}"
  );
  setCursor(Qt::PointingHandCursor);
  setSizePolicy(sizePolicy);
}

ButtonWidget::ButtonWidget(QWidget *parent): QPushButton(parent) {
  init();
}

ButtonWidget::ButtonWidget(const QString &text, QWidget *parent): QPushButton(text, parent) {
  init();
}

void ButtonWidget::setSize(float factor) {
  QSize currentSize = sizeHint();
  int width = static_cast<int>(std::round(currentSize.width() * factor));
  int height = static_cast<int>(std::round(currentSize.height() * factor));
  setMinimumSize(width, height);
}
