#ifndef INKMARK_BOOKMARK_VIEW_H
#define INKMARK_BOOKMARK_VIEW_H

#include <QWidget>
#include <QHBoxLayout>
#include "models/bookmark_model.h"

class BookmarkView: public QWidget {
 private:
  // TODO Create Interface per Bookmark
  BookmarkModel *model;
  QHBoxLayout *layout;

 public:
  BookmarkView(BookmarkModel *m = nullptr);
};

#endif //INKMARK_BOOKMARK_VIEW_H
