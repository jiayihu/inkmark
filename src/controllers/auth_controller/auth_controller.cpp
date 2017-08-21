#include "auth_controller.h"

void AuthController::handleLoginClicked(const QString &email, const QString &password) {
  model->loginUser(email, password);
}

AuthController::AuthController(ApplicationModel *m, AuthView *v): model(m), view(v) {
  QObject::connect(view, SIGNAL(loginClicked(QString, QString)), this, SLOT(handleLoginClicked(QString, QString)));
}
