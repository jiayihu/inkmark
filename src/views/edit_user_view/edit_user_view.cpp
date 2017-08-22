#include "edit_user_view.h"
#include <QFormLayout>
#include <QLabel>
#include "widgets/button_widget/button_widget.h"
#include "utilities/utilities.h"

void EditUserView::handleEditClick() {
  QString name = nameInput->text();
  QString surname = surnameInput->text();
  QString email = emailInput->text();
  QString password = passwordInput->text();

  emit saveClicked(model, name, surname, email, password);
}

EditUserView::EditUserView(QWidget *parent): QWidget(parent) {
  QVBoxLayout *layout = new QVBoxLayout();

  QFormLayout *formLayout = new QFormLayout();
  nameInput = new TextInputWidget();
  surnameInput = new TextInputWidget();
  emailInput = new TextInputWidget();
  passwordInput = new TextInputWidget();

  formLayout->addRow(new QLabel("Name"), nameInput);
  formLayout->addRow(new QLabel("Surname"), surnameInput);
  formLayout->addRow(new QLabel("Email"), emailInput);
  formLayout->addRow(new QLabel("Password"), passwordInput);

  QHBoxLayout *buttonsLayout = new QHBoxLayout();
  ButtonWidget *cancelButton = new ButtonWidget("Cancel");
  QObject::connect(cancelButton, SIGNAL(clicked()), this, SIGNAL(cancelClicked()));
  ButtonWidget *editButton = new ButtonWidget("Save user");
  QObject::connect(editButton, SIGNAL(clicked()), this, SLOT(handleEditClick()));
  buttonsLayout->setAlignment(Qt::AlignLeft);
  buttonsLayout->addWidget(cancelButton);
  buttonsLayout->addWidget(editButton);
  QWidget *buttonsWidget = wrapInWidget(buttonsLayout);
  buttonsWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

  layout->addWidget(wrapInWidget(formLayout));
  layout->addWidget(buttonsWidget);

  setLayout(layout);
}

void EditUserView::setModel(UserInterface *newModel) {
  model = newModel;

  nameInput->setText(model->getName());
  surnameInput->setText(model->getSurname());
  emailInput->setText(model->getEmail());
  passwordInput->setText(model->getPassword());
}

