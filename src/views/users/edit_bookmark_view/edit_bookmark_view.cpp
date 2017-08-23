#include <QFormLayout>
#include <QLabel>
#include "edit_bookmark_view.h"
#include "widgets/button_widget/button_widget.h"

void EditBookmarkView::handleEditClick() {
  QString name = nameInput->text();
  QString link = linkInput->text();
  QString description = descriptionTextArea->toPlainText();

  emit saveClicked(model, name, link, description);
}

EditBookmarkView::EditBookmarkView(QWidget *parent): QWidget(parent) {
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
  ButtonWidget *editButton = new ButtonWidget("Save bookmark");
  QObject::connect(editButton, SIGNAL(clicked()), this, SLOT(handleEditClick()));
  buttonsLayout->setAlignment(Qt::AlignLeft);
  buttonsLayout->addWidget(cancelButton);
  buttonsLayout->addWidget(editButton);
  layout->addLayout(buttonsLayout);

  setLayout(layout);
}

void EditBookmarkView::setModel(BookmarkInterface *newModel) {
  model = newModel;

  nameInput->setText(model->getName());
  linkInput->setText(model->getLink().toString());
  descriptionTextArea->setText(model->getDescription());
}
