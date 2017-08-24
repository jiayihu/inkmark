#ifndef INKMARK_INKMARK_H
#define INKMARK_INKMARK_H

#include <QObject>
#include "models/application_model.h"
#include "views/application_view/application_view.h"
#include "controllers/application_controller/application_controller.h"

class Inkmark: public QObject {
  Q_OBJECT

 private:
  static QString modelFilename; // Non è utilizzato all'esterno per il momento

  ApplicationModel *appModel;
  ApplicationView *appView;
  ApplicationController *applicationController;

  bool loadModel();

 private slots:
  void saveModel() const;

 public:
  Inkmark();
  ~Inkmark();

  void show() const;
};

#endif //INKMARK_INKMARK_H
