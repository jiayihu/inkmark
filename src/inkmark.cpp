#include <QDebug>
#include <QJsonDocument>
#include "inkmark.h"

QString Inkmark::modelFilename = "model.json";

bool Inkmark::loadModel() {
  QFile loadFile(Inkmark::modelFilename);

  if (!loadFile.open(QIODevice::ReadOnly)) {
    qWarning() << "Inkmark::loadModel(): Couldn't open JSON file to read the model.";
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
    qWarning() << "Inkmark::saveModel(): Couldn't open JSON file to save the model.";
    return;
  }

  saveFile.write(jsonDoc.toJson());
}

Inkmark::Inkmark(): appModel(new ApplicationModel()), appView(new ApplicationView()) {
  loadModel();
  applicationController = new ApplicationController(appModel, appView);

  // Salvantaggio dei dati alla chiusura
  QObject::connect(appView, SIGNAL(applicationClosed()), this, SLOT(saveModel()));
}

Inkmark::~Inkmark() {
  delete appModel;
  delete applicationController;
}

void Inkmark::show() const {
  appView->show();
}
