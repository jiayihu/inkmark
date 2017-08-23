#include <QHBoxLayout>
#include "bookmark_view.h"

QWidget* BookmarkView::createContent() {
  QWidget *contentContainer = new QWidget();
  QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  sizePolicy.setHorizontalStretch(1);
  contentContainer->setSizePolicy(sizePolicy);
  QVBoxLayout *layout = new QVBoxLayout(contentContainer);

  nameLink = new LinkWidget();
  nameLink->setStyleSheet("font-size: 18px;");
  descriptionLabel = new QLabel();
  descriptionLabel->setWordWrap(true);
  layout->addWidget(nameLink);
  layout->addWidget(descriptionLabel);

  return contentContainer;
}

QLabel* BookmarkView::createHostLabel() const {
  QLabel *hostLabel = new QLabel();
  hostLabel->setStyleSheet("font-size: 14px; color: #999;");
  QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  sizePolicy.setHorizontalStretch(0);
  hostLabel->setSizePolicy(sizePolicy);

  return hostLabel;
}

QWidget* BookmarkView::createButtons() {
  QWidget *buttonsContainer = new QWidget();
  QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  sizePolicy.setHorizontalStretch(0);
  buttonsContainer->setSizePolicy(sizePolicy);

  QHBoxLayout *layout = new QHBoxLayout(buttonsContainer);

  deleteButton = new ButtonWidget("Delete");
  QObject::connect(deleteButton, SIGNAL(clicked()), this, SLOT(handleDeleteClick()));
  editButton = new ButtonWidget("Edit");
  QObject::connect(editButton, SIGNAL(clicked()), this, SLOT(handleEditClick()));

  layout->addWidget(deleteButton);
  layout->addWidget(editButton);

  return buttonsContainer;
}

void BookmarkView::handleDeleteClick() { emit clickedDelete(model); }

void BookmarkView::handleEditClick() { emit clickedEdit(model); }

BookmarkView::BookmarkView(QWidget *parent): model(nullptr), QWidget(parent) {
  setFixedWidth(640);
  setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

  QHBoxLayout *layout = new QHBoxLayout();

  QWidget *contentContainer = createContent();
  hostLabel = createHostLabel();
  QWidget *buttonsContainer = createButtons();

  layout->addWidget(contentContainer);
  layout->addWidget(hostLabel);
  layout->addWidget(buttonsContainer);

  setLayout(layout);
}

void BookmarkView::setPrivilegies(bool canEdit, bool canDelete) const {
  editButton->setVisible(canEdit);
  deleteButton->setVisible(canDelete);
}

void BookmarkView::setModel(BookmarkInterface *newModel) {
  model = newModel;

  QUrl link = model->getLink();
  nameLink->setText(model->getName());
  nameLink->setUrl(link);
  descriptionLabel->setText(model->getDescription());
  hostLabel->setText(link.host());
}
