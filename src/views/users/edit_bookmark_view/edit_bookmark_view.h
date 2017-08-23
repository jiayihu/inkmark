#ifndef INKMARK_EDIT_BOOKMARK_VIEW_H
#define INKMARK_EDIT_BOOKMARK_VIEW_H

#include <QString>
#include <QWidget>
#include "widgets/text_input_widget/text_input_widget.h"
#include "widgets/text_area_widget/text_area_widget.h"
#include "models/bookmark_model.h"

class EditBookmarkView: public QWidget {
  Q_OBJECT

 private:
  BookmarkInterface *model;
  TextInputWidget *nameInput;
  TextInputWidget *linkInput;
  TextAreaWidget *descriptionTextArea;

 private slots:
  void handleEditClick();

 public:
  EditBookmarkView(QWidget *parent = nullptr);

 public slots:
  void setModel(BookmarkInterface *newModel);

 signals:
  void saveClicked(BookmarkInterface *model, QString newName, QString newLink, QString newDesc);
  void cancelClicked();
};

#endif //INKMARK_EDIT_BOOKMARK_VIEW_H