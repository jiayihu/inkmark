#ifndef INKMARK_BOOKMARKS_LIST_VIEW_H
#define INKMARK_BOOKMARKS_LIST_VIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include "models/bookmark_model.h"

class BookmarksListView: public QWidget {
  Q_OBJECT

 private:
  QVBoxLayout *layout;

 public:
  BookmarksListView();

 public slots:
  void addBookmark(BookmarkModel *bookmark);
};

#endif //INKMARK_BOOKMARKS_LIST_VIEW_H
