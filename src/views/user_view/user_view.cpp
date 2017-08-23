#include <QVBoxLayout>
#include "user_view.h"

QWidget* UserView::createContent() {
  QWidget *contentContainer = new QWidget();
  QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  sizePolicy.setHorizontalStretch(1);
  contentContainer->setSizePolicy(sizePolicy);

  QHBoxLayout *layout = new QHBoxLayout(contentContainer);

  fullnameLabel = new QLabel();
  emailLabel = new QLabel();
  emailLabel->setStyleSheet("font-size: 14px; color: #999;");
  roleLabel = new QLabel();
  roleLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  roleLabel->setStyleSheet(
    "background-color: #999; border-radius: 3px; font-size: 14px; color: #fff; padding: 3px;"
  );

  layout->addWidget(fullnameLabel);
  layout->addWidget(emailLabel);
  layout->addWidget(roleLabel);

  return contentContainer;
}

QWidget* UserView::createButtons() {
  QWidget *buttonsContainer = new QWidget();
  QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  sizePolicy.setHorizontalStretch(0);
  buttonsContainer->setSizePolicy(sizePolicy);

  QHBoxLayout *layout = new QHBoxLayout(buttonsContainer);

  deleteButton = new ButtonWidget("Delete");
  QObject::connect(deleteButton, SIGNAL(clicked()), this, SLOT(handleDeleteClick()));
  editButton = new ButtonWidget("Edit");
  QObject::connect(editButton, SIGNAL(clicked()), this, SLOT(handleEditClick()));

  layout->addWidget(deleteButton);
  layout->addWidget(editButton);

  return buttonsContainer;
}

void UserView::handleDeleteClick() { emit clickedDelete(model); }

void UserView::handleEditClick() { emit clickedEdit(model); }

UserView::UserView(QWidget *parent): model(nullptr), QWidget(parent) {
  setFixedWidth(640);
  setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

  QHBoxLayout *layout = new QHBoxLayout();

  QWidget *contentContainer = createContent();
  QWidget *buttonsContainer = createButtons();

  layout->addWidget(contentContainer);
  layout->addWidget(buttonsContainer);

  setLayout(layout);
}
void UserView::setModel(UserInterface *newModel) {
  model = newModel;

  fullnameLabel->setText(model->getName() + " " + model->getSurname());
  emailLabel->setText(model->getEmail());
  roleLabel->setText(model->getRole());
}
