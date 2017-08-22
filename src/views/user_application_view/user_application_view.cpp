#include <QSizePolicy>
#include <QDebug>
#include <QTimer>
#include "user_application_view.h"
#include "utilities/utilities.h"

QLayout* UserApplicationView::createMenu(QWidget *parent) {
  QHBoxLayout *menuLayout = new QHBoxLayout(parent);
  menuLayout->setAlignment(Qt::AlignLeft);

  addBookmarkButton = new ButtonWidget("Add bookmark");
  QObject::connect(addBookmarkButton, SIGNAL(clicked()), this, SLOT(toggleAddViewVisibility()));

  ButtonWidget *searchButton = new ButtonWidget("Search bookmark");
  QObject::connect(searchButton, SIGNAL(clicked()), this, SLOT(toggleSearchViewVisibility()));

  ButtonWidget *logoutButton = new ButtonWidget("Logout");
  QObject::connect(logoutButton, SIGNAL(clicked()), this, SIGNAL(logoutClicked()));

  username = new QLabel();
  username->setStyleSheet("background-color: transparent; color: #ffffff;");
  username->setVisible(false);

  menuLayout->addWidget(addBookmarkButton);
  menuLayout->addWidget(searchButton);
  menuLayout->addWidget(logoutButton);
  menuLayout->addWidget(createSpacer());
  menuLayout->addWidget(username);

  return menuLayout;
}

QLayout* UserApplicationView::createContent(QWidget *parent) {
  QHBoxLayout *contentLayout = new QHBoxLayout(parent);
  contentLayout->setContentsMargins(0, 0, 0, 0);

  addBookmarkView = new AddBookmarkView();
  addBookmarkView->setVisible(false);
  QObject::connect(addBookmarkView, SIGNAL(cancelClicked()), this, SLOT(toggleAddViewVisibility()));
  QObject::connect(addBookmarkView, SIGNAL(submitClicked(QString, QString, QString)), this, SLOT(toggleAddViewVisibility()));

  searchBookmarkView = new SearchBookmarkView();
  searchBookmarkView->setVisible(false);
  QObject::connect(searchBookmarkView, SIGNAL(clickedCancel()), this, SLOT(toggleSearchViewVisibility()));

  bookmarksListView = new BookmarksListView();
  contentLayout->addWidget(addBookmarkView);
  contentLayout->addWidget(searchBookmarkView);
  contentLayout->addWidget(bookmarksListView);

  return contentLayout;
}

void UserApplicationView::toggleAddViewVisibility() {
  if (searchBookmarkView->isVisible()) searchBookmarkView->setVisible(false);

  bool visibility = addBookmarkView->isVisible();
  addBookmarkView->setVisible(!visibility);
  resizeToMin();
}

void UserApplicationView::toggleSearchViewVisibility() {
  if (addBookmarkView->isVisible()) addBookmarkView->setVisible(false);

  bool visibility = searchBookmarkView->isVisible();
  searchBookmarkView->setVisible(!visibility);
  resizeToMin();
}

void UserApplicationView::resizeToMin() {
  // Ridimensiona la finestra appena i widget sono stabili. Uso di lamda invece
  // che di SLOT per evitare nuovo metodo
  QTimer::singleShot(0, this, [&]() {
    adjustSize();
  });
}

// Inizializza le sotto-views dell'area utente. Il loro parent è nullptr perché
// saranno aggiunge al layout in `createContent`
UserApplicationView::UserApplicationView(QWidget *parent)
  : QWidget(parent), addBookmarkView(nullptr), bookmarksListView(nullptr), searchBookmarkView(nullptr) {}

AddBookmarkView* UserApplicationView::getAddBookmarkView() const { return addBookmarkView; }

BookmarksListView* UserApplicationView::getBookmarkListView() const { return bookmarksListView; }

SearchBookmarkView* UserApplicationView::getSearchBookmarkView() const { return searchBookmarkView; }

void UserApplicationView::setUser(UserInterface *u) {
  user = u;

  if (user) {
    addBookmarkButton->setVisible(user->canAdd());
    bookmarksListView->setPrivilegies(user);
    username->setText(user->getName() + " " + user->getSurname());
    username->setVisible(true);
  } else {
    addBookmarkButton->setVisible(false);
    bookmarksListView->setPrivilegies(user);
    username->clear();
    username->setVisible(false);
  }
}
