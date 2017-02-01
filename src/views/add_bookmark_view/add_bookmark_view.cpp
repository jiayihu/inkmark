#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include "add_bookmark_view.h"

void AddBookmarkView::handleSubmitClick() {
  QString name = nameInput->text();
  QString link = linkInput->text();
  QString description = descriptionTextArea->toPlainText();

  emit submitClicked(name, link, description);
}

AddBookmarkView::AddBookmarkView(QWidget *parent): QWidget(parent) {
  QFormLayout *formLayout = new QFormLayout;
  nameInput = new QLineEdit;
  nameInput->setMinimumWidth(200);
  linkInput = new QLineEdit;
  linkInput->setMinimumWidth(200);
  descriptionTextArea = new QTextEdit;
  descriptionTextArea->setMinimumWidth(300);
  // Al copy-paste incolla il testo senza formattazione
  descriptionTextArea->setAcceptRichText(false);
  QPushButton *submit = new QPushButton("Add bookmark");

  formLayout->addRow("Name: ", nameInput);
  formLayout->addRow("Link: ", linkInput);
  formLayout->addRow("Description", descriptionTextArea);
  formLayout->addWidget(submit);

  QObject::connect(submit, SIGNAL(clicked()), this, SLOT(handleSubmitClick()));

  setLayout(formLayout);
}
