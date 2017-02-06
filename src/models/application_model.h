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
  ~ApplicationModel();

  // Restituisce un vettore di array da usare come read-only
  QVector<BookmarkInterface*> getBookmarks() const;

  void readFromJSON(const QJsonObject &json);
  void writeToJSON(QJsonObject &json) const;

 public slots:
  void addBookmark(BookmarkModel *bookmark);
  void deleteBookmark(BookmarkInterface *bookmark);
  void editBookmark(BookmarkInterface *bookmark, QString newName, QString newLink, QString newDesc);
  QVector<BookmarkInterface*> search(QString searchText) const;

 signals:
  void addedBookmark(BookmarkInterface *bookmark);
  void deletedBookmark(BookmarkInterface *bookmark);
  void updatedBookmark(BookmarkInterface *bookmark);
  void finishedSearch(QVector<BookmarkInterface*>) const;
};

#endif //INKMARK_MODEL_H
