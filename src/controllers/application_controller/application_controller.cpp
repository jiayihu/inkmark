#include "application_controller.h"

ApplicationController::ApplicationController(ApplicationModel *m, ApplicationView *v)
  : model(m), view(v) {

  UserApplicationView *userApplicationView = view->getUserApplicationView();
  userApplicationController = new UserApplicationController(model, userApplicationView);
}

ApplicationController::~ApplicationController() {
  delete userApplicationController;
}
