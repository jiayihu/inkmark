#ifndef INKMARK_APPLICATION_CONTROLLER_H
#define INKMARK_APPLICATION_CONTROLLER_H

#include <QObject>
#include "models/application_model.h"
#include "views/application_view/application_view.h"

class ApplicationController: public QObject {
  Q_OBJECT

 private:
  ApplicationModel *model;
  ApplicationView *view;

 private slots:
  void handleSearch(QString searchText) const;

 public:
  ApplicationController(ApplicationModel *m, ApplicationView *v);
};

#endif //INKMARK_APPLICATION_CONTROLLER_H
