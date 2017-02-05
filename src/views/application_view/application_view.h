#ifndef INKMARK_APPLICATION_H
#define INKMARK_APPLICATION_H

#include <QWidget>
#include <QVector>
#include <QCloseEvent>
#include <QHBoxLayout>
#include "models/bookmark_model.h"
#include "views/add_bookmark_view/add_bookmark_view.h"
#include "views/search_bookmark_view/search_bookmark_view.h"
#include "views/bookmarks_list_view/bookmarks_list_view.h"

class ApplicationView: public QWidget {
 Q_OBJECT

 private:
  AddBookmarkView *addBookmarkView;
  SearchBookmarkView *searchBookmarkView;
  BookmarksListView *bookmarksListView;

  QString getApplicationStyles() const;
  QString getMenuStyle() const;
  QVBoxLayout *createAppLayout() const;
  QWidget *createMenu() const;
  QWidget *createContent();

 private slots:
  void toggleSearchViewVisibility();
  void toggleAddViewVisibility();
  void resizeToMin();

 public:
  ApplicationView(QWidget *parent = nullptr);

  AddBookmarkView* getAddBookmarkView() const;
  SearchBookmarkView* getSearchBookmarkView() const;
  BookmarksListView* getBookmarkListView() const;

  void closeEvent(QCloseEvent *event);

  signals:
    void applicationClosed();
};

#endif //INKMARK_APPLICATION_H
