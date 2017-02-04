#include "link_widget.h"

LinkWidget::LinkWidget(QWidget *parent): QLabel(parent) {}

LinkWidget::LinkWidget(QString t, QUrl u, QWidget *parent): QLabel(t, parent), url(u) {
  setText("<a href=\"" + url.toString() + "\">" + QLabel::text() + "</a>");
  setTextFormat(Qt::RichText);
  setTextInteractionFlags(Qt::TextBrowserInteraction);
  setOpenExternalLinks(true);
}

void LinkWidget::setUrl(QUrl newUrl) {
  url = newUrl;
  setText("<a href=\"" + url.toString() + "\">" + QLabel::text() + "</a>");
}
