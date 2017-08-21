#include <QLabel>
#include "login_view.h"
#include "widgets/button_widget/button_widget.h"
#include "utilities/utilities.h"

QWidget * LoginView::createButtons() const {
  QVBoxLayout *layout = new QVBoxLayout();
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setAlignment(Qt::AlignHCenter);

  ButtonWidget *submitButton = new ButtonWidget("Login");
  QObject::connect(submitButton, SIGNAL(clicked()), this, SLOT(handleSubmitClicked()));
  layout->addWidget(submitButton);

  QHBoxLayout *minorLayout = new QHBoxLayout();
  ButtonWidget *registerButton = new ButtonWidget("Register");
  QObject::connect(registerButton, SIGNAL(clicked()), this, SIGNAL(registerClicked()));
  minorLayout->addWidget(registerButton);
  layout->addWidget(wrap(minorLayout));

  return wrap(layout);
}

void LoginView::handleSubmitClicked() {
  QString email = emailInput->text();
  QString password = passwordInput->text();

  emit loginClicked(email, password);
}

LoginView::LoginView(QWidget *parent): QWidget(parent) {
  QVBoxLayout *layout = new QVBoxLayout();
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setAlignment(Qt::AlignCenter);
  setMinimumSize(480, 320);

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
