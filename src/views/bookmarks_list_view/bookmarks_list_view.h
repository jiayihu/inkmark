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
  QVector<BookmarkInterface*> model;
  QHBoxLayout *containerLayout;
  QVBoxLayout *listLayout;
  EditBookmarkView *editBookmarkView;
  QMap<BookmarkInterface*, BookmarkView*> viewsMap;

  QString getStyles() const;
  void clean();

 private slots:
  /**
   * Cancella la view relativa al bookmark ed emette il signal `clickedDelete`
   */
  void handleDeleteClicked(BookmarkInterface *bookmark);
  void handleEditClicked(BookmarkInterface *bookmark);
  void hideEditView();

 public:
  BookmarksListView(QWidget *parent = nullptr);

 public slots:
  void setModel(const QVector<BookmarkInterface *> &newModel);
  void addBookmarkView(BookmarkInterface *bookmark);
  void updateBookmarkView(BookmarkInterface *bookmark);

 signals:
  void clickedDelete(BookmarkInterface *bookmark);
  void editedBookmark(BookmarkInterface *bookmark, QString newName, QString newLink, QString newDesc);
};

#endif //INKMARK_BOOKMARKS_LIST_VIEW_H
