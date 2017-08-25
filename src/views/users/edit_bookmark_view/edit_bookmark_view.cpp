#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>
#include <QFormLayout>
#include "edit_bookmark_view.h"
#include "widgets/button_widget/button_widget.h"
#include "utilities/utilities.h"

QWidget* EditBookmarkView::createTypeSelect() {
  QFormLayout *layout = new QFormLayout();
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setFormAlignment(Qt::AlignLeft);

  typeSelect = new QComboBox();
  typeSelect->addItem(bookmarkTypeToString(BookmarkType::none));
  typeSelect->addItem(bookmarkTypeToString(BookmarkType::article));
  typeSelect->addItem(bookmarkTypeToString(BookmarkType::video));

  typeSelect->setStyleSheet(
    "QComboBox {"
      "border: 1px solid #e3e1e1;"
      "border-radius: 3px;"
      "padding: 5px 10px;"
      "min-width: 60px;"
      "}"
    "QComboBox QAbstractItemView {"
      "line-height: 20px;"
      "selection-color: #54C0C0;"
    "}"
  );

  QObject::connect(typeSelect, SIGNAL(currentTextChanged(QString)), this, SLOT(handleTypeChange(QString)));

  layout->addRow(new QLabel("Bookmark type"), typeSelect);

  return wrapInWidget(layout);
}

QWidget* EditBookmarkView::createArticleFields() {
  QFormLayout *layout = new QFormLayout();
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setFormAlignment(Qt::AlignLeft);
  layout->setLabelAlignment(Qt::AlignLeft);

  publicationInput = new QDateEdit(QDate::currentDate());
  publicationInput->setCalendarPopup(true);
  publicationInput->setDisplayFormat("dd MMMM yyyy");
  publicationInput->setMaximumDate(QDate::currentDate());
  publicationInput->setStyleSheet("padding: 5px 10px;");

  minReadInput = new QTimeEdit();
  minReadInput->setDisplayFormat("mm:ss");
  minReadInput->setStyleSheet("border: 1px solid #e3e1e1; border-radius: 3px; padding: 5px 10px;");

  layout->addRow("Pubblication date", publicationInput);
  layout->addRow("Min to read", minReadInput);

  articleFields = wrapInWidget(layout);
  articleFields->setVisible(false);

  return articleFields;
}

QWidget* EditBookmarkView::createVideoFields() {
  QFormLayout *layout = new QFormLayout();
  layout->setContentsMargins(0, 10, 0, 10);
  layout->setFormAlignment(Qt::AlignLeft);
  layout->setLabelAlignment(Qt::AlignLeft);

  durationInput = new QTimeEdit();
  durationInput->setDisplayFormat("mm:ss");
  durationInput->setStyleSheet("border: 1px solid #e3e1e1; border-radius: 3px; padding: 5px 10px;");
  layout->addRow("Duration", durationInput);

  videoFields = wrapInWidget(layout);
  videoFields->setVisible(false);

  return videoFields;
}

QWidget* EditBookmarkView::createFields() {
  QVBoxLayout *layout = new QVBoxLayout();

  nameInput = new TextInputWidget();
  linkInput = new TextInputWidget();
  descriptionTextArea = new TextAreaWidget();
  descriptionTextArea->setFixedHeight(96);

  layout->addWidget(new QLabel("Name"));
  layout->addWidget(nameInput);
  layout->addWidget(new QLabel("Url"));
  layout->addWidget(linkInput);
  layout->addWidget(new QLabel("Description"));
  layout->addWidget(descriptionTextArea);

  typeField = createTypeSelect();
  layout->addWidget(typeField);
  layout->addWidget(createArticleFields());
  layout->addWidget(createVideoFields());

  return wrapInWidget(layout);
}

QWidget* EditBookmarkView::createButtons() {
  QHBoxLayout *layout = new QHBoxLayout();
  ButtonWidget *cancelButton = new ButtonWidget("Cancel");
  QObject::connect(cancelButton, SIGNAL(clicked()), this, SIGNAL(cancelClicked()));
  ButtonWidget *submitButton = new ButtonWidget("Save bookmark");
  QObject::connect(submitButton, SIGNAL(clicked()), this, SLOT(handleSubmitClick()));
  layout->addWidget(cancelButton);
  layout->addWidget(submitButton);

  return wrapInWidget(layout);
}

void EditBookmarkView::handleTypeChange(const QString &typeString) {
  BookmarkType type = stringToBookmarkType(typeString);

  if (type == BookmarkType::none) {
    articleFields->setVisible(false);
    videoFields->setVisible(false);
  } else if (type == BookmarkType::article) {
    articleFields->setVisible(true);
    videoFields->setVisible(false);
  } else if (type == BookmarkType::video) {
    articleFields->setVisible(false);
    videoFields->setVisible(true);
  } else {
    qWarning() << "EditBookmarkView::handleTypeChange(): Umknown bookmark type passed";
  }
}

void EditBookmarkView::handleSubmitClick() {
  QString name = nameInput->text();
  QString link = linkInput->text();
  QString description = descriptionTextArea->toPlainText();
  BookmarkType type = stringToBookmarkType(typeSelect->currentText());
  QDate pubblication = publicationInput->date();
  QTime minRead = minReadInput->time();
  QTime duration = durationInput->time();

  if (!model) emit addClicked(name, link, description, type, pubblication, minRead, duration);
  else emit editClicked(model, name, link, description, pubblication, minRead, duration);
}

EditBookmarkView::EditBookmarkView(QWidget *parent): QWidget(parent) {
  QVBoxLayout *layout = new QVBoxLayout();
  layout->setAlignment(Qt::AlignLeft);

  layout->addWidget(createFields());
  layout->addWidget(createButtons());

  setLayout(layout);
}

void EditBookmarkView::setModel(BookmarkInterface *newModel) {
  model = newModel;

  nameInput->setText(model->getName());
  linkInput->setText(model->getLink().toString());
  descriptionTextArea->setText(model->getDescription());

  typeField->setVisible(false);
  typeSelect->setCurrentText(bookmarkTypeToString(newModel->getType()));

  ArticleInterface *article = dynamic_cast<ArticleInterface*>(newModel);
  VideoInterface *video = dynamic_cast<VideoInterface*>(newModel);

  if (article) {
    publicationInput->setDate(article->getPublication());
    minReadInput->setTime(article->getMinRead());
  } else if (video) {
    durationInput->setTime(video->getDuration());
  }
}

void EditBookmarkView::clear() const {
  nameInput->clear();
  linkInput->clear();
  descriptionTextArea->clear();
  publicationInput->setDate(QDate::currentDate());
  minReadInput->setTime(QTime(0, 0, 0, 0));
  durationInput->setTime(QTime(0, 0, 0, 0));
}
