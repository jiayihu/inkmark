#include "users_list_controller.h"

void UsersListController::setModel() const {
  view->setModel(model->getUsers());
}

UsersListController::UsersListController(ApplicationModel *m, UsersListView *v)
  : model(m), view(v) {
  /**
   * Connessioni Model => View
   */
  QObject::connect(model, SIGNAL(deletedUser(UserInterface*)), view, SLOT(deleteUserView(UserInterface*)));
  QObject::connect(model, SIGNAL(updatedUser(UserInterface*)), view, SLOT(updateUserView(UserInterface*)));
  QObject::connect(
    model,
    SIGNAL(changedUserRole(UserInterface*, UserInterface*)),
    view,
    SLOT(updateUserRole(UserInterface*, UserInterface*))
  );
  QObject::connect(model, SIGNAL(registeredUser(UserInterface*)), this, SLOT(setModel()));

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
  QObject::connect(view, SIGNAL(changedUserRole(UserInterface*, QString)), model, SLOT(changeUserRole(UserInterface*, QString)));

  // Setta il model iniziale
  setModel();
}
