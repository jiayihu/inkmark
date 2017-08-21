#ifndef INKMARK_LOGIN_VIEW_H
#define INKMARK_LOGIN_VIEW_H

#include <QWidget>
#include <QFormLayout>
#include "widgets/text_input_widget/text_input_widget.h"

class AuthView: public QWidget {
  Q_OBJECT

 private:
  TextInputWidget *emailInput;
  TextInputWidget *passwordInput;

  QWidget *createButtons() const;

  private slots:
   void handleLoginClicked();

 public:
  AuthView(QWidget *parent = nullptr);

 public slots:
  void clear();

 signals:
  void guestClicked();
  void registerClicked();
  void loginClicked(QString email, QString password);
};

#endif //INKMARK_LOGIN_VIEW_H
