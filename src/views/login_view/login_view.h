#ifndef INKMARK_LOGIN_VIEW_H
#define INKMARK_LOGIN_VIEW_H

#include <QWidget>
#include <QFormLayout>
#include "widgets/text_input_widget/text_input_widget.h"

class LoginView: public QWidget {
  Q_OBJECT

 private:
  TextInputWidget *emailInput;
  TextInputWidget *passwordInput;

  QWidget *createButtons() const;

  private slots:
   void handleSubmitClicked();

 public:
  LoginView(QWidget *parent = nullptr);

  signals:
   void registerClicked();
   void loginClicked(QString email, QString password);
};

#endif //INKMARK_LOGIN_VIEW_H
