#include "application_model.h"

QVector<BookmarkModel*> ApplicationModel::getBookmarks() const { return bookmarks; }

void ApplicationModel::clean() {
  for (int i = 0; i < bookmarks.size(); i++) delete bookmarks[i];
}

ApplicationModel::~ApplicationModel() { clean(); }

QVector<BookmarkModel*> ApplicationModel::search(QString searchText) const {
  QVector<BookmarkModel*> found;

  for (int i = 0; i < bookmarks.size(); i++) {
    if (bookmarks[i]->hasWord(searchText)) found.push_back(bookmarks[i]);
  }

  return found;
}

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

void ApplicationModel::addBookmark(BookmarkModel *bookmark) {
  bookmarks.push_back(bookmark);
  emit addedBookmark(bookmark);
}

void ApplicationModel::deleteBookmark(BookmarkModel *bookmark) {
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

void ApplicationModel::editBookmark(BookmarkModel *bookmark, QString newName, QString newLink, QString newDesc) {
  int bookmarkIndex = bookmarks.indexOf(bookmark);

  if (bookmarkIndex == -1) return;

  BookmarkModel *foundBookmark = bookmarks[bookmarkIndex];
  foundBookmark->editName(newName);
  foundBookmark->editLink(newLink);
  foundBookmark->editDescription(newDesc);

  emit updatedBookmark(bookmark);
}
