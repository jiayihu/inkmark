#include "bookmarks_list_view.h"
#include "../bookmark_view/bookmark_view.h"

BookmarksListView::BookmarksListView(): layout(new QVBoxLayout()) {
  layout->setAlignment(Qt::AlignTop);
  setLayout(layout);
}

void BookmarksListView::addBookmark(BookmarkModel *bookmark) {
  BookmarkView *bookmarkView = new BookmarkView(bookmark);
  layout->addWidget(bookmarkView);
}
