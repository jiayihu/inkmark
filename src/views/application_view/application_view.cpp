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

  QLayout *menuLayout = userApplicationView->createMenu();
  menuContainer->setLayout(menuLayout);

  return menuContainer;
}

QWidget* ApplicationView::createContent() {
  QWidget *contentContainer = new QWidget();
  contentContainer->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
  QLayout *contentLayout = userApplicationView->createContent();
  contentContainer->setLayout(contentLayout);

  return contentContainer;
}

void ApplicationView::resizeToMin() { adjustSize(); }

ApplicationView::ApplicationView(QWidget *parent)
  : QWidget(parent), userApplicationView(new UserApplicationView()) {
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

UserApplicationView* ApplicationView::getUserApplicationView() const {
  return userApplicationView;
}

void ApplicationView::closeEvent(QCloseEvent *event) {
  emit applicationClosed();
  event->accept();
}
