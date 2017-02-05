#ifndef INKMARK_BUTTON_WIDGET_H
#define INKMARK_BUTTON_WIDGET_H

#include <QPushButton>
#include <QString>
#include <QSizePolicy>

class ButtonWidget: public QPushButton {
  // Macro necessaria per cambiare la .className() da QPushButton a ButtonWidget
  // affinché si possa usare ButtonWidget come selettore negli stylesheets
  Q_OBJECT

 private:
  static QSizePolicy sizePolicy;
  void init();

 public:
  ButtonWidget(QWidget *parent = nullptr);
  ButtonWidget(QString text, QWidget *parent = nullptr);
};

#endif //INKMARK_BUTTON_WIDGET_H
