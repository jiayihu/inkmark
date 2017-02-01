#include <gtest/gtest.h>
#include <QJsonDocument>
#include <QString>
#include "models/bookmark_model.h"

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

TEST(Bookmark, ToJSON) {
  BookmarkModel google("https://www.google.it/", "Google", "Google's homepage");
  QJsonObject *googleJSON = google.toJSON();
  QJsonDocument jsonDoc(*googleJSON);
  QString jsonString = jsonDoc.toJson(QJsonDocument::Compact);
  QString expectedString = "{\"description\":\"Google's homepage\",\"isImportant\":false,\"link\":\"https://www.google.it/\",\"name\":\"Google\"}";
  EXPECT_EQ(jsonString.toStdString(), expectedString.toStdString());
}

TEST(Article, GetAuthors) {
  QDateTime now(QDateTime::currentDateTime());
  ArticleModel jarvisAI(
      "https://www.facebook.com/notes/mark-zuckerberg/building-jarvis/10154361492931634/",
      "Facebook",
      "Building Jarvis - Facebook",
      now,
      15
  );
  jarvisAI.addAuthor("Mark Zuckerberg0");
  jarvisAI.addAuthor("Mark Zuckerberg1");

  QVector<QString> authors = jarvisAI.getAuthors();
  for (int i = 0; i < authors.size(); i++) {
    EXPECT_EQ(authors[i].toStdString(), "Mark Zuckerberg" + std::to_string(i));
  }
}
