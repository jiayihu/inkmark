#include <QSizePolicy>
#include <QDebug>
#include <QTimer>
#include "application_view.h"

QString ApplicationView::getApplicationStyles() const {
  return "background-color: #FCFCFC;";
}

QString ApplicationView::getMenuStyle() const {
  return
    "QWidget#menu { background-color: #4C5052; }"
    "ButtonWidget { margin-left: 15px; }";
}

QVBoxLayout* ApplicationView::createAppLayout() const {
  QVBoxLayout *appLayout = new QVBoxLayout();
  // Layout di dimensione sempre al minimo in base al contenuto
  appLayout->setSizeConstraint(QLayout::SetFixedSize);
  appLayout->setContentsMargins(0, 0, 0, 0);
  appLayout->setSpacing(0);
  appLayout->setAlignment(Qt::AlignTop);

  return appLayout;
}

QWidget* ApplicationView::createMenu() const {
  QWidget *menuContainer = new QWidget();
  menuContainer->setObjectName("menu");
  menuContainer->setStyleSheet(getMenuStyle());
  menuContainer->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));

  QHBoxLayout *menuLayout = new QHBoxLayout(menuContainer);
  menuLayout->setAlignment(Qt::AlignLeft);

  ButtonWidget *addBookmarkButton = new ButtonWidget("Add bookmark");
  QObject::connect(addBookmarkButton, SIGNAL(clicked()), this, SLOT(toggleAddViewVisibility()));

  ButtonWidget *searchButton = new ButtonWidget("Search bookmark");
  QObject::connect(searchButton, SIGNAL(clicked()), this, SLOT(toggleSearchViewVisibility()));

  menuLayout->addWidget(addBookmarkButton);
  menuLayout->addWidget(searchButton);

  return menuContainer;
}

QWidget* ApplicationView::createContent() {
  QWidget *contentContainer = new QWidget();
  contentContainer->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
  QHBoxLayout *contentLayout = new QHBoxLayout(contentContainer);

  addBookmarkView = new AddBookmarkView();
  addBookmarkView->setVisible(false);
  QObject::connect(addBookmarkView, SIGNAL(cancelClicked()), this, SLOT(toggleAddViewVisibility()));
  QObject::connect(addBookmarkView, SIGNAL(submitClicked(QString, QString, QString)), this, SLOT(toggleAddViewVisibility()));

  searchBookmarkView = new SearchBookmarkView();
  searchBookmarkView->setVisible(false);
  QObject::connect(searchBookmarkView, SIGNAL(clickedCancel()), this, SLOT(toggleSearchViewVisibility()));

  bookmarksListView = new BookmarksListView();
  contentLayout->addWidget(addBookmarkView);
  contentLayout->addWidget(searchBookmarkView);
  contentLayout->addWidget(bookmarksListView);

  return contentContainer;
}

void ApplicationView::toggleAddViewVisibility() {
  if (searchBookmarkView->isVisible()) searchBookmarkView->setVisible(false);

  bool visibility = addBookmarkView->isVisible();
  addBookmarkView->setVisible(!visibility);
  QTimer::singleShot(0, this, SLOT(resizeToMin()));
}

void ApplicationView::toggleSearchViewVisibility() {
  if (addBookmarkView->isVisible()) addBookmarkView->setVisible(false);

  bool visibility = searchBookmarkView->isVisible();
  searchBookmarkView->setVisible(!visibility);
  QTimer::singleShot(0, this, SLOT(resizeToMin()));
}

void ApplicationView::resizeToMin() { adjustSize(); }

ApplicationView::ApplicationView(QWidget *parent): QWidget(parent) {
  setWindowTitle("Inkmark");
  setStyleSheet(getApplicationStyles());
  setMinimumSize(768, 480);

  QVBoxLayout *appLayout = createAppLayout();

  QWidget *menuContainer = createMenu();
  QWidget *contentContainer = createContent();
  appLayout->addWidget(menuContainer);
  appLayout->addWidget(contentContainer);

  setLayout(appLayout);
}

AddBookmarkView* ApplicationView::getAddBookmarkView() const { return addBookmarkView; }

BookmarksListView* ApplicationView::getBookmarkListView() const { return bookmarksListView; }

SearchBookmarkView* ApplicationView::getSearchBookmarkView() const { return searchBookmarkView; }

void ApplicationView::closeEvent(QCloseEvent *event) {
  emit applicationClosed();
  event->accept();
}
