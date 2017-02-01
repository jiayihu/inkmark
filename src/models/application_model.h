#ifndef INKMARK_MODEL_H
#define INKMARK_MODEL_H

#include "bookmark_model.h"
#include <QVector>
#include <QObject>

class ApplicationModel: public QObject {
  Q_OBJECT

 private:
  QVector<BookmarkModel*> bookmarks;

 public:
  QVector<BookmarkModel*> getBookmarks() const;
  ~ApplicationModel();

 public slots:
    void addBookmark(BookmarkModel *bookmark);

 signals:
    void addedBookmark(BookmarkModel *bookmark);
};

#endif //INKMARK_MODEL_H
