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

QWidget* ApplicationView::createContent() const {
  QWidget *contentContainer = new QWidget();
  contentContainer->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
  QLayout *contentLayout = userApplicationView->createContent();
  contentContainer->setLayout(contentLayout);

  return contentContainer;
}

QWidget* ApplicationView::createUserArea() const {
  QWidget *userArea = new QWidget();
  QVBoxLayout *userAreaLayout = new QVBoxLayout();
  userAreaLayout->setContentsMargins(0, 0, 0, 0);

  QWidget *menuContainer = createMenu();
  QWidget *contentContainer = createContent();
  userAreaLayout->addWidget(menuContainer);
  userAreaLayout->addWidget(contentContainer);

  userArea->setLayout(userAreaLayout);
  return userArea;
}

void ApplicationView::resizeToMin() { adjustSize(); }

ApplicationView::ApplicationView(QWidget *parent)
  : QWidget(parent), authView(new AuthView()), userApplicationView(new UserApplicationView()) {
  setWindowTitle("Inkmark");
  setStyleSheet(getApplicationStyles());
  setMinimumSize(768, 480);

  appLayout = createAppLayout();

  userArea = createUserArea();
  userArea->setVisible(false);

  appLayout->addWidget(authView);
  setLayout(appLayout);
}

AuthView* ApplicationView::getAuthView() const {
  return authView;
}

UserApplicationView* ApplicationView::getUserApplicationView() const {
  return userApplicationView;
}

void ApplicationView::closeEvent(QCloseEvent *event) {
  emit applicationClosed();
  event->accept();
}

void ApplicationView::setUser(UserInterface *user) const {
  appLayout->removeWidget(authView);
  appLayout->addWidget(userArea);
  userArea->setVisible(true);
}

void ApplicationView::removeUser() const {
  appLayout->removeWidget(userArea);
  appLayout->addWidget(authView);
  userArea->setVisible(false);
}
