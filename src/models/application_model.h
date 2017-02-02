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

  void clean();

 public:
  QVector<BookmarkModel*> getBookmarks() const;
  ~ApplicationModel();

  void readFromJSON(const QJsonObject &json);
  void writeToJSON(QJsonObject &json) const;

 public slots:
    void addBookmark(BookmarkModel *bookmark);

 signals:
    void addedBookmark(BookmarkModel *bookmark);
};

#endif //INKMARK_MODEL_H
