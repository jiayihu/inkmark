#ifndef INKMARK_BOOKMARKS_LIST_CONTROLLER_H
#define INKMARK_BOOKMARKS_LIST_CONTROLLER_H

#include "models/application_model.h"
#include "views/bookmarks_list_view/bookmarks_list_view.h"

class BookmarksListController: public QObject {
  Q_OBJECT

 private:
  ApplicationModel *model;
  BookmarksListView *view;

 private slots:
  void handleFinishedSearch(const QVector<BookmarkInterface *> &results);

 public:
  BookmarksListController(ApplicationModel *m = nullptr, BookmarksListView *v = nullptr);
};

#endif //INKMARK_BOOKMARKS_LIST_CONTROLLER_H
