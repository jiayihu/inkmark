#include <iostream>
#include <QApplication>
#include "models/application-model.h"
#include "views/application-view.h"

class Inkmark {
 private:
  ApplicationModel appModel;
  ApplicationView appView;

 public:
  Inkmark() {}

  void init() {
    appView.show();
    QObject::connect(&appView, SIGNAL(clickedQuit()), qApp, SLOT(quit()));
  }
};

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  Inkmark inkmark;
  inkmark.init();

  return app.exec();
}
