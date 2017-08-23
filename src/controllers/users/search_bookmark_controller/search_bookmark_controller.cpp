#include "search_bookmark_controller.h"

SearchBookmarkController::SearchBookmarkController(ApplicationModel *m, SearchBookmarkView *v): model(m), view(v) {
  QObject::connect(view, SIGNAL(clickedSearch(QString)), model, SLOT(search(QString)));
}
