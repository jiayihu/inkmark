#include "add_bookmark_controller.h"

AddBookmarkController::AddBookmarkController(ApplicationModel *m, AddBookmarkView *v)
  : model(m), view(v) {
  QObject::connect(view, SIGNAL(submitClicked(QString, QString, QString)), this, SLOT(handleSubmitClicked(QString, QString, QString)));

  // Pulire gli input all'aggiunta con successo del bookmark
  QObject::connect(model, SIGNAL(addedBookmark(BookmarkInterface*)), view, SLOT(clear()));
}

void AddBookmarkController::handleSubmitClicked(const QString &name, const QString &link, const QString &description) {
  model->addBookmark(name, link, description);
}
