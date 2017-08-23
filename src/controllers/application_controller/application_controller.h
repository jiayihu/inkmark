#ifndef INKMARK_APPLICATION_CONTROLLER_H
#define INKMARK_APPLICATION_CONTROLLER_H

#include "models/application_model.h"
#include "views/application_view/application_view.h"
#include "controllers/auth_controller/auth_controller.h"
#include "controllers/admin/admin_application_controller/admin_application_controller.h"
#include "controllers/users/user_application_controller/user_application_controller.h"

/**
 * Inizializza i controllers del modulo admin e utente
 */
class ApplicationController {
 private:
  ApplicationModel *model;
  ApplicationView *view;
  AuthController *authController;
  AdminApplicationController *adminApplicationController;
  UserApplicationController *userApplicationController;

 public:
  ApplicationController(ApplicationModel *m = nullptr, ApplicationView *v = nullptr);
  ~ApplicationController();
};

#endif //INKMARK_APPLICATION_CONTROLLER_H
