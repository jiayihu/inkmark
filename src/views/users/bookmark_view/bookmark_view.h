#ifndef INKMARK_BOOKMARK_VIEW_H
#define INKMARK_BOOKMARK_VIEW_H

#include <QWidget>
#include <QLabel>
#include "models/bookmark_model.h"
#include "widgets/link_widget/link_widget.h"
#include "widgets/button_widget/button_widget.h"

/**
 * Classe view che mostra un singolo bookmark
 */
class BookmarkView: public QWidget {
  Q_OBJECT

 private:
  static void setMetadataStyles(QLabel *label);

  BookmarkInterface *model;

  LinkWidget *nameLink;
  QLabel *descriptionLabel;
  QLabel *hostLabel;
  QLabel *publicationLabel;
  QLabel *minReadLabel;
  QLabel *durationLabel;
  ButtonWidget *deleteButton;
  ButtonWidget *editButton;

  QWidget* createContent();
  QWidget* createMetadata();
  QWidget* createButtons();

 private slots:
  /**
   * Emette il signal clickedDelete con il proprio model
   */
  void handleDeleteClick();
  void handleEditClick();

 public:
  BookmarkView(QWidget *parent = nullptr);

  void setPrivilegies(bool canEdit, bool canDelete) const;

 public slots:
  void setModel(BookmarkInterface *newModel);

 signals:
  void clickedDelete(BookmarkInterface*);
  void clickedEdit(BookmarkInterface*);
};

#endif //INKMARK_BOOKMARK_VIEW_H
