#ifndef INKMARK_SEARCH_BOOKMARK_VIEW_H
#define INKMARK_SEARCH_BOOKMARK_VIEW_H

#include <QWidget>
#include "widgets/text_input_widget/text_input_widget.h"
#include "widgets/button_widget/button_widget.h"

class SearchBookmarkView: public QWidget {
  Q_OBJECT

 private:
  TextInputWidget *searchInput;

 private slots:
  void handleSearchClick();

 public:
  SearchBookmarkView(QWidget *parent = nullptr);

 signals:
  void clickedSearch(QString searchText);
  void clickedCancel();
};

#endif //INKMARK_SEARCH_BOOKMARK_VIEW_H
