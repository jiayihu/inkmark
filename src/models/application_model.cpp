#include "application_model.h"

QVector<BookmarkInterface*> ApplicationModel::getBookmarks() const {
  QVector<BookmarkInterface*> bookmarksInterfaces;
  for (int i = 0; i < bookmarks.size(); i++) bookmarksInterfaces.push_back(bookmarks[i]);

  return bookmarksInterfaces;
}

void ApplicationModel::clean() {
  for (int i = 0; i < bookmarks.size(); i++) delete bookmarks[i];
}

ApplicationModel::~ApplicationModel() { clean(); }

void ApplicationModel::readFromJSON(const QJsonObject &json) {
  // Pulisco l'oggetto se conteneva dati
  clean();

  QJsonArray bookmarksJSON = json.value("bookmarks").toArray();
  for (int i = 0; i < bookmarksJSON.size(); i++) {
    BookmarkModel *bookmark = new BookmarkModel();
    bookmark->readFromJSON(bookmarksJSON[i].toObject());
    bookmarks.push_back(bookmark);
  }
}

void ApplicationModel::writeToJSON(QJsonObject &json) const {
  QJsonArray bookmarksJSON;

  for (int i = 0; i < bookmarks.size(); i++) {
    QJsonObject bookmarkJSON;
    bookmarks[i]->writeToJSON(bookmarkJSON);
    bookmarksJSON.append(bookmarkJSON);
  }

  json.insert("bookmarks", bookmarksJSON);
}

void ApplicationModel::addBookmark(const QString &name, const QString &link, const QString &description) {
  BookmarkModel *bookmark = new BookmarkModel(link, name, description);
  bookmarks.push_back(bookmark);
  
  emit addedBookmark(bookmark);
}

void ApplicationModel::deleteBookmark(BookmarkInterface *bookmark) {
  QVector<BookmarkModel*>::iterator it = bookmarks.begin();
  bool trovato = false;

  for (; it != bookmarks.end() && !trovato; it++) {
    if (*it == bookmark) {
      bookmarks.erase(it);
      trovato = true;
    }
  }

  if (!trovato) return;

  emit deletedBookmark(bookmark);
  // Cancella il bookmark dallo heap dopo il signal
  delete bookmark;
}

void ApplicationModel::editBookmark(BookmarkInterface *bookmark, const QString &newName, const QString &newLink, const QString &newDesc) {
  int bookmarkIndex = bookmarks.indexOf(static_cast<BookmarkModel*>(bookmark));

  if (bookmarkIndex == -1) return;

  BookmarkModel *foundBookmark = bookmarks[bookmarkIndex];
  foundBookmark->editName(newName);
  foundBookmark->editLink(newLink);
  foundBookmark->editDescription(newDesc);

  emit updatedBookmark(bookmark);
}

QVector<BookmarkInterface*> ApplicationModel::search(const QString &searchText) const {
  QVector<BookmarkInterface*> found;

  for (int i = 0; i < bookmarks.size(); i++) {
    if (bookmarks[i]->hasWord(searchText)) found.push_back(bookmarks[i]);
  }

  emit finishedSearch(found);
  return found;
}
