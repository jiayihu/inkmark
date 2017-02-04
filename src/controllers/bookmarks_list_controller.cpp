#include "bookmarks_list_controller.h"

BookmarksListController::BookmarksListController(ApplicationModel *m, BookmarksListView *v)
    : model(m), view(v) {
  QObject::connect(model, SIGNAL(addedBookmark(BookmarkModel*)), view, SLOT(addBookmark(BookmarkModel*)));
  QObject::connect(view, SIGNAL(clickedDelete(BookmarkModel*)), model, SLOT(deleteBookmark(BookmarkModel*)));

  // Il model ha già dei bookmarks
  QVector<BookmarkModel*> bookmarks = m->getBookmarks();
  if (bookmarks.size()) {
    for (int i = 0; i < bookmarks.size(); i++) view->addBookmark(bookmarks[i]);
  }
}
