#include <QString>
#include "bookmarks_list_controller.h"

void BookmarksListController::handleFinishedSearch(const QVector<BookmarkInterface *> &results) {
  view->setModel(results);
}

BookmarksListController::BookmarksListController(ApplicationModel *m, BookmarksListView *v)
    : model(m), view(v) {
  /**
   * Connessioni Model => View
   */
  QObject::connect(model, SIGNAL(addedBookmark(BookmarkInterface*)), view, SLOT(addBookmarkView(BookmarkInterface*)));
  QObject::connect(model, SIGNAL(updatedBookmark(BookmarkInterface*)), view, SLOT(updateBookmarkView(BookmarkInterface*)));
  QObject::connect(model, SIGNAL(finishedSearch(QVector<BookmarkInterface*>)), this, SLOT(handleFinishedSearch(QVector<BookmarkInterface*>)));

  /**
   * Connessioni View => Model
   */
  QObject::connect(view, SIGNAL(clickedDelete(BookmarkInterface*)), model, SLOT(deleteBookmark(BookmarkInterface*)));
  QObject::connect(
      view,
      SIGNAL(editedBookmark(BookmarkInterface*, QString, QString, QString)),
      model,
      SLOT(editBookmark(BookmarkInterface*, QString, QString, QString))
  );

  // Setta il model iniziale
  view->setModel(model->getBookmarks());
}
