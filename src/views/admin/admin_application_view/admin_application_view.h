#ifndef INKMARK_ADMIN_APPLICATION_VIEW_H
#define INKMARK_ADMIN_APPLICATION_VIEW_H

#include <QWidget>
#include <QVector>
#include <QLabel>
#include "models/user_model.h"
#include "widgets/button_widget/button_widget.h"
#include "views/admin/users_list_view/users_list_view.h"

class AdminApplicationView: public QWidget {
  Q_OBJECT

 private:
  UsersListView *usersListView;
  UserInterface *user;
  QLabel *username;

 public:
  AdminApplicationView(QWidget *parent = nullptr);

  // Ritorna il menu dell'area admin
  QWidget *createMenu();
  // Ritorna il contenuto dell'area admin
  QWidget *createContent();

  UsersListView* getUsersListView() const;

  void setUser(UserInterface *user);

  signals:
   void logoutClicked();
};

#endif //INKMARK_ADMIN_APPLICATION_VIEW_H
