#include "utilities.h"

/**
 * Wrappa un layout dentro un QWidget per permettere layout annidati.
 * QLayout non permette `.addWidget()` di altri layout
 */
QWidget* wrap(QLayout* layout) {
  QWidget* wrapper = new QWidget();
  wrapper->setLayout(layout);

  return wrapper;
}
