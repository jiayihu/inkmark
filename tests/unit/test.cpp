#include <gtest/gtest.h>
#include "model/bookmark-model.h"

TEST(Bookmark, Getters) {
  BookmarkModel google("https://www.google.it/", "Google", "Google's homepage");
  EXPECT_EQ(google.getLink().toString(), "https://www.google.it/");
  EXPECT_EQ(google.getName(), "Google");
  EXPECT_EQ(google.getDescription(), "Google's homepage");
  EXPECT_FALSE(google.getIsImportant());
}

TEST(Bookmark, EditFunctions) {
  BookmarkModel bookmark("https://www.google.it/", "Google", "Google's homepage");
  bookmark.editLink(QUrl("https://www.microsoft.com/it-it/"));
  bookmark.editName("Microsoft");
  bookmark.editDescription("Microsoft Italian homepage");

  EXPECT_EQ(bookmark.getLink().toString(), "https://www.microsoft.com/it-it/");
  EXPECT_EQ(bookmark.getName(), "Microsoft");
  EXPECT_EQ(bookmark.getDescription(), "Microsoft Italian homepage");
}

TEST(Bookmark, IsLinkValid) {
  BookmarkModel invalid("<abc>");
  BookmarkModel valid("google.com");
  EXPECT_FALSE(invalid.isLinkValid());
  EXPECT_TRUE(valid.isLinkValid());
}

TEST(Article, GetAuthors) {
  QDateTime now(QDateTime::currentDateTime());
  Article jarvisAI(now, 15);

  jarvisAI.addAuthor("Mark Zuckerberg0");
  jarvisAI.addAuthor("Mark Zuckerberg1");

  QVector<QString> authors = jarvisAI.getAuthors();
  for (int i = 0; i < authors.size(); i++) {
    EXPECT_EQ(authors[i].toStdString(), "Mark Zuckerberg" + std::to_string(i));
  }
}
