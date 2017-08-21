#ifndef INKMARK_BOOKMARKS_LIST_VIEW_H
#define INKMARK_BOOKMARKS_LIST_VIEW_H

#include <QMap>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "models/bookmark_model.h"
#include "models/user_model.h"
#include "views/bookmark_view/bookmark_view.h"
#include "views/edit_bookmark_view/edit_bookmark_view.h"

/**
 * Classe view che mostra una lista di bookmarks. E' utilizzata sia per la lista
 * completa dei bookmarks sia per mostrare i risultati di ricerca, cambiando il
 * model di volta in volta.
 */
class BookmarksListView: public QWidget {
  Q_OBJECT

 private:
  QVector<BookmarkInterface*> model;
  QHBoxLayout *containerLayout;
  QVBoxLayout *listLayout;
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
  // Cancella la view relativa al bookmark ed emette il signal `clickedDelete`
  void handleDeleteClicked(BookmarkInterface *bookmark);
  void handleEditClicked(BookmarkInterface *bookmark);
  void hideEditView();

 public:
  BookmarksListView(QWidget *parent = nullptr);

  void setPrivilegies(UserInterface* user) const;

 public slots:
  void setModel(const QVector<BookmarkInterface *> &newModel);
  void addBookmarkView(BookmarkInterface *bookmark);
  void updateBookmarkView(BookmarkInterface *bookmark);

 signals:
  void clickedDelete(BookmarkInterface *bookmark);
  void editedBookmark(BookmarkInterface *bookmark, QString newName, QString newLink, QString newDesc);
};

#endif //INKMARK_BOOKMARKS_LIST_VIEW_H
