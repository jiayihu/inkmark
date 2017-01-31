#include "application-model.h"

QVector<BookmarkModel*> ApplicationModel::getBookmarks() const { return bookmarks; }

void ApplicationModel::addBookmark(BookmarkModel *bookmark) {
  bookmarks.push_back(bookmark);
  emit addedBookmark(bookmark);
}
