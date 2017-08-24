#include "add_bookmark_controller.h"

AddBookmarkController::AddBookmarkController(ApplicationModel *m, EditBookmarkView *v)
  : model(m), view(v) {
  QObject::connect(
    view,
    SIGNAL(addClicked(QString, QString, QString, BookmarkType, QDate, QTime, QTime)),
    model,
    SLOT(addBookmark(QString, QString, QString, BookmarkType, QDate, QTime, QTime))
  );

  // Pulire gli input all'aggiunta con successo del bookmark
  QObject::connect(model, SIGNAL(addedBookmark(BookmarkInterface*)), view, SLOT(clear()));
}
