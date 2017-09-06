#ifndef INKMARK_USERS_LIST_VIEW_H
#define INKMARK_USERS_LIST_VIEW_H

#include <QWidget>
#include <QLayout>
#include <QMap>
#include "models/user_model.h"
#include "views/admin/user_view/user_view.h"
#include "views/admin/edit_user_view/edit_user_view.h"

class UsersListView: public QWidget {
 Q_OBJECT

 private:
  QVector<UserInterface*> model;

  QLayout *containerLayout;
  QLayout *listLayout;
  EditUserView *editUserView;

  /**
   * Mappa utilizzata per tenere traccia di quali views sono mostrate, ove la chiave
   * è il puntatore al user. Tempi di modifica/delete più efficienti rispetto
   * ad un vector
   */
  QMap<UserInterface*, UserView*> viewsMap;

  QString getStyles() const;
  void clean();

 private slots:
  void handleEditClicked(UserInterface *user);
  void hideEditView();

 public:
  UsersListView(QWidget *parent = nullptr);

  void setPrivilegies(UserInterface *currentUser) const;

 public slots:
  void setModel(QVector<UserInterface *> newModel);
  void addUserView(UserInterface *user);
  void deleteUserView(UserInterface *user);
  void updateUserView(UserInterface *user);
  void updateUserRole(UserInterface *oldUser, UserInterface *newUser);

 signals:
  void clickedDelete(UserInterface *user);
  void editedUser(UserInterface *user,
                  const QString &newName,
                  const QString &newSurname,
                  const QString &newEmail,
                  const QString &newPwd);
  void changedUserRole(UserInterface *user, QString newRole);
};

#endif //INKMARK_USERS_LIST_VIEW_H
