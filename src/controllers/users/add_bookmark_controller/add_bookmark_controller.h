#ifndef INKMARK_ADD_BOOKMARK_CONTROLLER_H
#define INKMARK_ADD_BOOKMARK_CONTROLLER_H

#include <QString>
#include "models/application_model.h"
#include "views/users/edit_bookmark_view/edit_bookmark_view.h"

class AddBookmarkController: public QObject {
  Q_OBJECT

 private:
  ApplicationModel *model;
  EditBookmarkView *view;

 public:
  AddBookmarkController(ApplicationModel *m = nullptr, EditBookmarkView *v = nullptr);
};

#endif //INKMARK_ADD_BOOKMARK_CONTROLLER_H
