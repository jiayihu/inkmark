#ifndef INKMARK_USERS_LIST_CONTROLLER_H
#define INKMARK_USERS_LIST_CONTROLLER_H

#include "models/application_model.h"
#include "views/admin/users_list_view/users_list_view.h"

class UsersListController: public QObject {
 Q_OBJECT

 private:
  ApplicationModel *model;
  UsersListView *view;

 private slots:
  void setModel() const;

 public:
  UsersListController(ApplicationModel *m = nullptr, UsersListView *v = nullptr);
};

#endif //INKMARK_USERS_LIST_CONTROLLER_H
