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
  QObject::connect(searchButton, SIGNAL(clicked()), this, SLOT(handleSearchClick()));
  formLayout->addWidget(searchButton);

  setLayout(formLayout);
}
