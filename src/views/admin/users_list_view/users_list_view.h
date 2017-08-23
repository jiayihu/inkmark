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
   * è il puntatore al bookmark. Tempi di modifica/delete più efficienti rispetto
   * ad un vector
   */
  QMap<UserInterface*, UserView*> viewsMap;

  QString getStyles() const;
  void clean();

 private slots:
  void handleDeleteClicked(UserInterface *bookmark);
  void handleEditClicked(UserInterface *bookmark);
  void hideEditView();

 public:
  UsersListView(QWidget *parent = nullptr);

  void setPrivilegies(UserInterface *currentUser) const;

 public slots:
  void setModel(QVector<UserInterface *> newModel);
  void addUserView(UserInterface *user);
  void updateUserView(UserInterface *bookmark);

 signals:
  void clickedDelete(UserInterface *bookmark);
  void editedUser(UserInterface *bookmark,
                  const QString &newName,
                  const QString &newSurname,
                  const QString &newEmail,
                  const QString &newPwd);
};

#endif //INKMARK_USERS_LIST_VIEW_H
