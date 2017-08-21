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
#include "views/user_application_view/user_application_view.h"

/**
 * Classe View che si occupa di istanziare le classi view figlie e del layout
 * generale come il menu
 */
class ApplicationView: public QWidget {
 Q_OBJECT

 private:
  AuthView *authView;
  QWidget *userArea;
  UserApplicationView *userApplicationView;
  QVBoxLayout *appLayout;

  QString getApplicationStyles() const;
  QString getMenuStyle() const;
  QVBoxLayout *createAppLayout() const;
  QWidget *createMenu() const;
  QWidget *createContent() const;
  QWidget *createUserArea() const;

 private slots:
  void resizeToMin();

 public:
  ApplicationView(QWidget *parent = nullptr);

  AuthView* getAuthView() const;
  UserApplicationView* getUserApplicationView() const;

  void closeEvent(QCloseEvent *event) override;

 public slots:
  void setUser(UserInterface *user) const;

  signals:
    void applicationClosed();
};

#endif //INKMARK_APPLICATION_H
