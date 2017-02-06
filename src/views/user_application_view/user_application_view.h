#ifndef INKMARK_USER_APPLICATION_VIEW_H
#define INKMARK_USER_APPLICATION_VIEW_H

#include <QWidget>
#include <QVector>
#include <QCloseEvent>
#include <QHBoxLayout>
#include "models/bookmark_model.h"
#include "views/add_bookmark_view/add_bookmark_view.h"
#include "views/search_bookmark_view/search_bookmark_view.h"
#include "views/bookmarks_list_view/bookmarks_list_view.h"

class UserApplicationView: public QWidget {
 Q_OBJECT

 private:
  AddBookmarkView *addBookmarkView;
  SearchBookmarkView *searchBookmarkView;
  BookmarksListView *bookmarksListView;

 private slots:
  void toggleSearchViewVisibility();
  void toggleAddViewVisibility();
  void resizeToMin();

 public:
  UserApplicationView(QWidget *parent = nullptr);

  QLayout *createMenu(QWidget *parent = nullptr) const;
  QLayout *createContent(QWidget *parent = nullptr);

  AddBookmarkView* getAddBookmarkView() const;
  SearchBookmarkView* getSearchBookmarkView() const;
  BookmarksListView* getBookmarkListView() const;
};

#endif //INKMARK_USER_APPLICATION_VIEW_H
