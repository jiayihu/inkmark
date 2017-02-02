#include "application_model.h"

QVector<BookmarkModel*> ApplicationModel::getBookmarks() const { return bookmarks; }

ApplicationModel::~ApplicationModel() {
  for (int i = 0; i < bookmarks.size(); i++) delete bookmarks[i];
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
