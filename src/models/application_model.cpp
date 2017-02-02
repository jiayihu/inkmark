#include "application_model.h"

QVector<BookmarkModel*> ApplicationModel::getBookmarks() const { return bookmarks; }

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

void ApplicationModel::addBookmark(BookmarkModel *bookmark) {
  bookmarks.push_back(bookmark);
  emit addedBookmark(bookmark);
}
