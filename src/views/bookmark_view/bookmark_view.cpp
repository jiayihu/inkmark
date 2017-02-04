#include <QPushButton>
#include <QHBoxLayout>
#include "bookmark_view.h"

void BookmarkView::handleDeleteClick() { emit clickedDelete(model); }

void BookmarkView::handleEditClick() { emit clickedEdit(model); }

BookmarkView::BookmarkView(BookmarkModel *m): model(m) {
  if (!model) return;

  QHBoxLayout *layout = new QHBoxLayout();

  QPushButton *deleteButton = new QPushButton("X");
  QObject::connect(deleteButton, SIGNAL(clicked()), this, SLOT(handleDeleteClick()));

  QUrl link = model->getLink();
  nameLink = new LinkWidget(model->getName(), link);
  hostLabel = new QLabel(link.host());

  QPushButton *editButton = new QPushButton("Edit");
  QObject::connect(editButton, SIGNAL(clicked()), this, SLOT(handleEditClick()));

  layout->addWidget(deleteButton);
  layout->addWidget(nameLink);
  layout->addWidget(hostLabel);
  layout->addWidget(editButton);

  setLayout(layout);
}

void BookmarkView::setModel(BookmarkModel *newModel) {
  model = newModel;

  QUrl link = model->getLink();
  nameLink->setText(model->getName());
  nameLink->setUrl(link);
  hostLabel = new QLabel(link.host());
}
