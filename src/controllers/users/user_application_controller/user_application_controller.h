#ifndef INKMARK_USER_APPLICATION_CONTROLLER_H
#define INKMARK_USER_APPLICATION_CONTROLLER_H

#include "models/application_model.h"
#include "views/users/user_application_view/user_application_view.h"
#include "controllers/users/add_bookmark_controller/add_bookmark_controller.h"
#include "controllers/users/bookmarks_list_controller/bookmarks_list_controller.h"
#include "controllers/users/search_bookmark_controller/search_bookmark_controller.h"

/**
 * Controller generale dell'applicazione utente che crea i controllers delle subviews
 * e gestisce casi più particolari come comunicazione tra views
 */
class UserApplicationController {
 private:
  ApplicationModel *model;
  UserApplicationView *view;

  AddBookmarkController *addBookmarkController;
  BookmarksListController *bookmarksListController;
  SearchBookmarkController *searchBookmarkController;

 public:
  UserApplicationController(ApplicationModel *m = nullptr, UserApplicationView *v = nullptr);
  ~UserApplicationController();
};

#endif //INKMARK_USER_APPLICATION_CONTROLLER_H
