#ifndef INKMARK_ADD_BOOKMARK_VIEW_H
#define INKMARK_ADD_BOOKMARK_VIEW_H

#include <QWidget>
#include <QComboBox>
#include <QDateEdit>
#include <QTimeEdit>
#include <QString>
#include "models/bookmark_model.h"
#include "widgets/text_input_widget/text_input_widget.h"
#include "widgets/text_area_widget/text_area_widget.h"


class AddBookmarkView: public QWidget {
  Q_OBJECT

 private:
  BookmarkInterface *model;

  TextInputWidget *nameInput;
  TextInputWidget *linkInput;
  TextAreaWidget *descriptionTextArea;
  QComboBox *typeSelect;
  QWidget *articleFields;
  QDateEdit *pubblicationInput;
  QTimeEdit *minReadInput;
  QWidget *videoFields;
  QTimeEdit *durationInput;

  QWidget* createTypeSelect();
  QWidget* createArticleFields();
  QWidget* createVideoFields();
  QWidget* createFields();
  QWidget* createButtons();

  private slots:
    void handleTypeChange(const QString &type);
    void handleSubmitClick();

 public:
  AddBookmarkView(QWidget *parent = nullptr);

 public slots:
  void setModel(BookmarkInterface *newModel);
  void clear() const;

 signals:
  void cancelClicked();
  void addClicked(
    const QString &name,
    const QString &link,
    const QString &description,
    const BookmarkType &type,
    const QDate &pubblication,
    const QTime &minRead,
    const QTime &duration
  );
  void editClicked(
    BookmarkInterface *bookmark,
    const QString &name,
    const QString &link,
    const QString &description,
    const BookmarkType &type,
    const QDate &pubblication,
    const QTime &minRead,
    const QTime &duration
  );
};

#endif //INKMARK_ADD_BOOKMARK_VIEW_H
