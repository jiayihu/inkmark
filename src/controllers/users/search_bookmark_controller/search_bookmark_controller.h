#ifndef INKMARK_SEARCH_BOOKMARK_CONTROLLER_H
#define INKMARK_SEARCH_BOOKMARK_CONTROLLER_H

#include <QObject>
#include "models/application_model.h"
#include "views/users/search_bookmark_view/search_bookmark_view.h"

class SearchBookmarkController: public QObject {
 Q_OBJECT

 private:
  ApplicationModel *model;
  SearchBookmarkView *view;

 public:
  SearchBookmarkController(ApplicationModel *m, SearchBookmarkView *v);
};

#endif //INKMARK_SEARCH_BOOKMARK_CONTROLLER_H
