#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>
#include <QFormLayout>
#include "add_bookmark_view.h"
#include "widgets/button_widget/button_widget.h"
#include "utilities/utilities.h"

QWidget* AddBookmarkView::createTypeSelect() {
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

QWidget* AddBookmarkView::createArticleFields() {
  QFormLayout *layout = new QFormLayout();
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setFormAlignment(Qt::AlignLeft);
  layout->setLabelAlignment(Qt::AlignLeft);

  pubblicationInput = new QDateEdit(QDate::currentDate());
  pubblicationInput->setCalendarPopup(true);
  pubblicationInput->setDisplayFormat("dd MMMM yyyy");
  pubblicationInput->setMaximumDate(QDate::currentDate());
  pubblicationInput->setStyleSheet("padding: 5px 10px;");

  minReadInput = new QTimeEdit();
  minReadInput->setStyleSheet("border: 1px solid #e3e1e1; border-radius: 3px; padding: 5px 10px;");

  layout->addRow("Pubblication date", pubblicationInput);
  layout->addRow("Min to read", minReadInput);

  articleFields = wrapInWidget(layout);
  articleFields->setVisible(false);

  return articleFields;
}

QWidget* AddBookmarkView::createVideoFields() {
  QFormLayout *layout = new QFormLayout();
  layout->setContentsMargins(0, 10, 0, 10);
  layout->setFormAlignment(Qt::AlignLeft);
  layout->setLabelAlignment(Qt::AlignLeft);

  durationInput = new QTimeEdit();
  durationInput->setStyleSheet("border: 1px solid #e3e1e1; border-radius: 3px; padding: 5px 10px;");
  layout->addRow("Duration", durationInput);

  videoFields = wrapInWidget(layout);
  videoFields->setVisible(false);

  return videoFields;
}

QWidget* AddBookmarkView::createFields() {
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

  layout->addWidget(createTypeSelect());
  layout->addWidget(createArticleFields());
  layout->addWidget(createVideoFields());

  return wrapInWidget(layout);
}

QWidget* AddBookmarkView::createButtons() {
  QHBoxLayout *layout = new QHBoxLayout();
  ButtonWidget *cancelButton = new ButtonWidget("Cancel");
  QObject::connect(cancelButton, SIGNAL(clicked()), this, SIGNAL(cancelClicked()));
  ButtonWidget *submitButton = new ButtonWidget("Save bookmark");
  QObject::connect(submitButton, SIGNAL(clicked()), this, SLOT(handleSubmitClick()));
  layout->addWidget(cancelButton);
  layout->addWidget(submitButton);

  return wrapInWidget(layout);
}

void AddBookmarkView::handleTypeChange(const QString &typeString) {
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
    qWarning() << "AddBookmarkView::handleTypeChange(): Umknown bookmark type passed";
  }
}

void AddBookmarkView::handleSubmitClick() {
  QString name = nameInput->text();
  QString link = linkInput->text();
  QString description = descriptionTextArea->toPlainText();
  BookmarkType type = stringToBookmarkType(typeSelect->currentText());
  QDate pubblication = pubblicationInput->date();
  QTime minRead = minReadInput->time();
  QTime duration = durationInput->time();

  if (!model) emit addClicked(name, link, description, type, pubblication, minRead, duration);
  else emit editClicked(model, name, link, description, type, pubblication, minRead, duration);
}

AddBookmarkView::AddBookmarkView(QWidget *parent): QWidget(parent) {
  QVBoxLayout *layout = new QVBoxLayout();
  layout->setAlignment(Qt::AlignLeft);

  layout->addWidget(createFields());
  layout->addWidget(createButtons());

  setLayout(layout);
}

void AddBookmarkView::setModel(BookmarkInterface *newModel) {
  model = newModel;

  nameInput->setText(model->getName());
  linkInput->setText(model->getLink().toString());
  descriptionTextArea->setText(model->getDescription());
}

void AddBookmarkView::clear() const {
  nameInput->clear();
  linkInput->clear();
  descriptionTextArea->clear();
  pubblicationInput->setDate(QDate::currentDate());
  minReadInput->setTime(QTime(0, 0, 0, 0));
  durationInput->setTime(QTime(0, 0, 0, 0));
}
