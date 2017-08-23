#include <QDebug>
#include "admin_application_view.h"
#include "utilities/utilities.h"

QWidget* AdminApplicationView::createMenu() {
  QHBoxLayout *layout = new QHBoxLayout();
  layout->setAlignment(Qt::AlignLeft);

  QLabel *title = new QLabel("Admin area 👮");
  title->setStyleSheet("background-color: transparent; color: #ffffff; font-size: 18px;");

  username = new QLabel();
  username->setStyleSheet("background-color: transparent; color: #ffffff;");
  username->setVisible(false);

  ButtonWidget *logoutButton = new ButtonWidget("Logout");
  QObject::connect(logoutButton, SIGNAL(clicked()), this, SIGNAL(logoutClicked()));

  layout->addWidget(title);
  layout->addWidget(createSpacer());
  layout->addWidget(username);
  layout->addWidget(logoutButton);

  QWidget *wrapper = wrapInWidget(layout);
  wrapper->setStyleSheet("background-color: #A0402A;");

  return wrapper;
}

QWidget* AdminApplicationView::createContent() {
  usersListView = new UsersListView();
  return usersListView;
}

AdminApplicationView::AdminApplicationView(QWidget *parent): QWidget(parent) {}

UsersListView* AdminApplicationView::getUsersListView() const { return usersListView; }

void AdminApplicationView::setUser(UserInterface *u) {
  user = u;

  if (user) {
    username->setText(user->getName() + " " + user->getSurname());
    username->setVisible(true);
  } else {
    username->clear();
    username->setVisible(false);
  }
}
