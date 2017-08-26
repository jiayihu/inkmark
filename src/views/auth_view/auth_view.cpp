#include <QLabel>
#include "auth_view.h"
#include "widgets/button_widget/button_widget.h"
#include "utilities/utilities.h"

QWidget* AuthView::createLoginBtns() const {
  QVBoxLayout *layout = new QVBoxLayout();
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setAlignment(Qt::AlignHCenter);

  // Bottoni Login
  ButtonWidget *loginButton = new ButtonWidget("Log into User area");
  QObject::connect(loginButton, SIGNAL(clicked()), this, SLOT(handleLoginClicked()));
  layout->addWidget(loginButton);

  ButtonWidget *adminButton = new ButtonWidget("Log into Admin area");
  QObject::connect(adminButton, SIGNAL(clicked()), this, SLOT(handleAdminClicked()));
  layout->addWidget(adminButton);

  // Scritta OR
  QLabel *orLabel = new QLabel("OR");
  orLabel->setAlignment(Qt::AlignHCenter);
  layout->addWidget(orLabel);

  // Bottoni per loggare come Guest o per Registrarsi
  QHBoxLayout *minorLayout = new QHBoxLayout();
  minorLayout->setContentsMargins(0, 0, 0, 0);

  ButtonWidget *guestButton = new ButtonWidget("Enter as Guest");
  QObject::connect(guestButton, SIGNAL(clicked()), this, SIGNAL(guestClicked()));

  ButtonWidget *registerButton = new ButtonWidget("Register");
  QObject::connect(registerButton, SIGNAL(clicked()), this, SLOT(toggleAreas()));

  minorLayout->addWidget(guestButton);
  minorLayout->addWidget(registerButton);
  layout->addWidget(wrapInWidget(minorLayout));

  return wrapInWidget(layout);
}

QWidget* AuthView::createRegisterBtns() const {
  QVBoxLayout *layout = new QVBoxLayout();
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setAlignment(Qt::AlignHCenter);

  // Bottone Login
  ButtonWidget *registerButton = new ButtonWidget("Register");
  registerButton->setSize(1.5);
  QObject::connect(registerButton, SIGNAL(clicked()), this, SLOT(handleRegisterClicked()));
  layout->addWidget(registerButton);

  // Scritta OR
  QLabel *orLabel = new QLabel("OR");
  orLabel->setAlignment(Qt::AlignHCenter);
  layout->addWidget(orLabel);

  // Bottone per tornare al Login
  ButtonWidget *loginButton = new ButtonWidget("Back to Login");
  QObject::connect(loginButton, SIGNAL(clicked()), this, SLOT(toggleAreas()));

  layout->addWidget(loginButton);

  return wrapInWidget(layout);
}

QWidget* AuthView::createLoginArea() {
  QVBoxLayout *layout = new QVBoxLayout();

  // Area campi input
  QFormLayout *formLayout = new QFormLayout();
  loginEmailInput = new TextInputWidget();
  loginPwdInput = new TextInputWidget();
  loginPwdInput->setEchoMode(QLineEdit::Password);

  formLayout->addRow(new QLabel("Email"), loginEmailInput);
  formLayout->addRow(new QLabel("Password"), loginPwdInput);

  QWidget *buttons = createLoginBtns();

  layout->addWidget(wrapInWidget(formLayout));
  layout->addWidget(buttons);

  return wrapInWidget(layout);
}

QWidget* AuthView::createRegisterArea() {
  QVBoxLayout *layout = new QVBoxLayout();

  // Area campi input
  QFormLayout *formLayout = new QFormLayout();
  registerNameInput = new TextInputWidget();
  registerSurnameInput = new TextInputWidget();
  registerEmailInput = new TextInputWidget();
  registerPwdInput = new TextInputWidget();
  registerPwdInput->setEchoMode(QLineEdit::Password);
  registerPwdConfirmInput = new TextInputWidget();
  registerPwdConfirmInput->setEchoMode(QLineEdit::Password);

  formLayout->addRow(new QLabel("Name *"), registerNameInput);
  formLayout->addRow(new QLabel("Surname *"), registerSurnameInput);
  formLayout->addRow(new QLabel("Email *"), registerEmailInput);
  formLayout->addRow(new QLabel("Password *"), registerPwdInput);
  formLayout->addRow(new QLabel("Confirm password *"), registerPwdConfirmInput);

  QWidget *buttons = createRegisterBtns();

  layout->addWidget(wrapInWidget(formLayout));
  layout->addWidget(buttons);

  return wrapInWidget(layout);
}

void AuthView::handleLoginClicked() {
  QString email = loginEmailInput->text();
  QString password = loginPwdInput->text();

  emit loginClicked(email, password);
}

void AuthView::handleAdminClicked() {
  QString email = loginEmailInput->text();
  QString password = loginPwdInput->text();

  emit adminClicked(email, password);
}

void AuthView::handleRegisterClicked() {
  QString name = registerNameInput->text();
  QString surname = registerSurnameInput->text();
  QString email = registerEmailInput->text();
  QString password = registerPwdInput->text();
  QString passwordConfirm = registerPwdConfirmInput->text();

  emit registerClicked(name, surname, email, password, passwordConfirm);
}

void AuthView::toggleAreas() {
  if (registerArea->isHidden()) {
    loginArea->setVisible(false);
    registerArea->setVisible(true);
  } else {
    registerArea->setVisible(false);
    loginArea->setVisible(true);
  }
}

AuthView::AuthView(QWidget *parent): QWidget(parent) {
  QVBoxLayout *layout = new QVBoxLayout();
  layout->setAlignment(Qt::AlignCenter);
  setMinimumSize(480, 360);

  QPixmap logoImg(":/logo.png");
  QLabel *logo = new QLabel();
  logo->setPixmap(logoImg.scaled(136, 104, Qt::KeepAspectRatio));
  logo->setAlignment(Qt::AlignCenter);
  layout->addWidget(logo);

  loginArea = createLoginArea();
  registerArea = createRegisterArea();
  registerArea->setVisible(false);

  layout->addWidget(loginArea);
  layout->addWidget(registerArea);

  setLayout(layout);
}

void AuthView::clear() {
  loginEmailInput->clear();
  loginPwdInput->clear();
  registerArea->setVisible(false);
  loginArea->setVisible(true);
}
