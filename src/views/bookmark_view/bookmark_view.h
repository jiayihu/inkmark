#ifndef INKMARK_BOOKMARK_VIEW_H
#define INKMARK_BOOKMARK_VIEW_H

#include <QWidget>
#include <QHBoxLayout>
#include "models/bookmark_model.h"

class BookmarkView: public QWidget {
  Q_OBJECT

 private:
  // TODO Create Interface per Bookmark
  BookmarkModel *model;
  QHBoxLayout *layout;

  private slots:
    /**
     * Emette il signal clickedDelete con il proprio model
     */
    void handleDeleteClick();

 public:
  BookmarkView(BookmarkModel *m = nullptr);

  signals:
    void clickedDelete(BookmarkModel*);
};

#endif //INKMARK_BOOKMARK_VIEW_H
