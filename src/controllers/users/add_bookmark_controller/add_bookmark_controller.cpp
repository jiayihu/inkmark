#include "add_bookmark_controller.h"

AddBookmarkController::AddBookmarkController(ApplicationModel *m, AddBookmarkView *v)
  : model(m), view(v) {
  QObject::connect(
    view,
    SIGNAL(submitClicked(QString, QString, QString, QString, QDate, QTime, QTime)),
    model,
    SLOT(addBookmark(QString, QString, QString, QString, QDate, QTime, QTime))
  );

  // Pulire gli input all'aggiunta con successo del bookmark
  QObject::connect(model, SIGNAL(addedBookmark(BookmarkInterface*)), view, SLOT(clear()));
}
