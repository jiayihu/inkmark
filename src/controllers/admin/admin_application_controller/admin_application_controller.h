#ifndef INKMARK_ADMIN_APPLICATION_CONTROLLER_H
#define INKMARK_ADMIN_APPLICATION_CONTROLLER_H

#include "models/application_model.h"
#include "views/admin/admin_application_view/admin_application_view.h"
#include "controllers/admin/users_list_controller/users_list_controller.h"

/**
 * Controller generale dell'applicazione admin che crea i controllers delle subviews
 */
class AdminApplicationController {
 private:
  ApplicationModel *model;
  AdminApplicationView *view;

  UsersListController *usersListController;

 public:
  AdminApplicationController(ApplicationModel *m = nullptr, AdminApplicationView *v = nullptr);
  ~AdminApplicationController();
};

#endif //INKMARK_ADMIN_APPLICATION_CONTROLLER_H
