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
 *
 * Per ogni modifica/aggiunta al model bisogna richiamarne un metodo, che provvederà
 * a fare la modifica e fare emit di un SIGNAL di cui è in ascolto qualunque
 * parte dell'applicazione sia interessata.
 *
 * Esiste inoltre un'unica istanza di ApplicationModel, che contiene tutti i dati
 * di interesse globale per l'applicazione come la lista di bookmarks.
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
  void addBookmark(const QString &name, const QString &link, const QString &description);
  void deleteBookmark(BookmarkInterface *bookmark);
  void editBookmark(BookmarkInterface *bookmark, const QString &newName, const QString &newLink, const QString &newDesc);
  QVector<BookmarkInterface*> search(const QString &searchText) const;

 signals:
  void addedBookmark(BookmarkInterface *bookmark);
  void deletedBookmark(BookmarkInterface *bookmark);
  void updatedBookmark(BookmarkInterface *bookmark);
  void finishedSearch(QVector<BookmarkInterface*> results) const;
};

#endif //INKMARK_MODEL_H
