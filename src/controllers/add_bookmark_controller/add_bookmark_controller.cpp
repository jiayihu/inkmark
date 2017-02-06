#include "add_bookmark_controller.h"

AddBookmarkController::AddBookmarkController(ApplicationModel *m, AddBookmarkView *v)
  : model(m), view(v) {
  QObject::connect(v, SIGNAL(submitClicked(QString, QString, QString)), this, SLOT(handleSubmitClicked(QString, QString, QString)));
}

void AddBookmarkController::handleSubmitClicked(const QString &name, const QString &link, const QString &description) {
  model->addBookmark(name, link, description);
}
