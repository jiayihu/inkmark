#include "users_list_view.h"
#include <QString>
#include <QScrollArea>

QString UsersListView::getStyles() const {
  return
    "QScrollBar:vertical { width: 5px; }"
      "QScrollBar::handle:vertical {"
      "background-color: #696969;"
      "}";
}

void UsersListView::clean() {
  for (int i = 0; i < model.size(); i++) {
    UserInterface *user = model[i];
    listLayout->removeWidget(viewsMap[user]);
    delete viewsMap[user];
  }

  viewsMap.clear();
  model.clear();
}

void UsersListView::handleDeleteClicked(UserInterface *user) {
  listLayout->removeWidget(viewsMap[user]);
  delete viewsMap[user];
  viewsMap.remove(user);

  emit clickedDelete(user);
}

void UsersListView::hideEditView() {
  editUserView->setVisible(false);
}

void UsersListView::handleEditClicked(UserInterface *user) {
  editUserView->setModel(user);
  editUserView->setVisible(true);
}

UsersListView::UsersListView(QWidget *parent): QWidget(parent) {
  setStyleSheet(getStyles());

  containerLayout = new QHBoxLayout();
  containerLayout->setAlignment(Qt::AlignTop);
  containerLayout->setSpacing(0);

  QWidget *listContainer = new QWidget();
  listLayout = new QVBoxLayout(listContainer);
  listLayout->setContentsMargins(0, 0, 0, 0);
  listLayout->setSpacing(0);
  listLayout->setAlignment(Qt::AlignTop);

  QScrollArea *scrollArea = new QScrollArea();
  scrollArea->setWidget(listContainer);
  scrollArea->setWidgetResizable(true);
  scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
  // UserView fixed width + 2 to avoid horizontal scroll
  scrollArea->setMinimumWidth(642);
  scrollArea->setFrameShape(QFrame::NoFrame);

  editUserView = new EditUserView();
  editUserView->setVisible(false);
  // Chiudi il widget per la modifica
  QObject::connect(editUserView, SIGNAL(saveClicked(UserInterface*, QString, QString, QString, QString)), this, SLOT(hideEditView()));
  QObject::connect(editUserView, SIGNAL(cancelClicked()), this, SLOT(hideEditView()));
  // Propaga il signal all'esterno
  QObject::connect(
    editUserView,
    SIGNAL(saveClicked(UserInterface*, QString, QString, QString, QString)),
    this,
    SIGNAL(editedUser(UserInterface*, QString, QString, QString, QString))
  );

  containerLayout->addWidget(scrollArea);
  containerLayout->addWidget(editUserView);

  setLayout(containerLayout);
}
void UsersListView::setModel(QVector<UserInterface *> newModel) {
  if (!model.empty()) clean();

  model = newModel;
  for (int i = 0; i < model.size(); i++) addUserView(model[i]);
}

void UsersListView::addUserView(UserInterface *user) {
  UserView *userView = new UserView();
  userView->setModel(user);
  viewsMap[user] = userView;
  QObject::connect(userView, SIGNAL(clickedDelete(UserInterface*)), this, SLOT(handleDeleteClicked(UserInterface*)));
  QObject::connect(userView, SIGNAL(clickedEdit(UserInterface*)), this, SLOT(handleEditClicked(UserInterface*)));

  listLayout->addWidget(userView);
}

void UsersListView::updateUserView(UserInterface *user) {
  UserView *userView = viewsMap[user];
  userView->setModel(user);
}
