#include "link_widget.h"

LinkWidget::LinkWidget(QString t, QUrl u): text(t), url(u) {
  setText("<a href=\"" + url.toString() + "\">" + text + "</a>");
  setTextFormat(Qt::RichText);
  setTextInteractionFlags(Qt::TextBrowserInteraction);
  setOpenExternalLinks(true);
}
