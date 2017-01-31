#ifndef INKMARK_APPLICATION_H
#define INKMARK_APPLICATION_H

#include <QWidget>
#include <QPushButton>

class ApplicationView: public QWidget {
 Q_OBJECT

 public:
  ApplicationView(QWidget *parent = nullptr);

  signals:
    void clickedQuit();
};

#endif //INKMARK_APPLICATION_H
