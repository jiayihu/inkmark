#ifndef INKMARK_ADD_BOOKMARK_VIEW_H
#define INKMARK_ADD_BOOKMARK_VIEW_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QString>


class AddBookmarkView: public QWidget {
  Q_OBJECT

 private:
  QLineEdit *nameInput;
  QLineEdit *linkInput;
  QTextEdit *descriptionTextArea;

  private slots:
    void handleSubmitClick();

 public:
  AddBookmarkView(QWidget *parent = nullptr);

  signals:
    void submitClicked(QString name, QString link, QString description);
};

#endif //INKMARK_ADD_BOOKMARK_VIEW_H
