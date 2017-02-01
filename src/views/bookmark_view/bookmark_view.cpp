#include "bookmark_view.h"
#include "widgets/link_widget/link_widget.h"

BookmarkView::BookmarkView(BookmarkModel *m): model(m), layout(new QHBoxLayout) {
  if (!m) return;

  QUrl link = m->getLink();
  LinkWidget *nameLink = new LinkWidget(m->getName(), link);
  QLabel *hostLabel = new QLabel(link.host());
  layout->addWidget(nameLink);
  layout->addWidget(hostLabel);

  setLayout(layout);
}
