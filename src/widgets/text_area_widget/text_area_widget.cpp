#include "text_area_widget.h"

TextAreaWidget::TextAreaWidget(QWidget *parent): QTextEdit(parent) {
  // Disabilita il bordo azzurro del focus
  setAttribute(Qt::WA_MacShowFocusRect, false);
  setStyleSheet(
    "TextAreaWidget {"
      "background-color: #f0f0f0;"
      "border-radius: 3px;"
      "padding: 5px;"
      "}"
      "TextAreaWidget:focus {"
      "background-color: #fff;"
      "border: 1px solid #ccc;"
      "}"
  );
  setMinimumWidth(200);
  // Al copy-paste incolla il testo senza formattazione
  setAcceptRichText(false);
}
