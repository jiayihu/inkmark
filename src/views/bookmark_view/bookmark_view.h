#ifndef INKMARK_BOOKMARK_VIEW_H
#define INKMARK_BOOKMARK_VIEW_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include "models/bookmark_model.h"
#include "widgets/link_widget/link_widget.h"

/**
 * Classe view che mostra un singolo bookmark
 */
class BookmarkView: public QWidget {
  Q_OBJECT

 private:
  BookmarkInterface *model;
  LinkWidget *nameLink;
  QLabel *descriptionLabel;
  QLabel *hostLabel;

  QWidget* createContent();
  QLabel* createHostLabel() const;
  QWidget* createButtons() const;

 private slots:
  /**
   * Emette il signal clickedDelete con il proprio model
   */
  void handleDeleteClick();
  void handleEditClick();

 public:
  BookmarkView(QWidget *parent = nullptr);

 public slots:
  void setModel(BookmarkInterface *newModel);

 signals:
  void clickedDelete(BookmarkInterface*);
  void clickedEdit(BookmarkInterface*);
};

#endif //INKMARK_BOOKMARK_VIEW_H
