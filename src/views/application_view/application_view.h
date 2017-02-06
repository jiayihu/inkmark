#ifndef INKMARK_APPLICATION_H
#define INKMARK_APPLICATION_H

#include <QWidget>
#include <QVector>
#include <QCloseEvent>
#include <QHBoxLayout>
#include "models/bookmark_model.h"
#include "views/user_application_view/user_application_view.h"

/**
 * Classe View che si occupa di istanziare le classi view figlie e del layout
 * generale come il menu
 */
class ApplicationView: public QWidget {
 Q_OBJECT

 private:
  UserApplicationView *userApplicationView;
  QString getApplicationStyles() const;
  QString getMenuStyle() const;
  QVBoxLayout *createAppLayout() const;
  QWidget *createMenu() const;
  QWidget *createContent();

 private slots:
  void resizeToMin();

 public:
  ApplicationView(QWidget *parent = nullptr);

  UserApplicationView* getUserApplicationView() const;

  void closeEvent(QCloseEvent *event);

  signals:
    void applicationClosed();
};

#endif //INKMARK_APPLICATION_H
