#include <QApplication>
#include <QFont>
#include <QDir>
#include "inkmark.h"

QString getAppStyles() {
  // Debug, mostra un bordo rosso attorno al widget in hover
  return
      "QWidget:hover { border: 1px solid red; }";
}

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  /**
   * In Mac l'eseguibile è creato alcune cartelle per cui la cartella corrente
   * non è quella da cui si lancia l'app, ma bensì quella dell'eseguibile effettivo
   * che è qualche livello più annidato.
   */
//  QDir bin(QCoreApplication::applicationDirPath());
//
//  #if defined(Q_OS_DARWIN)
//    bin.cdUp();
//    bin.cdUp();
//    bin.cdUp();
//  #endif
//  QDir::setCurrent(bin.absolutePath());

  /** Fine fix per Mac */

  app.setStyleSheet(getAppStyles());
  app.setFont(QFont("Helvetica", 14));

  Inkmark inkmark;
  inkmark.show();

  return app.exec();
}
