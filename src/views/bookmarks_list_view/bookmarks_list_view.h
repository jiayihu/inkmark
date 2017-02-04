#ifndef INKMARK_BOOKMARKS_LIST_VIEW_H
#define INKMARK_BOOKMARKS_LIST_VIEW_H

#include <QMap>
#include <QWidget>
#include <QVBoxLayout>
#include "models/bookmark_model.h"
#include "../bookmark_view/bookmark_view.h"

class BookmarksListView: public QWidget {
  Q_OBJECT

 private:
  QVBoxLayout *layout;
  QMap<BookmarkModel*, BookmarkView*> viewsMap;

 private slots:
  /**
   * Cancella la view relativa al bookmark ed emette il signal `clickedDelete`
   */
  void handleDeleteClicked(BookmarkModel *bookmark);

 public:
  BookmarksListView();

 public slots:
  void addBookmark(BookmarkModel *bookmark);

 signals:
  void clickedDelete(BookmarkModel *bookmark);
};

#endif //INKMARK_BOOKMARKS_LIST_VIEW_H
