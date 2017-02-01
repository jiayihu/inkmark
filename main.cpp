#include <iostream>
#include <QApplication>
#include "models/application_model.h"
#include "controllers/add_bookmark_controller.h"
#include "controllers/bookmarks_list_controller.h"
#include "views/application_view/application_view.h"

class Inkmark {
 private:
  ApplicationModel appModel;
  ApplicationView appView;

 public:
  Inkmark() {}

  void init() {
    AddBookmarkView *addBookmarkView = appView.getAddBookmarkView();
    AddBookmarkController *addBookmarkController = new AddBookmarkController(&appModel, addBookmarkView);
    BookmarksListView *bookmarksListView = appView.getBookmarkListView();
    BookmarksListController *bookmarksListController = new BookmarksListController(&appModel, bookmarksListView);

    appView.show();
  }
};

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  Inkmark inkmark;
  inkmark.init();

  return app.exec();
}
