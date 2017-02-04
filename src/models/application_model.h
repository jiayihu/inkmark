#ifndef INKMARK_MODEL_H
#define INKMARK_MODEL_H

#include <QString>
#include <QVector>
#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include "bookmark_model.h"

class ApplicationModel: public QObject {
  Q_OBJECT

 private:
  QVector<BookmarkModel*> bookmarks;

  void clean();

 public:
  QVector<BookmarkModel*> getBookmarks() const;
  ~ApplicationModel();

  void readFromJSON(const QJsonObject &json);
  void writeToJSON(QJsonObject &json) const;

 public slots:
  void addBookmark(BookmarkModel *bookmark);
  void deleteBookmark(BookmarkModel *bookmark);
  void editBookmark(BookmarkModel *bookmark, QString newName, QString newLink, QString newDesc);

 signals:
  void addedBookmark(BookmarkModel *bookmark);
  void deletedBookmark(BookmarkModel *bookmark);
  void updatedBookmark(BookmarkModel *bookmark);
};

#endif //INKMARK_MODEL_H
