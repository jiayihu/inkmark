#ifndef INKMARK_BOOKMARKS_LIST_VIEW_H
#define INKMARK_BOOKMARKS_LIST_VIEW_H

#include <QMap>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "models/bookmark_model.h"
#include "views/bookmark_view/bookmark_view.h"
#include "views/edit_bookmark_view/edit_bookmark_view.h"

class BookmarksListView: public QWidget {
  Q_OBJECT

 private:
  QHBoxLayout *containerLayout;
  QVBoxLayout *listLayout;
  EditBookmarkView *editBookmarkView;
  QMap<BookmarkModel*, BookmarkView*> viewsMap;

 private slots:
  /**
   * Cancella la view relativa al bookmark ed emette il signal `clickedDelete`
   */
  void handleDeleteClicked(BookmarkModel *bookmark);
  void handleEditClicked(BookmarkModel *bookmark);
  void handleSaveClicked();

 public:
  BookmarksListView();

 public slots:
  void addBookmarkView(BookmarkModel *bookmark);
  void updateBookmarkView(BookmarkModel *bookmark);

 signals:
  void clickedDelete(BookmarkModel *bookmark);
  void editedBookmark(BookmarkModel *bookmark, QString newName, QString newLink, QString newDesc);
};

#endif //INKMARK_BOOKMARKS_LIST_VIEW_H
