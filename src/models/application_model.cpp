#include "application_model.h"

QVector<BookmarkModel*> ApplicationModel::getBookmarks() const { return bookmarks; }

ApplicationModel::~ApplicationModel() {
  for (int i = 0; i < bookmarks.size(); i++) delete bookmarks[i];
}

QJsonObject* ApplicationModel::toJSON() const {
  QJsonObject *json = new QJsonObject();
  QJsonArray bookmarksJSON;

  for (int i = 0; i < bookmarks.size(); i++) {
    QJsonObject *bookmarkJSON = bookmarks[i]->toJSON();
    bookmarksJSON.append(*bookmarkJSON);
  }

  json->insert("bookmarks", bookmarksJSON);

  return json;
}

void ApplicationModel::addBookmark(BookmarkModel *bookmark) {
  bookmarks.push_back(bookmark);
  emit addedBookmark(bookmark);
}
