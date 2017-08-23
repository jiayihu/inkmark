#include "auth_controller.h"

void AuthController::handleLoginClicked(const QString &email, const QString &password) {
  model->loginUser(email, password);
}

AuthController::AuthController(ApplicationModel *m, AuthView *v): model(m), view(v) {
  // View => Model
  QObject::connect(view, SIGNAL(loginClicked(QString, QString)), model, SLOT(loginUser(QString, QString)));
  QObject::connect(view, SIGNAL(adminClicked(QString, QString)), model, SLOT(loginAdmin(QString, QString)));
  QObject::connect(view, SIGNAL(guestClicked()), model, SLOT(loginAsGuest()));
  QObject::connect(view,
                   SIGNAL(registerClicked(QString, QString, QString, QString, QString)),
                   model,
                   SLOT(registerUser(QString, QString, QString, QString, QString)));

  // Model => View
  QObject::connect(model, SIGNAL(loggedInUser(UserInterface*)), view, SLOT(clear()));
  QObject::connect(model, SIGNAL(loggedInAdmin(UserInterface*)), view, SLOT(clear()));
}
