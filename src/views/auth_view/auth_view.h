#ifndef INKMARK_LOGIN_VIEW_H
#define INKMARK_LOGIN_VIEW_H

#include <QWidget>
#include <QFormLayout>
#include "widgets/text_input_widget/text_input_widget.h"

class AuthView: public QWidget {
  Q_OBJECT

 private:
  TextInputWidget *loginEmailInput;
  TextInputWidget *loginPwdInput;
  TextInputWidget *registerNameInput;
  TextInputWidget *registerSurnameInput;
  TextInputWidget *registerEmailInput;
  TextInputWidget *registerPwdInput;
  TextInputWidget *registerPwdConfirmInput;
  QWidget *loginArea;
  QWidget *registerArea;

  QWidget *createLoginBtns() const;
  QWidget *createLoginArea();
  QWidget *createRegisterBtns() const;
  QWidget *createRegisterArea();

  private slots:
   void handleLoginClicked();
   void handleAdminClicked();
   void handleRegisterClicked();
   void toggleAreas();

 public:
  AuthView(QWidget *parent = nullptr);

 public slots:
  void clear();

 signals:
  void guestClicked();
  void registerClicked(const QString &name, const QString &surname, const QString &email, const QString &password, const QString &passwordConfirm);
  void loginClicked(const QString &email, const QString &password);
  void adminClicked(const QString &email, const QString &password);
};

#endif //INKMARK_LOGIN_VIEW_H
