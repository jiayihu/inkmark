#ifndef INKMARK_APPLICATION_H
#define INKMARK_APPLICATION_H

#include <QWidget>
#include <QVector>
#include <QCloseEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "models/bookmark_model.h"
#include "models/user_model.h"
#include "views/auth_view/auth_view.h"
#include "views/users/user_application_view/user_application_view.h"
#include "views/admin/admin_application_view/admin_application_view.h"

/**
 * Classe ApplicationView che si occupa di istanziare e gestire le sotto-views
 * per le aree utente, admin e autenticazione
 */
class ApplicationView: public QWidget {
 Q_OBJECT

 private:
  AuthView *authView;
  AdminApplicationView *adminApplicationView;
  UserApplicationView *userApplicationView;

  QWidget *errorBox;
  QLabel *errorLabel;
  QWidget *containerArea;
  // Layout contenitori dei menu/content delle aree utente e admin
  QLayout *appLayout;
  QLayout *menuLayout;
  QLayout *contentLayout;

  // Widget menu/content delle aree utente e admin
  QWidget *userMenu;
  QWidget *userContent;
  QWidget *adminMenu;
  QWidget *adminContent;

  QString getApplicationStyles() const;
  QString getMenuStyle() const;
  QLayout *createAppLayout() const;
  QWidget *createErrorBox();
  QWidget *createMenu();
  QWidget *createContent();
  QWidget *createContainerArea();

  void setUserAreaVisible(bool visible) const;
  void setAdminAreaVisible(bool visible) const;

 private slots:
  void hideErrorBox() const;

 public:
  ApplicationView(QWidget *parent = nullptr);

  AuthView* getAuthView() const;
  AdminApplicationView* getAdminApplicationView() const;
  UserApplicationView* getUserApplicationView() const;

  void closeEvent(QCloseEvent *event) override;

 public slots:
  void showError(QString message) const;
  void showUserArea(UserInterface *user) const;
  void showAdminArea(UserInterface *user) const;
  void hideContainerArea() const;

  signals:
    void applicationClosed();
};

#endif //INKMARK_APPLICATION_H
