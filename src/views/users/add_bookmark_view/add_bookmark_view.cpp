#include <QLabel>
#include <QVBoxLayout>
#include "add_bookmark_view.h"
#include "widgets/button_widget/button_widget.h"

void AddBookmarkView::handleSubmitClick() {
  QString name = nameInput->text();
  QString link = linkInput->text();
  QString description = descriptionTextArea->toPlainText();

  emit submitClicked(name, link, description);
}

AddBookmarkView::AddBookmarkView(QWidget *parent): QWidget(parent) {
  QVBoxLayout *layout = new QVBoxLayout();
  nameInput = new TextInputWidget();
  linkInput = new TextInputWidget();
  descriptionTextArea = new TextAreaWidget();

  layout->addWidget(new QLabel("Name"));
  layout->addWidget(nameInput);
  layout->addWidget(new QLabel("Url"));
  layout->addWidget(linkInput);
  layout->addWidget(new QLabel("Description"));
  layout->addWidget(descriptionTextArea);

  QHBoxLayout *buttonsLayout = new QHBoxLayout();
  ButtonWidget *cancelButton = new ButtonWidget("Cancel");
  QObject::connect(cancelButton, SIGNAL(clicked()), this, SIGNAL(cancelClicked()));
  ButtonWidget *submitButton = new ButtonWidget("Add bookmark");
  QObject::connect(submitButton, SIGNAL(clicked()), this, SLOT(handleSubmitClick()));
  buttonsLayout->setAlignment(Qt::AlignLeft);
  buttonsLayout->addWidget(cancelButton);
  buttonsLayout->addWidget(submitButton);
  layout->addLayout(buttonsLayout);

  setLayout(layout);
}

void AddBookmarkView::clear() const {
  nameInput->clear();
  linkInput->clear();
  descriptionTextArea->clear();
}
