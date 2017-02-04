#include <QFormLayout>
#include <QPushButton>
#include "edit_bookmark_view.h"
#include "widgets/button_widget/button_widget.h"

void EditBookmarkView::handleEditClick() {
  QString name = nameInput->text();
  QString link = linkInput->text();
  QString description = descriptionTextArea->toPlainText();

  emit saveClicked(model, name, link, description);
}

EditBookmarkView::EditBookmarkView(QWidget *parent): QWidget(parent) {
  QFormLayout *formLayout = new QFormLayout;
  nameInput = new TextInputWidget();
  linkInput = new TextInputWidget();
  descriptionTextArea = new TextAreaWidget();
  ButtonWidget *cancelButton = new ButtonWidget("Cancel");
  QObject::connect(cancelButton, SIGNAL(clicked()), this, SIGNAL(cancelClicked()));
  ButtonWidget *editButton = new ButtonWidget("Save bookmark");
  QObject::connect(editButton, SIGNAL(clicked()), this, SLOT(handleEditClick()));

  formLayout->addRow("Name: ", nameInput);
  formLayout->addRow("Link: ", linkInput);
  formLayout->addRow("Description", descriptionTextArea);
  formLayout->addWidget(cancelButton);
  formLayout->addWidget(editButton);

  setLayout(formLayout);
}

void EditBookmarkView::setModel(BookmarkModel *newModel) {
  model = newModel;

  nameInput->setText(model->getName());
  linkInput->setText(model->getLink().toString());
  descriptionTextArea->setText(model->getDescription());
}
