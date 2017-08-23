#include <QString>
#include <QScrollArea>
#include "bookmarks_list_view.h"

QString BookmarksListView::getStyles() const {
  return
  "QScrollBar:vertical { width: 5px; }"
  "QScrollBar::handle:vertical {"
    "background-color: #696969;"
  "}";
}

void BookmarksListView::clean() {
  for (int i = 0; i < model.size(); i++) {
    BookmarkInterface *bookmark = model[i];
    listLayout->removeWidget(viewsMap[bookmark]);
    delete viewsMap[bookmark];
  }

  viewsMap.clear();
  model.clear();
}

void BookmarksListView::hideEditView() {
  editBookmarkView->setVisible(false);
}

void BookmarksListView::handleEditClicked(BookmarkInterface *bookmark) {
  editBookmarkView->setModel(bookmark);
  editBookmarkView->setVisible(true);
}

BookmarksListView::BookmarksListView(QWidget *parent): QWidget(parent) {
  setStyleSheet(getStyles());

  containerLayout = new QHBoxLayout();
  containerLayout->setAlignment(Qt::AlignTop);
  containerLayout->setSpacing(0);

  QWidget *listContainer = new QWidget();
  listLayout = new QVBoxLayout(listContainer);
  listLayout->setContentsMargins(0, 0, 0, 0);
  listLayout->setSpacing(0);
  listLayout->setAlignment(Qt::AlignTop);

  QScrollArea *scrollArea = new QScrollArea();
  scrollArea->setWidget(listContainer);
  scrollArea->setWidgetResizable(true);
  scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
  // BookmarkView fixed width + 2 to avoid horizontal scroll
  scrollArea->setMinimumWidth(642);
  scrollArea->setFrameShape(QFrame::NoFrame);

  editBookmarkView = new EditBookmarkView();
  editBookmarkView->setVisible(false);
  // Chiudi il widget per la modifica
  QObject::connect(editBookmarkView, SIGNAL(saveClicked(BookmarkInterface*, QString, QString, QString)), this, SLOT(hideEditView()));
  QObject::connect(editBookmarkView, SIGNAL(cancelClicked()), this, SLOT(hideEditView()));
  // Propaga il signal all'esterno
  QObject::connect(
      editBookmarkView,
      SIGNAL(saveClicked(BookmarkInterface*, QString, QString, QString)),
      this,
      SIGNAL(editedBookmark(BookmarkInterface*, QString, QString, QString))
  );

  containerLayout->addWidget(scrollArea);
  containerLayout->addWidget(editBookmarkView);

  setLayout(containerLayout);
}

void BookmarksListView::setPrivilegies(UserInterface* currentUser) const {
  for (int i = 0; i < model.size(); i++) {
    BookmarkInterface* bookmark = model[i];
    BookmarkView* bookmarkView = viewsMap[bookmark];
    if (currentUser) bookmarkView->setPrivilegies(currentUser->canEdit(bookmark), currentUser->canDelete(bookmark));
    else bookmarkView->setPrivilegies(false, false);
  }
}

void BookmarksListView::setModel(QVector<BookmarkInterface *> newModel) {
  if (!model.empty()) clean();

  model = newModel;
  for (int i = 0; i < model.size(); i++) addBookmarkView(model[i]);
}

void BookmarksListView::addBookmarkView(BookmarkInterface *bookmark) {
  BookmarkView *bookmarkView = new BookmarkView();
  bookmarkView->setModel(bookmark);
  viewsMap[bookmark] = bookmarkView;
  QObject::connect(bookmarkView, SIGNAL(clickedDelete(BookmarkInterface*)), this, SIGNAL(clickedDelete(BookmarkInterface*)));
  QObject::connect(bookmarkView, SIGNAL(clickedEdit(BookmarkInterface*)), this, SLOT(handleEditClicked(BookmarkInterface*)));

  listLayout->addWidget(bookmarkView);
}

void BookmarksListView::deleteBookmarkView(BookmarkInterface *bookmark) {
  listLayout->removeWidget(viewsMap[bookmark]);
  delete viewsMap[bookmark];
  viewsMap.remove(bookmark);
  model.remove(model.indexOf(bookmark));
}

void BookmarksListView::updateBookmarkView(BookmarkInterface *bookmark) {
  BookmarkView *bookmarkView = viewsMap[bookmark];
  bookmarkView->setModel(bookmark);
}
