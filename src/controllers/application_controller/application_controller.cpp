#include "application_controller.h"
#include "views/search_bookmark_view/search_bookmark_view.h"

ApplicationController::ApplicationController(ApplicationModel *m, ApplicationView *v)
  : model(m), view(v) {
  BookmarksListView *bookmarksListView = view->getBookmarkListView();
  SearchBookmarkView *searchBookmarkView = view->getSearchBookmarkView();

  // Uso di funzione lambda, permesso da Qt, per evitare di scrivere una funzione
  // handler. Non interessano gli eventuali parametri del signal.
  QObject::connect(
    searchBookmarkView,
    &SearchBookmarkView::clickedCancel,
    [=]() { bookmarksListView->setModel(model->getBookmarks()); }
  );
}
