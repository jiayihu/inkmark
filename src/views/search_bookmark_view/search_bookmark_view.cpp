#include <QFormLayout>
#include "search_bookmark_view.h"

void SearchBookmarkView::handleSearchClick() {
  QString searchText = searchInput->text();
  emit clickedSearch(searchText);
}

SearchBookmarkView::SearchBookmarkView(QWidget *parent): QWidget(parent) {
  QFormLayout *formLayout = new QFormLayout();

  searchInput = new TextInputWidget();
  formLayout->addRow("Search text: ", searchInput);
  ButtonWidget *searchButton = new ButtonWidget("Search");
  ButtonWidget *cancelButton = new ButtonWidget("Cancel");
  QObject::connect(searchButton, SIGNAL(clicked()), this, SLOT(handleSearchClick()));
  QObject::connect(cancelButton, SIGNAL(clicked()), this, SIGNAL(clickedCancel()));
  formLayout->addWidget(searchButton);
  formLayout->addWidget(cancelButton);

  setLayout(formLayout);
}
