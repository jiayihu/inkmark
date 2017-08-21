#include "application_controller.h"

ApplicationController::ApplicationController(ApplicationModel *m, ApplicationView *v)
  : model(m), view(v) {

  AuthView *authView = view->getAuthView();
  authController = new AuthController(model, authView);

  UserApplicationView *userApplicationView = view->getUserApplicationView();
  userApplicationController = new UserApplicationController(model, userApplicationView);

  // Model => View
  QObject::connect(model, SIGNAL(loggedIn(UserInterface*)), view, SLOT(setUser(UserInterface*)));
  QObject::connect(model, SIGNAL(loggedOut()), view, SLOT(removeUser()));
}

ApplicationController::~ApplicationController() {
  delete authController;
  delete userApplicationController;
}
