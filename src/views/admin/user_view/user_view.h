#ifndef INKMARK_USER_VIEW_H
#define INKMARK_USER_VIEW_H

#include <QWidget>
#include <QLabel>
#include "models/user_model.h"
#include "widgets/button_widget/button_widget.h"

/**
 * Classe view che mostra un singolo utente
 */
class UserView: public QWidget {
  Q_OBJECT

 private:
  UserInterface *model;
  bool isCurrentUser;

  QLabel *fullnameLabel;
  QLabel *emailLabel;
  QLabel *roleLabel;
  ButtonWidget *deleteButton;
  ButtonWidget *editButton;

  QWidget* createContent();
  QWidget* createButtons();

 private slots:
  /**
   * Emette il signal clickedDelete con il proprio model
   */
  void handleDeleteClick();
  void handleEditClick();

 public:
  UserView(QWidget *parent = nullptr);

 public slots:
  void setModel(UserInterface *newModel);
  void setIsCurrentUser(UserInterface *currentUser);

  signals:
  void clickedDelete(UserInterface*);
  void clickedEdit(UserInterface*);
};

#endif //INKMARK_USER_VIEW_H
