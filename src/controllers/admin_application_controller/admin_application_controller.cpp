#include "admin_application_controller.h"

AdminApplicationController::AdminApplicationController(ApplicationModel *m, AdminApplicationView *v)
  : model(m), view(v) {
  UsersListView *usersListView = view->getUsersListView();
  usersListController = new UsersListController(model, usersListView);

  QObject::connect(view, SIGNAL(logoutClicked()), model, SLOT(logout()));
}

AdminApplicationController::~AdminApplicationController() {
  delete usersListController;
}

