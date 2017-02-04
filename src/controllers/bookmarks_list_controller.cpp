#include <QString>
#include "bookmarks_list_controller.h"

BookmarksListController::BookmarksListController(ApplicationModel *m, BookmarksListView *v)
    : model(m), view(v) {
  /**
   * Connessioni Model => View
   */
  QObject::connect(model, SIGNAL(addedBookmark(BookmarkModel*)), view, SLOT(addBookmarkView(BookmarkModel*)));
  QObject::connect(model, SIGNAL(updatedBookmark(BookmarkModel*)), view, SLOT(updateBookmarkView(BookmarkModel*)));

  /**
   * Connessioni View => Model
   */
  QObject::connect(view, SIGNAL(clickedDelete(BookmarkModel*)), model, SLOT(deleteBookmark(BookmarkModel*)));
  QObject::connect(
      view,
      SIGNAL(editedBookmark(BookmarkModel*, QString, QString, QString)),
      model,
      SLOT(editBookmark(BookmarkModel*, QString, QString, QString))
  );

  // Il model ha già dei bookmarks
  QVector<BookmarkModel*> bookmarks = m->getBookmarks();
  if (bookmarks.size()) {
    for (int i = 0; i < bookmarks.size(); i++) view->addBookmarkView(bookmarks[i]);
  }
}
