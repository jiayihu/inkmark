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

/**
 * Classe view usata sia per la creazione che modifica di un bookmark, poiché
 * i campi sono identici in entrambi i casi. L'unica distinzione è che nel secondo
 * caso la view possiede un model definito, ovvero il bookmark da editare.
 */
class EditBookmarkView: public QWidget {
  Q_OBJECT

 private:
  BookmarkInterface *model;

  TextInputWidget *nameInput;
  TextInputWidget *linkInput;
  TextAreaWidget *descriptionTextArea;
  QComboBox *typeSelect;
  QWidget *articleFields;
  QDateEdit *publicationInput;
  QTimeEdit *minReadInput;
  QWidget *videoFields;
  QTimeEdit *durationInput;

  QWidget *typeField;

  QWidget* createTypeSelect();
  QWidget* createArticleFields();
  QWidget* createVideoFields();
  QWidget* createFields();
  QWidget* createButtons();

  private slots:
    void handleTypeChange(const QString &type);
    void handleSubmitClick();

 public:
  EditBookmarkView(QWidget *parent = nullptr);

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
    const QDate &publication,
    const QTime &minRead,
    const QTime &duration
  );
  void editClicked(
    BookmarkInterface *bookmark,
    const QString &name,
    const QString &link,
    const QString &description,
    const QDate &publication,
    const QTime &minRead,
    const QTime &duration
  );
};

#endif //INKMARK_ADD_BOOKMARK_VIEW_H
