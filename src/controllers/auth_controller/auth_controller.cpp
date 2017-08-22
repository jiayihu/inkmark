#include "auth_controller.h"

void AuthController::handleLoginClicked(const QString &email, const QString &password) {
  model->loginUser(email, password);
}

AuthController::AuthController(ApplicationModel *m, AuthView *v): model(m), view(v) {
  QObject::connect(view, SIGNAL(loginClicked(QString, QString)), model, SLOT(loginUser(QString, QString)));
  QObject::connect(view, SIGNAL(guestClicked()), model, SLOT(loginAsGuest()));

  // Pulire gli input al login con successo
  QObject::connect(model, SIGNAL(loggedIn(UserInterface*)), view, SLOT(clear()));
}
