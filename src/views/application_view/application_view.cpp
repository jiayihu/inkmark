#include <QPushButton>
#include "application_view.h"

void ApplicationView::toggleAddViewVisibility() {
  if (searchBookmarkView->isVisible()) searchBookmarkView->setVisible(false);

  bool visibility = addBookmarkView->isVisible();
  addBookmarkView->setVisible(!visibility);
}

void ApplicationView::toggleSearchViewVisibility() {
  if (addBookmarkView->isVisible()) addBookmarkView->setVisible(false);

  bool visibility = searchBookmarkView->isVisible();
  searchBookmarkView->setVisible(!visibility);
}

ApplicationView::ApplicationView(QWidget *parent): QWidget(parent) {
  setWindowTitle("Inkmark");
  setStyleSheet("background-color: #FFFFFF;");
  setMinimumSize(768, 480);

  QVBoxLayout *containerLayout = new QVBoxLayout();

  QHBoxLayout *menuLayout = new QHBoxLayout();
  ButtonWidget *addBookmarkButton = new ButtonWidget("Add bookmark");
  QObject::connect(addBookmarkButton, SIGNAL(clicked()), this, SLOT(toggleAddViewVisibility()));
  ButtonWidget *searchButton = new ButtonWidget("Search bookmark");
  QObject::connect(searchButton, SIGNAL(clicked()), this, SLOT(toggleSearchViewVisibility()));
  menuLayout->addWidget(addBookmarkButton);
  menuLayout->addWidget(searchButton);

  QHBoxLayout *contentLayout = new QHBoxLayout();

  addBookmarkView = new AddBookmarkView;
  addBookmarkView->setVisible(false);
  QObject::connect(addBookmarkView, SIGNAL(submitClicked(QString, QString, QString)), this, SLOT(toggleAddViewVisibility()));

  searchBookmarkView = new SearchBookmarkView;
  searchBookmarkView->setVisible(false);
  QObject::connect(searchBookmarkView, SIGNAL(clickedCancel()), this, SLOT(toggleSearchViewVisibility()));

  bookmarksListView = new BookmarksListView;
  contentLayout->addWidget(addBookmarkView);
  contentLayout->addWidget(searchBookmarkView);
  contentLayout->addWidget(bookmarksListView);

  containerLayout->addLayout(menuLayout);
  containerLayout->addLayout(contentLayout);

  setLayout(containerLayout);
}

AddBookmarkView* ApplicationView::getAddBookmarkView() const {
  return addBookmarkView;
}

BookmarksListView* ApplicationView::getBookmarkListView() const {
  return bookmarksListView;
}

SearchBookmarkView* ApplicationView::getSearchBookmarkView() const {
  return searchBookmarkView;
}

void ApplicationView::closeEvent(QCloseEvent *event) {
  emit applicationClosed();
  event->accept();
}
