#ifndef INKMARK_USER_APPLICATION_VIEW_H
#define INKMARK_USER_APPLICATION_VIEW_H

#include <QWidget>
#include <QVector>
#include "models/bookmark_model.h"
#include "models/user_model.h"
#include "views/users/edit_bookmark_view/edit_bookmark_view.h"
#include "views/users/search_bookmark_view/search_bookmark_view.h"
#include "views/users/bookmarks_list_view/bookmarks_list_view.h"

class UserApplicationView: public QWidget {
 Q_OBJECT

 private:
  UserInterface *user;

  EditBookmarkView *addBookmarkView;
  SearchBookmarkView *searchBookmarkView;
  BookmarksListView *bookmarksListView;
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

  EditBookmarkView* getAddBookmarkView() const;
  SearchBookmarkView* getSearchBookmarkView() const;
  BookmarksListView* getBookmarkListView() const;

  void setUser(UserInterface *user);

 signals:
  void logoutClicked();
};

#endif //INKMARK_USER_APPLICATION_VIEW_H
