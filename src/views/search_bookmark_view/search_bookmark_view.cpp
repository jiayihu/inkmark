#include <QVBoxLayout>
#include <QLabel>
#include "search_bookmark_view.h"

void SearchBookmarkView::handleSearchClick() {
  QString searchText = searchInput->text();
  emit clickedSearch(searchText);
}

SearchBookmarkView::SearchBookmarkView(QWidget *parent): QWidget(parent) {
  QVBoxLayout *layout = new QVBoxLayout();
  layout->setAlignment(Qt::AlignTop);

  searchInput = new TextInputWidget();
  layout->addWidget(new QLabel("Search text: "));;
  layout->addWidget(searchInput);
  ButtonWidget *searchButton = new ButtonWidget("Search");
  ButtonWidget *cancelButton = new ButtonWidget("Cancel");
  QObject::connect(searchButton, SIGNAL(clicked()), this, SLOT(handleSearchClick()));
  QObject::connect(cancelButton, SIGNAL(clicked()), this, SIGNAL(clickedCancel()));

  QHBoxLayout *buttonsLayout = new QHBoxLayout();
  buttonsLayout->setAlignment(Qt::AlignLeft);
  buttonsLayout->addWidget(cancelButton);
  buttonsLayout->addWidget(searchButton);
  layout->addLayout(buttonsLayout);

  setLayout(layout);
}
