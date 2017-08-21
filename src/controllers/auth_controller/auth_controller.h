#ifndef INKMARK_AUTH_CONTROLLER_H
#define INKMARK_AUTH_CONTROLLER_H

#include <QObject>
#include "models/application_model.h"
#include "views/auth_view/auth_view.h"

class AuthController: public QObject {
  Q_OBJECT

 private:
  ApplicationModel *model;
  AuthView *view;

 private slots:
  void handleLoginClicked(const QString &email, const QString &password);

 public:
  AuthController(ApplicationModel *m = nullptr, AuthView *view = nullptr);
};

#endif //INKMARK_AUTH_CONTROLLER_H
