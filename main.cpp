#include <QApplication>
#include <QString>
#include <QFont>
#include "inkmark.h"

QString getAppStyles() {
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
