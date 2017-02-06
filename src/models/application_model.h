#ifndef INKMARK_MODEL_H
#define INKMARK_MODEL_H

#include <QString>
#include <QVector>
#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include "bookmark_model.h"

/**
 * Classe che gestisce il model dell'applicazione. Nessun'altra classa può
 * modificare il model dell'applicazione, infatti tutti i metodi ritornano al
 * massimo puntatori di tipo BookmarkInterface, che contiene solo metodi virtuali
 * marcati const.
 */
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
  QVector<BookmarkModel*> search(QString searchText) const;

 signals:
  void addedBookmark(BookmarkModel *bookmark);
  void deletedBookmark(BookmarkModel *bookmark);
  void updatedBookmark(BookmarkModel *bookmark);
  void finishedSearch(QVector<BookmarkModel*>) const;
};

#endif //INKMARK_MODEL_H
