#include "text_input_widget.h"

TextInputWidget::TextInputWidget(QWidget *parent): QLineEdit(parent) {
  setMinimumWidth(150);
  // Disabilita il bordo azzurro del focus
  setAttribute(Qt::WA_MacShowFocusRect, 0);
  setStyleSheet(
    "TextInputWidget {"
      "background-color: #f0f0f0;"
      "border-radius: 3px;"
      "padding: 5px;"
    "}"
    "TextInputWidget:focus {"
      "background-color: #fff;"
      "border: 1px solid #ccc;"
    "}"
  );
}
