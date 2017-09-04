#include <QDebug>
#include <QHBoxLayout>
#include "bookmark_view.h"
#include "utilities/utilities.h"

void BookmarkView::setMetadataStyles(QLabel *label) {
  label->setStyleSheet("font-size: 14px; color: #999;");
  label->setVisible(false);
  label->setAlignment(Qt::AlignRight);
}

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

QWidget* BookmarkView::createMetadata() {
  QVBoxLayout *layout = new QVBoxLayout();
  layout->setSpacing(0);

  hostLabel = new QLabel();
  setMetadataStyles(hostLabel);
  hostLabel->setVisible(true);
  layout->addWidget(hostLabel);

  // Label specifiche del tipo di bookmark
  publicationLabel = new QLabel();
  setMetadataStyles(publicationLabel);
  minReadLabel = new QLabel();
  setMetadataStyles(minReadLabel);
  durationLabel = new QLabel();
  setMetadataStyles(durationLabel);

  layout->addWidget(publicationLabel);
  layout->addWidget(minReadLabel);
  layout->addWidget(durationLabel);

  return wrapInWidget(layout);
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
  QWidget *buttonsContainer = createButtons();

  layout->addWidget(contentContainer);
  layout->addWidget(createMetadata());
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
  nameLink->setText("🔗 " + model->getName());
  nameLink->setUrl(link);
  descriptionLabel->setText(model->getDescription());
  hostLabel->setText(link.host());

  // Campi dati specifici del tipo di bookmark
  ArticleInterface *articleBookmark = dynamic_cast<ArticleInterface *>(model);
  VideoInterface *videoBookmark = dynamic_cast<VideoInterface *>(model);

  if (articleBookmark) {
    nameLink->setText("📖 " + model->getName());
    publicationLabel->setText("📆 " + articleBookmark->getPublication().toString("dd MMMM yyyy"));
    publicationLabel->setVisible(true);
    minReadLabel->setText("⏱ " + articleBookmark->getMinRead().toString("mm:ss"));
    minReadLabel->setVisible(true);
  } else if (videoBookmark) {
    nameLink->setText("🖥 " + model->getName());
    durationLabel->setText("⏱ " + videoBookmark->getDuration().toString("mm:ss"));
    durationLabel->setVisible(true);
  }
}
