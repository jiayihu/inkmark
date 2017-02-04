#include <QString>
#include "bookmarks_list_view.h"

void BookmarksListView::clean() {
  for (int i = 0; i < model.size(); i++) {
    BookmarkModel *bookmark = model[i];
    listLayout->removeWidget(viewsMap[bookmark]);
    delete viewsMap[bookmark];
    viewsMap.remove(bookmark);
  }
  model.clear();
}

void BookmarksListView::handleDeleteClicked(BookmarkModel *bookmark) {
  listLayout->removeWidget(viewsMap[bookmark]);
  delete viewsMap[bookmark];
  viewsMap.remove(bookmark);

  emit clickedDelete(bookmark);
}

void BookmarksListView::hideEditView() {
  editBookmarkView->setVisible(false);
}

void BookmarksListView::handleEditClicked(BookmarkModel *bookmark) {
  editBookmarkView->setModel(bookmark);
  editBookmarkView->setVisible(true);
}

BookmarksListView::BookmarksListView(QWidget *parent): QWidget(parent) {
  containerLayout = new QHBoxLayout();
  containerLayout->setAlignment(Qt::AlignTop);

  QWidget *listContainer = new QWidget();
  listLayout = new QVBoxLayout(listContainer);
  listLayout->setAlignment(Qt::AlignTop);

  editBookmarkView = new EditBookmarkView(this);
  editBookmarkView->setVisible(false);
  // Chiudi il widget per la modifica
  QObject::connect(editBookmarkView, SIGNAL(saveClicked(BookmarkModel*, QString, QString, QString)), this, SLOT(hideEditView()));
  QObject::connect(editBookmarkView, SIGNAL(cancelClicked()), this, SLOT(hideEditView()));
  // Propaga il signal all'esterno
  QObject::connect(
      editBookmarkView,
      SIGNAL(saveClicked(BookmarkModel*, QString, QString, QString)),
      this,
      SIGNAL(editedBookmark(BookmarkModel*, QString, QString, QString))
  );

  containerLayout->addWidget(listContainer);
  containerLayout->addWidget(editBookmarkView);

  setLayout(containerLayout);
}

void BookmarksListView::setModel(const QVector<BookmarkModel *> &newModel) {
  if (model.size()) clean();

  // TODO Non fare nulla se è lo stesso model
  model = newModel;
  for (int i = 0; i < model.size(); i++) addBookmarkView(model[i]);
}

void BookmarksListView::addBookmarkView(BookmarkModel *bookmark) {
  BookmarkView *bookmarkView = new BookmarkView(bookmark);
  viewsMap[bookmark] = bookmarkView;
  QObject::connect(bookmarkView, SIGNAL(clickedDelete(BookmarkModel*)), this, SLOT(handleDeleteClicked(BookmarkModel*)));
  QObject::connect(bookmarkView, SIGNAL(clickedEdit(BookmarkModel*)), this, SLOT(handleEditClicked(BookmarkModel*)));

  listLayout->addWidget(bookmarkView);
}

void BookmarksListView::updateBookmarkView(BookmarkModel *bookmark) {
  BookmarkView *bookmarkView = viewsMap[bookmark];
  bookmarkView->setModel(bookmark);
}
