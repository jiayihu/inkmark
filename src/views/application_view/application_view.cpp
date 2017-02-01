#include "application_view.h"
#include <QHBoxLayout>

ApplicationView::ApplicationView(QWidget *parent): QWidget(parent) {
  setWindowTitle("Inkmark");

  QHBoxLayout *twoColumns = new QHBoxLayout;
  addBookmarkView = new AddBookmarkView;
  bookmarksListView = new BookmarksListView;

  twoColumns->addWidget(addBookmarkView);
  twoColumns->addWidget(bookmarksListView);

  setLayout(twoColumns);
}

AddBookmarkView* ApplicationView::getAddBookmarkView() const {
  return addBookmarkView;
}

BookmarksListView* ApplicationView::getBookmarkListView() const {
  return bookmarksListView;
}
