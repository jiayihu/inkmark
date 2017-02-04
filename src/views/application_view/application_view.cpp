#include "application_view.h"
#include <QHBoxLayout>

ApplicationView::ApplicationView(QWidget *parent): QWidget(parent) {
  setWindowTitle("Inkmark");
  setStyleSheet("background-color: #FFFFFF;");
  setMinimumSize(768, 480);

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

void ApplicationView::closeEvent(QCloseEvent *event) {
  emit applicationClosed();
  event->accept();
}
