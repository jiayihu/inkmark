#include "application_controller.h"

ApplicationController::ApplicationController(ApplicationModel *m, ApplicationView *v)
  : model(m), view(v) {

  AuthView *authView = view->getAuthView();
  authController = new AuthController(model, authView);

  AdminApplicationView *adminApplicationView = view->getAdminApplicationView();
  adminApplicationController = new AdminApplicationController(model, adminApplicationView);

  UserApplicationView *userApplicationView = view->getUserApplicationView();
  userApplicationController = new UserApplicationController(model, userApplicationView);

  // Model => View
  QObject::connect(model, SIGNAL(hadUserError(QString)), view, SLOT(showError(QString)));
  QObject::connect(model, SIGNAL(loggedInUser(UserInterface*)), view, SLOT(showUserArea(UserInterface*)));
  QObject::connect(model, SIGNAL(loggedInAdmin(UserInterface*)), view, SLOT(showAdminArea(UserInterface*)));
  QObject::connect(model, SIGNAL(loggedOut()), view, SLOT(hideContainerArea()));
}

ApplicationController::~ApplicationController() {
  delete authController;
  delete adminApplicationController;
  delete userApplicationController;
}
