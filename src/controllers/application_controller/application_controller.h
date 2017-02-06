#ifndef INKMARK_APPLICATION_CONTROLLER_H
#define INKMARK_APPLICATION_CONTROLLER_H

#include "models/application_model.h"
#include "views/application_view/application_view.h"
#include "controllers/user_application_controller/user_application_controller.h"

/**
 * Inizializza i controllers del modulo admin e utente
 */
class ApplicationController {
 private:
  ApplicationModel *model;
  ApplicationView *view;
  UserApplicationController *userApplicationController;

 public:
  ApplicationController(ApplicationModel *m = nullptr, ApplicationView *v = nullptr);
  ~ApplicationController();
};

#endif //INKMARK_APPLICATION_CONTROLLER_H
