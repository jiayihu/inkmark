#ifndef INKMARK_BUTTON_WIDGET_H
#define INKMARK_BUTTON_WIDGET_H

#include <QPushButton>
#include <QString>

class ButtonWidget: public QPushButton {
 public:
  ButtonWidget(QWidget *parent = nullptr);
  ButtonWidget(QString text, QWidget *parent = nullptr);
};

#endif //INKMARK_BUTTON_WIDGET_H
