#ifndef INKMARK_EDIT_USER_VIEW_H
#define INKMARK_EDIT_USER_VIEW_H

#include <QWidget>
#include "models/user_model.h"
#include "widgets/text_input_widget/text_input_widget.h"
#include "widgets/text_area_widget/text_area_widget.h"

class EditUserView: public QWidget {
 Q_OBJECT

 private:
  UserInterface *model;
  TextInputWidget *nameInput;
  TextInputWidget *surnameInput;
  TextInputWidget *emailInput;
  TextInputWidget *passwordInput;

 private slots:
  void handleEditClick();

 public:
  EditUserView(QWidget *parent = nullptr);

 public slots:
  void setModel(UserInterface *newModel);

 signals:
  void saveClicked(
    UserInterface *model,
    const QString &newName,
    const QString &newSurname,
    const QString &newEmail,
    const QString &newPassword);
  void cancelClicked();
};

#endif //INKMARK_EDIT_USER_VIEW_H
