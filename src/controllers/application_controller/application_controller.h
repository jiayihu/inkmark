#ifndef INKMARK_APPLICATION_CONTROLLER_H
#define INKMARK_APPLICATION_CONTROLLER_H

#include "models/application_model.h"
#include "views/application_view/application_view.h"

class ApplicationController {
 private:
  ApplicationModel *model;
  ApplicationView *view;

 public:
  ApplicationController(ApplicationModel *m = nullptr, ApplicationView *v = nullptr);
};

#endif //INKMARK_APPLICATION_CONTROLLER_H
