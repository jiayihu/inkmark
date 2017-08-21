#ifndef INKMARK_ADD_BOOKMARK_VIEW_H
#define INKMARK_ADD_BOOKMARK_VIEW_H

#include <QWidget>
#include <QString>
#include "widgets/text_input_widget/text_input_widget.h"
#include "widgets/text_area_widget/text_area_widget.h"


class AddBookmarkView: public QWidget {
  Q_OBJECT

 private:
  TextInputWidget *nameInput;
  TextInputWidget *linkInput;
  TextAreaWidget *descriptionTextArea;

  private slots:
    void handleSubmitClick();

 public:
  AddBookmarkView(QWidget *parent = nullptr);

 public slots:
  void clear() const;

 signals:
  void cancelClicked();
  void submitClicked(const QString &name, const QString &link, const QString &description);
};

#endif //INKMARK_ADD_BOOKMARK_VIEW_H
