#ifndef INKMARK_LINK_WIDGET_H
#define INKMARK_LINK_WIDGET_H

#include <QLabel>
#include <QString>
#include <QUrl>

class LinkWidget: public QLabel {
 private:
  QString text;
  QUrl url;

 public:
  LinkWidget(QString t = "", QUrl u = QUrl());
};

#endif //INKMARK_LINK_WIDGET_H
