#ifndef INKMARK_ADD_BOOKMARK_CONTROLLER_H
#define INKMARK_ADD_BOOKMARK_CONTROLLER_H

#include <QString>
#include "models/application_model.h"
#include "views/users/add_bookmark_view/add_bookmark_view.h"

class AddBookmarkController: public QObject {
  Q_OBJECT

 private:
  ApplicationModel *model;
  AddBookmarkView *view;

 private slots:
  void handleSubmitClicked(const QString &name, const QString &link, const QString &description);

 public:
  AddBookmarkController(ApplicationModel *m = nullptr, AddBookmarkView *v = nullptr);
};

#endif //INKMARK_ADD_BOOKMARK_CONTROLLER_H
