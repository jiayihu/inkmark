#ifndef INKMARK_BOOKMARKS_LIST_VIEW_H
#define INKMARK_BOOKMARKS_LIST_VIEW_H

#include <QMap>
#include <QWidget>
#include <QLayout>
#include "models/bookmark_model.h"
#include "models/user_model.h"
#include "views/users/bookmark_view/bookmark_view.h"
#include "views/users/edit_bookmark_view/edit_bookmark_view.h"

/**
 * Classe view che mostra una lista di bookmarks. E' utilizzata sia per la lista
 * completa dei bookmarks sia per mostrare i risultati di ricerca, cambiando il
 * model di volta in volta.
 */
class BookmarksListView: public QWidget {
  Q_OBJECT

 private:
  QVector<BookmarkInterface*> model;
  QLayout *containerLayout;
  QLayout *listLayout;
  EditBookmarkView *editBookmarkView;
  /**
   * Mappa utilizzata per tenere traccia di quali views sono mostrate, ove la chiave
   * è il puntatore al bookmark. Tempi di modifica/delete più efficienti rispetto
   * ad un vector
   */
  QMap<BookmarkInterface*, BookmarkView*> viewsMap;

  QString getStyles() const;
  void clean();

 private slots:
  void handleEditClicked(BookmarkInterface *bookmark);
  void hideEditView();

 public:
  BookmarksListView(QWidget *parent = nullptr);

  void setPrivilegies(UserInterface* user) const;

 public slots:
  void setModel(QVector<BookmarkInterface *> newModel);
  void addBookmarkView(BookmarkInterface *bookmark);
  void deleteBookmarkView(BookmarkInterface *bookmark);
  void updateBookmarkView(BookmarkInterface *bookmark);

 signals:
  void clickedDelete(BookmarkInterface *bookmark);
  void editedBookmark(
    BookmarkInterface *bookmark,
    const QString &name,
    const QString &link,
    const QString &description,
    const QDate &publication,
    const QTime &minRead,
    const QTime &duration
  );
};

#endif //INKMARK_BOOKMARKS_LIST_VIEW_H
