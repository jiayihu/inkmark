#include "add_bookmark_controller.h"

AddBookmarkController::AddBookmarkController(ApplicationModel *m, AddBookmarkView *v)
  : model(m), view(v) {
  QObject::connect(v, SIGNAL(submitClicked(QString, QString, QString)), this, SLOT(handleSubmitClicked(QString, QString, QString)));
}

void AddBookmarkController::handleSubmitClicked(QString name, QString link, QString description) {
  BookmarkModel *bookmark = new BookmarkModel(link, name, description);
  model->addBookmark(bookmark);
}
