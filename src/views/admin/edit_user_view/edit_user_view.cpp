#include "edit_user_view.h"
#include <QFormLayout>
#include <QLabel>
#include "widgets/button_widget/button_widget.h"
#include "utilities/utilities.h"

QWidget* EditUserView::createForm() {
  QFormLayout *layout = new QFormLayout();
  nameInput = new TextInputWidget();
  surnameInput = new TextInputWidget();
  emailInput = new TextInputWidget();
  passwordInput = new TextInputWidget();

  layout->addRow(new QLabel("Name"), nameInput);
  layout->addRow(new QLabel("Surname"), surnameInput);
  layout->addRow(new QLabel("Email"), emailInput);
  layout->addRow(new QLabel("Password"), passwordInput);

  return wrapInWidget(layout);
}

QWidget* EditUserView::createButtons() const {
  QHBoxLayout *layout = new QHBoxLayout();
  ButtonWidget *cancelButton = new ButtonWidget("Cancel");
  QObject::connect(cancelButton, SIGNAL(clicked()), this, SIGNAL(cancelClicked()));
  ButtonWidget *editButton = new ButtonWidget("Save user");
  QObject::connect(editButton, SIGNAL(clicked()), this, SLOT(handleEditClick()));
  layout->setAlignment(Qt::AlignLeft);
  layout->addWidget(cancelButton);
  layout->addWidget(editButton);
  QWidget *buttonsWidget = wrapInWidget(layout);
  buttonsWidget->setStyleSheet("border-bottom: 2px solid #e3e1e1;");

  return buttonsWidget;
}

QWidget* EditUserView::createRoleForm() {
  QFormLayout *layout = new QFormLayout();

  isAdmin = new QCheckBox("Admin");
  ButtonWidget *confirmButton = new ButtonWidget("Change role");
  QObject::connect(confirmButton, SIGNAL(clicked()), this, SLOT(handleChangeRole()));

  layout->addRow(new QLabel("Role:"), isAdmin);
  layout->addWidget(confirmButton);

  return wrapInWidget(layout);
}

void EditUserView::handleEditClick() {
  QString name = nameInput->text();
  QString surname = surnameInput->text();
  QString email = emailInput->text();
  QString password = passwordInput->text();

  emit saveClicked(model, name, surname, email, password);
}

void EditUserView::handleChangeRole() {
  bool isAdminChecked = isAdmin->isChecked();
  QString newRole = isAdminChecked ? "admin" : "user";

  emit changeRoleClicked(model, newRole);
}

EditUserView::EditUserView(QWidget *parent): QWidget(parent) {
  QVBoxLayout *layout = new QVBoxLayout();

  layout->addWidget(createForm());
  layout->addWidget(createButtons());
  layout->addWidget(createRoleForm());

  setLayout(layout);
}

void EditUserView::setModel(UserInterface *newModel) {
  model = newModel;

  nameInput->setText(model->getName());
  surnameInput->setText(model->getSurname());
  emailInput->setText(model->getEmail());
  passwordInput->setText(model->getPassword());

  isAdmin->setChecked(model->getRole() == "admin");
}

