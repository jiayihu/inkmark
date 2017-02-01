#include "bookmarks_list_controller.h"

BookmarksListController::BookmarksListController(ApplicationModel *m, BookmarksListView *v)
    : model(m), view(v) {
  QObject::connect(model, SIGNAL(addedBookmark(BookmarkModel*)), this, SLOT(handleAddedBookmark(BookmarkModel*)));
}

void BookmarksListController::handleAddedBookmark(BookmarkModel *bookmark) {
  view->addBookmark(bookmark);
}
