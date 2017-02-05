#ifndef INKMARK_INKMARK_H
#define INKMARK_INKMARK_H

#include <QObject>
#include "models/application_model.h"
#include "views/application_view/application_view.h"
#include "controllers/application_controller/application_controller.h"
#include "controllers/add_bookmark_controller.h"
#include "controllers/bookmarks_list_controller.h"
#include "controllers/search_bookmark_controller/search_bookmark_controller.h"

class Inkmark: public QObject {
  Q_OBJECT

 private:
  ApplicationModel *appModel;
  ApplicationView *appView;

  AddBookmarkController *addBookmarkController;
  BookmarksListController *bookmarksListController;
  SearchBookmarkController *searchBookmarkController;
  ApplicationController *applicationController;

  static QString modelFilename; // Non è utilizzato all'esterno per il momento

 public:
  Inkmark();
  ~Inkmark();

  void init();
  bool loadModel();

  public slots:
    void saveModel() const;
};

#endif //INKMARK_INKMARK_H
