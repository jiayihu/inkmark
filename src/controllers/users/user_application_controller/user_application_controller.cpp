#include "user_application_controller.h"

UserApplicationController::UserApplicationController(ApplicationModel *m, UserApplicationView *v)
  : model(m), view(v) {
  EditBookmarkView *addBookmarkView = view->getAddBookmarkView();
  addBookmarkController = new AddBookmarkController(model, addBookmarkView);

  BookmarksListView *bookmarksListView = view->getBookmarkListView();
  bookmarksListController = new BookmarksListController(model, bookmarksListView);

  SearchBookmarkView *searchBookmarkView = view->getSearchBookmarkView();
  searchBookmarkController = new SearchBookmarkController(model, searchBookmarkView);

  QObject::connect(view, SIGNAL(logoutClicked()), model, SLOT(logout()));

  // Uso di funzione lambda, permesso da Qt, per evitare di scrivere un metodo
  // handler. Non interessano gli eventuali parametri del signal.
  QObject::connect(
    searchBookmarkView,
    &SearchBookmarkView::clickedCancel,
    [=]() { bookmarksListView->setModel(model->getBookmarks()); }
  );
}

UserApplicationController::~UserApplicationController() {
  delete addBookmarkController;
  delete bookmarksListController;
  delete searchBookmarkController;
}
