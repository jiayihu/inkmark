#include "bookmarks_list_view.h"

void BookmarksListView::handleDeleteClicked(BookmarkModel *bookmark) {
  layout->removeWidget(viewsMap[bookmark]);
  viewsMap.remove(bookmark);

  emit clickedDelete(bookmark);
}

BookmarksListView::BookmarksListView(): layout(new QVBoxLayout()) {
  layout->setAlignment(Qt::AlignTop);
  setLayout(layout);
}

void BookmarksListView::addBookmark(BookmarkModel *bookmark) {
  BookmarkView *bookmarkView = new BookmarkView(bookmark);
  viewsMap[bookmark] = bookmarkView;
  QObject::connect(bookmarkView, SIGNAL(clickedDelete(BookmarkModel*)), this, SLOT(handleDeleteClicked(BookmarkModel*)));

  layout->addWidget(bookmarkView);
}
