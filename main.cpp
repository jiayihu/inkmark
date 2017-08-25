#include <QApplication>
#include <QFont>
#include "inkmark.h"

QString getAppStyles() {
  // Debug, mostra un bordo rosso attorno al widget in hover
  return
      "QWidget:hover { border: 1px solid red; }";
}

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  app.setStyleSheet(getAppStyles());
  app.setFont(QFont("Helvetica", 14));

  Inkmark inkmark;
  inkmark.show();

  return app.exec();
}
