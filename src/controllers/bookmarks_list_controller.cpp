#include "bookmarks_list_controller.h"

BookmarksListController::BookmarksListController(ApplicationModel *m, BookmarksListView *v)
    : model(m), view(v) {
  QObject::connect(model, SIGNAL(addedBookmark(BookmarkModel*)), this, SLOT(handleAddedBookmark(BookmarkModel*)));

  // Il model ha già dei bookmarks
  QVector<BookmarkModel*> bookmarks = m->getBookmarks();
  if (bookmarks.size()) {
    for (int i = 0; i < bookmarks.size(); i++) view->addBookmark(bookmarks[i]);
  }
}

void BookmarksListController::handleAddedBookmark(BookmarkModel *bookmark) {
  view->addBookmark(bookmark);
}
