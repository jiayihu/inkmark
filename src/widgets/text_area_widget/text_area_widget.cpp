#include "text_area_widget.h"

TextAreaWidget::TextAreaWidget() {
  setMinimumWidth(300);
  // Al copy-paste incolla il testo senza formattazione
  setAcceptRichText(false);
}
