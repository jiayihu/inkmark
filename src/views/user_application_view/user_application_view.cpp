#include <QSizePolicy>
#include <QDebug>
#include <QTimer>
#include "user_application_view.h"


QLayout* UserApplicationView::createMenu(QWidget *parent) const {
  QHBoxLayout *menuLayout = new QHBoxLayout(parent);
  menuLayout->setAlignment(Qt::AlignLeft);

  ButtonWidget *addBookmarkButton = new ButtonWidget("Add bookmark");
  QObject::connect(addBookmarkButton, SIGNAL(clicked()), this, SLOT(toggleAddViewVisibility()));

  ButtonWidget *searchButton = new ButtonWidget("Search bookmark");
  QObject::connect(searchButton, SIGNAL(clicked()), this, SLOT(toggleSearchViewVisibility()));

  menuLayout->addWidget(addBookmarkButton);
  menuLayout->addWidget(searchButton);

  return menuLayout;
}

QLayout* UserApplicationView::createContent(QWidget *parent) {
  QHBoxLayout *contentLayout = new QHBoxLayout(parent);

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
  QTimer::singleShot(0, this, SLOT(resizeToMin()));
}

void UserApplicationView::toggleSearchViewVisibility() {
  if (addBookmarkView->isVisible()) addBookmarkView->setVisible(false);

  bool visibility = searchBookmarkView->isVisible();
  searchBookmarkView->setVisible(!visibility);
  QTimer::singleShot(0, this, SLOT(resizeToMin()));
}

void UserApplicationView::resizeToMin() { adjustSize(); }

UserApplicationView::UserApplicationView(QWidget *parent)
  : QWidget(parent), addBookmarkView(nullptr), bookmarksListView(nullptr), searchBookmarkView(nullptr) {}

AddBookmarkView* UserApplicationView::getAddBookmarkView() const { return addBookmarkView; }

BookmarksListView* UserApplicationView::getBookmarkListView() const { return bookmarksListView; }

SearchBookmarkView* UserApplicationView::getSearchBookmarkView() const { return searchBookmarkView; }
