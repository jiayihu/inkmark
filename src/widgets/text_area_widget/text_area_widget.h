#ifndef INKMARK_TEXT_AREAD_WIDGET_H
#define INKMARK_TEXT_AREAD_WIDGET_H

#include <QTextEdit>

class TextAreaWidget: public QTextEdit {
  Q_OBJECT

 public:
  TextAreaWidget(QWidget *parent = nullptr);
};

#endif //INKMARK_TEXT_AREAD_WIDGET_H
