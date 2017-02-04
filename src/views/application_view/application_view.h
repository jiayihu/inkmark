#ifndef INKMARK_APPLICATION_H
#define INKMARK_APPLICATION_H

#include <QWidget>
#include <QCloseEvent>
#include "views/add_bookmark_view/add_bookmark_view.h"
#include "views/bookmarks_list_view/bookmarks_list_view.h"

class ApplicationView: public QWidget {
 Q_OBJECT

 private:
  AddBookmarkView *addBookmarkView;
  BookmarksListView *bookmarksListView;

 private slots:
  void toggleAddViewVisibility();

 public:
  ApplicationView(QWidget *parent = nullptr);
  AddBookmarkView* getAddBookmarkView() const;
  BookmarksListView* getBookmarkListView() const;
  void closeEvent(QCloseEvent *event);

  signals:
    void applicationClosed();
};

#endif //INKMARK_APPLICATION_H
