#include "text_input_widget.h"

TextInputWidget::TextInputWidget(QWidget *parent): QLineEdit(parent) {
  setMinimumWidth(200);
}
