#ifndef INKMARK_LINK_WIDGET_H
#define INKMARK_LINK_WIDGET_H

#include <QLabel>
#include <QString>
#include <QUrl>

class LinkWidget: public QLabel {
 private:
  QUrl url;

 public:
  LinkWidget(QString t = "", QUrl u = QUrl());

  void setUrl(QUrl newUrl);
};

#endif //INKMARK_LINK_WIDGET_H
