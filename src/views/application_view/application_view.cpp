#include <QPushButton>
#include "application_view.h"
#include "widgets/button_widget/button_widget.h"

void ApplicationView::toggleAddViewVisibility() {
  bool visibility = addBookmarkView->isVisible();
  addBookmarkView->setVisible(!visibility);
}

ApplicationView::ApplicationView(QWidget *parent): QWidget(parent) {
  setWindowTitle("Inkmark");
  setStyleSheet("background-color: #FFFFFF;");
  setMinimumSize(768, 480);

  QVBoxLayout *containerLayout = new QVBoxLayout();

  QHBoxLayout *menuLayout = new QHBoxLayout();
  ButtonWidget *addBookmarkButton = new ButtonWidget("Add bookmark");
  QObject::connect(addBookmarkButton, SIGNAL(clicked()), this, SLOT(toggleAddViewVisibility()));
  ButtonWidget *searchButton = new ButtonWidget("Search bookmark");
  menuLayout->addWidget(addBookmarkButton);
  menuLayout->addWidget(searchButton);

  QHBoxLayout *contentLayout = new QHBoxLayout();

  addBookmarkView = new AddBookmarkView;
  addBookmarkView->setVisible(false);
  QObject::connect(addBookmarkView, SIGNAL(submitClicked(QString, QString, QString)), this, SLOT(toggleAddViewVisibility()));

  bookmarksListView = new BookmarksListView;
  contentLayout->addWidget(addBookmarkView);
  contentLayout->addWidget(bookmarksListView);

  containerLayout->addLayout(menuLayout);
  containerLayout->addLayout(contentLayout);

  setLayout(containerLayout);
}

AddBookmarkView* ApplicationView::getAddBookmarkView() const {
  return addBookmarkView;
}

BookmarksListView* ApplicationView::getBookmarkListView() const {
  return bookmarksListView;
}

void ApplicationView::closeEvent(QCloseEvent *event) {
  emit applicationClosed();
  event->accept();
}
