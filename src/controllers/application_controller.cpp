#include <QVector>
#include "application_controller.h"
#include "views/search_bookmark_view/search_bookmark_view.h"

void ApplicationController::handleSearch(QString searchText) const {
  QVector<BookmarkModel*> found = model->search(searchText);
  if (found.size()) view->showSearchResults(found);
}

ApplicationController::ApplicationController(ApplicationModel *m, ApplicationView *v): model(m), view(v) {
  SearchBookmarkView *searchView = view->getSearchBookmarkView();
  QObject::connect(searchView, SIGNAL(clickedSearch(QString)), this, SLOT(handleSearch(QString)));
}
