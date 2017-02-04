#include "link_widget.h"

LinkWidget::LinkWidget(QString t, QUrl u): QLabel(t), url(u) {
  setText("<a href=\"" + url.toString() + "\">" + QLabel::text() + "</a>");
  setTextFormat(Qt::RichText);
  setTextInteractionFlags(Qt::TextBrowserInteraction);
  setOpenExternalLinks(true);
}

void LinkWidget::setUrl(QUrl newUrl) {
  url = newUrl;
  setText("<a href=\"" + url.toString() + "\">" + QLabel::text() + "</a>");
}
