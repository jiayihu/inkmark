#ifndef INKMARK_USER_APPLICATION_VIEW_H
#define INKMARK_USER_APPLICATION_VIEW_H

#include <QWidget>
#include <QVector>
#include <QHBoxLayout>
#include "models/bookmark_model.h"
#include "models/user_model.h"
#include "views/add_bookmark_view/add_bookmark_view.h"
#include "views/search_bookmark_view/search_bookmark_view.h"
#include "views/bookmarks_list_view/bookmarks_list_view.h"

class UserApplicationView: public QWidget {
 Q_OBJECT

 private:
  AddBookmarkView *addBookmarkView;
  SearchBookmarkView *searchBookmarkView;
  BookmarksListView *bookmarksListView;
  UserInterface *user;
  QLabel *username;

  ButtonWidget *addBookmarkButton;

  void resizeToMin();

 private slots:
  void toggleSearchViewVisibility();
  void toggleAddViewVisibility();

 public:
  UserApplicationView(QWidget *parent = nullptr);

  // Ritorna il menu dell'area utente
  QWidget *createMenu();
  // Ritorna il contenuto dell'area utente
  QWidget *createContent();

  AddBookmarkView* getAddBookmarkView() const;
  SearchBookmarkView* getSearchBookmarkView() const;
  BookmarksListView* getBookmarkListView() const;

  void setUser(UserInterface *user);

 signals:
  void logoutClicked();
};

#endif //INKMARK_USER_APPLICATION_VIEW_H
