#ifndef INKMARK_UTILITIES_H
#define INKMARK_UTILITIES_H

#include <QWidget>
#include <QLayout>

/**
 * Wrappa un QLayout in un QWidget affinché possa essere annidato all'interno
 * di un altro QLayout. Qt non permette QLayout annidati direttamente
 */
QWidget* wrap(QLayout* layout);

/**
 * Create in widget vuoto auto-espandente come trick per allineare elementi a
 * destra
 */
QWidget* createSpacer();

#endif //INKMARK_UTILITIES_H
