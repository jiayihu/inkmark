#include "link_widget.h"

QString LinkWidget::createHTMLLink() const {
  return
    "<a href=\"" + url.toString() + "\" style=\"color: #666; font-weight: bold;\">" + QLabel::text() + "</a>";
}

LinkWidget::LinkWidget(const QString &t, const QUrl &u, QWidget *parent): QLabel(t, parent), url(u) {
  setText(createHTMLLink());
  setTextFormat(Qt::RichText);
  setTextInteractionFlags(Qt::TextBrowserInteraction);
  setOpenExternalLinks(true);
}

void LinkWidget::setUrl(QUrl newUrl) {
  url = newUrl;
  setText(createHTMLLink());
}
