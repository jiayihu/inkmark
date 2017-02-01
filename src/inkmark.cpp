#include "inkmark.h"
#include <QDebug>
#include <QJsonDocument>

Inkmark::Inkmark(): appModel(new ApplicationModel()), appView(appView = new ApplicationView()) {}

Inkmark::~Inkmark() { delete appModel; }

void Inkmark::init() {
  AddBookmarkView *addBookmarkView = appView->getAddBookmarkView();
  AddBookmarkController *addBookmarkController = new AddBookmarkController(appModel, addBookmarkView);
  BookmarksListView *bookmarksListView = appView->getBookmarkListView();
  BookmarksListController *bookmarksListController = new BookmarksListController(appModel, bookmarksListView);

  QObject::connect(appView, SIGNAL(applicationClosed()), this, SLOT(saveModel()));

  appView->show();
}

void Inkmark::saveModel() const {
  QJsonObject *modelJSON = appModel->toJSON();
  QJsonDocument jsonDoc(*modelJSON);
  QFile saveFile("model.json");

  if (!saveFile.open(QIODevice::WriteOnly)) {
    qWarning("Couldn't open save file.");
    return;
  }

  saveFile.write(jsonDoc.toJson());
}
