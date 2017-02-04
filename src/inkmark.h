#ifndef INKMARK_INKMARK_H
#define INKMARK_INKMARK_H

#include <QObject>
#include "models/application_model.h"
#include "views/application_view/application_view.h"

class Inkmark: public QObject {
  Q_OBJECT

 private:
  ApplicationModel *appModel;
  ApplicationView *appView;
  static QString modelFilename; // Non è utilizzato all'esterno per il momento

 public:
  Inkmark();
  ~Inkmark();

  bool loadModel();
  void init();

  public slots:
    void saveModel() const;
};

#endif //INKMARK_INKMARK_H
