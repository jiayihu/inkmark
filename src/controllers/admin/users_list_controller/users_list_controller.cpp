#include "users_list_controller.h"
#include <QString>

UsersListController::UsersListController(ApplicationModel *m, UsersListView *v)
  : model(m), view(v) {
  /**
   * Connessioni Model => View
   */
  QObject::connect(model, SIGNAL(updatedUser(UserInterface*)), view, SLOT(updateUserView(UserInterface*)));

  /**
   * Connessioni View => Model
   */
  QObject::connect(view, SIGNAL(clickedDelete(UserInterface*)), model, SLOT(deleteUser(UserInterface*)));
  QObject::connect(
    view,
    SIGNAL(editedUser(UserInterface*, QString, QString, QString, QString)),
    model,
    SLOT(editUser(UserInterface*, QString, QString, QString, QString))
  );

  // Setta il model iniziale
  view->setModel(model->getUsers());
}
