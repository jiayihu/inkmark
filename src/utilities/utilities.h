#ifndef INKMARK_UTILITIES_H
#define INKMARK_UTILITIES_H

#include <QWidget>
#include <QLayout>

/**
 * Wrappa un QLayout in un QWidget affinché possa essere annidato all'interno
 * di un altro QLayout. Qt non permette QLayout annidati direttamente
 */
QWidget* wrap(QLayout* layout);

#endif //INKMARK_UTILITIES_H
