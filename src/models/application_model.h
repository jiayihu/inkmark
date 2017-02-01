#ifndef INKMARK_MODEL_H
#define INKMARK_MODEL_H

#include "bookmark_model.h"
#include <QVector>
#include <QObject>
#include <QJsonObject>
#include <QJsonArray>

class ApplicationModel: public QObject {
  Q_OBJECT

 private:
  QVector<BookmarkModel*> bookmarks;

 public:
  QVector<BookmarkModel*> getBookmarks() const;
  ~ApplicationModel();

  QJsonObject* toJSON() const;

 public slots:
    void addBookmark(BookmarkModel *bookmark);

 signals:
    void addedBookmark(BookmarkModel *bookmark);
};

#endif //INKMARK_MODEL_H
