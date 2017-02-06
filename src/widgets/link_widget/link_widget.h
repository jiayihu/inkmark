#ifndef INKMARK_LINK_WIDGET_H
#define INKMARK_LINK_WIDGET_H

#include <QLabel>
#include <QString>
#include <QUrl>

class LinkWidget: public QLabel {
 private:
  QUrl url;

  QString createHTMLLink() const;

 public:
  LinkWidget(const QString &t = "", const QUrl &u = QUrl(), QWidget *parent = nullptr);

  void setUrl(QUrl newUrl);
};

#endif //INKMARK_LINK_WIDGET_H
