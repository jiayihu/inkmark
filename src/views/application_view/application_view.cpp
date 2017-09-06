#include <QSizePolicy>
#include <QHBoxLayout>
#include <QDebug>
#include <QTimer>
#include <utilities/utilities.h>
#include "application_view.h"

QString ApplicationView::getApplicationStyles() const {
  return "background-color: #FCFCFC;";
}

QString ApplicationView::getMenuStyle() const {
  return "ButtonWidget { margin-left: 15px; }";
}

QLayout* ApplicationView::createAppLayout() const {
  QVBoxLayout *layout = new QVBoxLayout();
  // Layout di dimensione sempre al minimo in base al contenuto
  layout->setSizeConstraint(QLayout::SetFixedSize);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);
  layout->setAlignment(Qt::AlignTop);

  return layout;
}

QWidget * ApplicationView::createErrorBox() {
  QHBoxLayout *layout= new QHBoxLayout();

  errorLabel = new QLabel();

  ButtonWidget *closeButton = new ButtonWidget("Close");
  closeButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  QObject::connect(closeButton, SIGNAL(clicked()), this, SLOT(hideErrorBox()));

  layout->addWidget(errorLabel);
  layout->addWidget(closeButton);

  errorBox = wrapInWidget(layout);
  errorBox->setStyleSheet("background-color: #D4411A; color: #fff;");
  errorBox->setVisible(false);

  return errorBox;
}

QWidget* ApplicationView::createMenu() {
  QWidget *menuContainer = new QWidget();
  menuContainer->setObjectName("menu");
  menuContainer->setStyleSheet(getMenuStyle());
  menuContainer->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));

  menuLayout = new QVBoxLayout();
  menuLayout->setContentsMargins(0, 0, 0, 0);

  userMenu = userApplicationView->createMenu();
  adminMenu = adminApplicationView->createMenu();

  menuLayout->addWidget(userMenu);
  menuLayout->addWidget(adminMenu);

  menuContainer->setLayout(menuLayout);
  return menuContainer;
}

QWidget* ApplicationView::createContent() {
  QWidget *contentContainer = new QWidget();
  contentContainer->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

  contentLayout = new QVBoxLayout();
  contentLayout->setContentsMargins(0, 0, 0, 0);

  userContent = userApplicationView->createContent();
  adminContent = adminApplicationView->createContent();

  contentLayout->addWidget(userContent);
  contentLayout->addWidget(adminContent);

  contentContainer->setLayout(contentLayout);
  return contentContainer;
}

QWidget* ApplicationView::createContainerArea() {
  QWidget *containerArea = new QWidget();
  QVBoxLayout *layout = new QVBoxLayout();
  layout->setContentsMargins(0, 0, 0, 0);

  QWidget *menuContainer = createMenu();
  QWidget *contentContainer = createContent();
  layout->addWidget(menuContainer);
  layout->addWidget(contentContainer);

  containerArea->setLayout(layout);
  return containerArea;
}

void ApplicationView::hideErrorBox() const {
  errorLabel->clear();
  errorBox->setVisible(false);
}

void ApplicationView::setUserAreaVisible(bool visible) const {
  userMenu->setVisible(visible);
  userContent->setVisible(visible);
}

void ApplicationView::setAdminAreaVisible(bool visible) const {
  adminMenu->setVisible(visible);
  adminContent->setVisible(visible);
}

ApplicationView::ApplicationView(QWidget *parent)
  : QWidget(parent),
    authView(new AuthView()),
    adminApplicationView(new AdminApplicationView()),
    userApplicationView(new UserApplicationView()){
  setWindowTitle("Inkmark");
  setStyleSheet(getApplicationStyles());
  setMinimumSize(768, 480);

  appLayout = createAppLayout();

  containerArea = createContainerArea();
  containerArea->setVisible(false);

  appLayout->addWidget(createErrorBox());
  appLayout->addWidget(authView);
  setLayout(appLayout);
}

AuthView* ApplicationView::getAuthView() const {
  return authView;
}

AdminApplicationView* ApplicationView::getAdminApplicationView() const {
  return adminApplicationView;
}

UserApplicationView* ApplicationView::getUserApplicationView() const {
  return userApplicationView;
}

void ApplicationView::closeEvent(QCloseEvent *event) {
  emit applicationClosed();
  event->accept();
}

void ApplicationView::showError(QString message) const {
  errorLabel->setText(message);
  errorBox->setVisible(true);
}

void ApplicationView::showUserArea(UserInterface *user) const {
  setAdminAreaVisible(false);
  setUserAreaVisible(true);

  appLayout->removeWidget(authView);
  appLayout->addWidget(containerArea);
  authView->setVisible(false);
  containerArea->setVisible(true);

  userApplicationView->setUser(user);
}

void ApplicationView::showAdminArea(UserInterface *user) const {
  setUserAreaVisible(false);
  setAdminAreaVisible(true);

  appLayout->removeWidget(authView);
  appLayout->addWidget(containerArea);
  authView->setVisible(false);
  containerArea->setVisible(true);

  adminApplicationView->setUser(user);
}

void ApplicationView::hideContainerArea() const {
  appLayout->removeWidget(containerArea);
  appLayout->addWidget(authView);
  authView->setVisible(true);
  containerArea->setVisible(false);

  userApplicationView->setUser(nullptr);
  adminApplicationView->setUser(nullptr);
}
