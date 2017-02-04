#include <QPushButton>
#include "bookmark_view.h"
#include "widgets/link_widget/link_widget.h"

void BookmarkView::handleDeleteClick() {
  emit clickedDelete(model);
}

BookmarkView::BookmarkView(BookmarkModel *m): model(m), layout(new QHBoxLayout) {
  if (!m) return;

  QPushButton *deleteButton = new QPushButton("X");
  QObject::connect(deleteButton, SIGNAL(clicked()), this, SLOT(handleDeleteClick()));

  QUrl link = m->getLink();
  LinkWidget *nameLink = new LinkWidget(m->getName(), link);
  QLabel *hostLabel = new QLabel(link.host());

  layout->addWidget(deleteButton);
  layout->addWidget(nameLink);
  layout->addWidget(hostLabel);

  setLayout(layout);
}
