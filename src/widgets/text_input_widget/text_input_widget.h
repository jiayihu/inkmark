#ifndef INKMARK_TEXT_INPUT_WIDGET_H
#define INKMARK_TEXT_INPUT_WIDGET_H

#include <QLineEdit>

class TextInputWidget: public QLineEdit {
  Q_OBJECT

 public:
  TextInputWidget(QWidget *parent = nullptr);
};

#endif //INKMARK_TEXT_INPUT_WIDGET_H
