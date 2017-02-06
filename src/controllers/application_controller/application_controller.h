#ifndef INKMARK_APPLICATION_CONTROLLER_H
#define INKMARK_APPLICATION_CONTROLLER_H

#include "models/application_model.h"
#include "views/application_view/application_view.h"

/**
 * Controller generale dell'applicazione che gestisce casi più particolari come
 * comunicazione tra views senza utilizzo del Model
 */
class ApplicationController {
 private:
  ApplicationModel *model;
  ApplicationView *view;

 public:
  ApplicationController(ApplicationModel *m = nullptr, ApplicationView *v = nullptr);
};

#endif //INKMARK_APPLICATION_CONTROLLER_H
