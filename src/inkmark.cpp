#include <QJsonDocument>
#include "inkmark.h"
#include "controllers/add_bookmark_controller.h"
#include "controllers/bookmarks_list_controller.h"
#include "controllers/application_controller.h"

QString Inkmark::modelFilename = "model.json";

Inkmark::Inkmark(): appModel(new ApplicationModel()), appView(appView = new ApplicationView()) {
  loadModel();
}

Inkmark::~Inkmark() { delete appModel; }

void Inkmark::init() {
  ApplicationController *applicationController = new ApplicationController(appModel, appView);

  AddBookmarkView *addBookmarkView = appView->getAddBookmarkView();
  AddBookmarkController *addBookmarkController = new AddBookmarkController(appModel, addBookmarkView);

  BookmarksListView *bookmarksListView = appView->getBookmarkListView();
  BookmarksListController *bookmarksListController = new BookmarksListController(appModel, bookmarksListView);
  SearchBookmarkView *searchBookmarkView = appView->getSearchBookmarkView();

  QObject::connect(appView, SIGNAL(applicationClosed()), this, SLOT(saveModel()));

  appView->show();
}

bool Inkmark::loadModel() {
  QFile loadFile(Inkmark::modelFilename);

  if (!loadFile.open(QIODevice::ReadOnly)) {
    qWarning("Couldn't open JSON file to read from.");
    return false;
  }

  QByteArray savedData = loadFile.readAll();
  QJsonDocument jsonDoc(QJsonDocument::fromJson(savedData));
  appModel->readFromJSON(jsonDoc.object());

  return true;
}

void Inkmark::saveModel() const {
  QJsonObject modelJSON;
  appModel->writeToJSON(modelJSON);
  QJsonDocument jsonDoc(modelJSON);

  QFile saveFile(Inkmark::modelFilename);

  if (!saveFile.open(QIODevice::WriteOnly)) {
    qWarning("Couldn't open JSON file to write to.");
    return;
  }

  saveFile.write(jsonDoc.toJson());
}
