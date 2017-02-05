#include <QJsonDocument>
#include "inkmark.h"

QString Inkmark::modelFilename = "model.json";

Inkmark::Inkmark(): appModel(new ApplicationModel()), appView(appView = new ApplicationView()) {
  loadModel();
  applicationController = new ApplicationController(appModel, appView);
}

Inkmark::~Inkmark() {
  delete appModel;
  delete addBookmarkController;
  delete bookmarksListController;
  delete searchBookmarkController;
  delete applicationController;
}

/**
 * Inizializza i controllers delle views. Le views sono già inizializzate da
 * ApplicationView, mentre il model è già inizializzato con ApplicationModel.
 * Esiste inoltre un'unica istanza di ApplicationModel, che contiene tutti i dati
 * di interesse globale per l'applicazione come la lista di bookmarks.
 */
void Inkmark::init() {
  AddBookmarkView *addBookmarkView = appView->getAddBookmarkView();
  addBookmarkController = new AddBookmarkController(appModel, addBookmarkView);

  BookmarksListView *bookmarksListView = appView->getBookmarkListView();
  bookmarksListController = new BookmarksListController(appModel, bookmarksListView);

  SearchBookmarkView *searchBookmarkView = appView->getSearchBookmarkView();
  searchBookmarkController = new SearchBookmarkController(appModel, searchBookmarkView);

  QObject::connect(appView, SIGNAL(applicationClosed()), this, SLOT(saveModel()));

  appView->show();
}

bool Inkmark::loadModel() {
  QFile loadFile(Inkmark::modelFilename);

  if (!loadFile.open(QIODevice::ReadOnly)) {
    qWarning("Couldn't open JSON file to read the model.");
    return false;
  }

  QByteArray savedData = loadFile.readAll();
  QJsonDocument jsonDoc(QJsonDocument::fromJson(savedData));
  // Popola il model tramite i dati nel JSON
  appModel->readFromJSON(jsonDoc.object());

  return true;
}

void Inkmark::saveModel() const {
  QJsonObject modelJSON;
  appModel->writeToJSON(modelJSON);
  QJsonDocument jsonDoc(modelJSON);

  QFile saveFile(Inkmark::modelFilename);

  if (!saveFile.open(QIODevice::WriteOnly)) {
    qWarning("Couldn't open JSON file to save the model.");
    return;
  }

  saveFile.write(jsonDoc.toJson());
}
