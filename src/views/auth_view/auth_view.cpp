#include <QLabel>
#include "auth_view.h"
#include "widgets/button_widget/button_widget.h"
#include "utilities/utilities.h"

QWidget * AuthView::createButtons() const {
  QVBoxLayout *layout = new QVBoxLayout();
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setAlignment(Qt::AlignHCenter);

  // Bottone Login
  ButtonWidget *loginButton = new ButtonWidget("Login");
  loginButton->setSize(1.5);
  QObject::connect(loginButton, SIGNAL(clicked()), this, SLOT(handleLoginClicked()));
  layout->addWidget(loginButton);

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
  QObject::connect(registerButton, SIGNAL(clicked()), this, SIGNAL(registerClicked()));

  minorLayout->addWidget(guestButton);
  minorLayout->addWidget(registerButton);
  layout->addWidget(wrap(minorLayout));


  return wrap(layout);
}

void AuthView::handleLoginClicked() {
  QString email = emailInput->text();
  QString password = passwordInput->text();

  emit loginClicked(email, password);
}

AuthView::AuthView(QWidget *parent): QWidget(parent) {
  QVBoxLayout *layout = new QVBoxLayout();
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setAlignment(Qt::AlignCenter);
  setMinimumSize(480, 360);

  QPixmap logoImg("images/logo.png");
  QLabel *logo = new QLabel();
  logo->setPixmap(logoImg.scaled(136, 104, Qt::KeepAspectRatio));
  logo->setAlignment(Qt::AlignCenter);
  layout->addWidget(logo);

  QFormLayout *formLayout = new QFormLayout();
  emailInput = new TextInputWidget();
  passwordInput = new TextInputWidget();
  passwordInput->setEchoMode(QLineEdit::Password);

  formLayout->addRow(new QLabel("Email"), emailInput);
  formLayout->addRow(new QLabel("Password"), passwordInput);

  QWidget *buttons = createButtons();

  layout->addWidget(wrap(formLayout));
  layout->addWidget(buttons);
  setLayout(layout);
}
