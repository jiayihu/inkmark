#include <gtest/gtest.h>
#include "models/bookmark_model.h"

TEST(BookmarkModel, Getters) {
  BookmarkModel google("https://www.google.it/", "Google", "Google's homepage");
  EXPECT_EQ(google.getLink().toString(), "https://www.google.it/");
  EXPECT_EQ(google.getName(), "Google");
  EXPECT_EQ(google.getDescription(), "Google's homepage");
  EXPECT_FALSE(google.getIsImportant());
}

TEST(BookmarkModel, EditFunctions) {
  BookmarkModel bookmark("https://www.google.it/", "Google", "Google's homepage");
  bookmark.editLink(QUrl("https://www.microsoft.com/it-it/"));
  bookmark.editName("Microsoft");
  bookmark.editDescription("Microsoft Italian homepage");

  EXPECT_EQ(bookmark.getLink().toString(), "https://www.microsoft.com/it-it/");
  EXPECT_EQ(bookmark.getName(), "Microsoft");
  EXPECT_EQ(bookmark.getDescription(), "Microsoft Italian homepage");
}

TEST(BookmarkModel, IsLinkValid) {
  BookmarkModel invalid("<abc>");
  BookmarkModel valid("google.com");
  EXPECT_FALSE(invalid.isLinkValid());
  EXPECT_TRUE(valid.isLinkValid());
}

TEST(BookmarkModel, ReadFromJSON) {
  QJsonObject googleJSON;
  googleJSON.insert("name", "Google");
  googleJSON.insert("link", "https://www.google.it/");
  googleJSON.insert("description", "Google's homepage");
  googleJSON.insert("isImportant", true);

  BookmarkModel bookmark;
  bookmark.readFromJSON(googleJSON);
  EXPECT_EQ(bookmark.getLink().toString(), "https://www.google.it/");
  EXPECT_EQ(bookmark.getName(), "Google");
  EXPECT_EQ(bookmark.getDescription(), "Google's homepage");
  EXPECT_TRUE(bookmark.getIsImportant());
}

TEST(BookmarkModel, WriteToJSON) {
  BookmarkModel google("https://www.google.it/", "Google", "Google's homepage");
  QJsonObject googleJSON;
  google.writeToJSON(googleJSON);

  EXPECT_EQ(googleJSON.value("name").toString(), google.getName());
  EXPECT_EQ(googleJSON.value("link").toString(), google.getLink().toString());
  EXPECT_EQ(googleJSON.value("description").toString(), google.getDescription());
  EXPECT_EQ(googleJSON.value("isImportant").toBool(), google.getIsImportant());
}

TEST(ArticleModel, Construction) {
  QDateTime now(QDateTime::fromString("02 Feb 2017 12:00:00", ArticleModel::format));
  ArticleModel jarvisAI(
      "https://www.facebook.com/notes/mark-zuckerberg/building-jarvis/10154361492931634/",
      "Facebook",
      "Building Jarvis - Facebook",
      now,
      15
  );
  jarvisAI.addAuthor("Mark Zuckerberg0");
  jarvisAI.addAuthor("Mark Zuckerberg1");

  EXPECT_EQ(jarvisAI.getPublication(), now);
  EXPECT_EQ(jarvisAI.getMinRead(), 15);

  QVector<QString> authors = jarvisAI.getAuthors();
  for (int i = 0; i < authors.size(); i++) {
    EXPECT_EQ(authors[i].toStdString(), "Mark Zuckerberg" + std::to_string(i));
  }
}

TEST(ArticleModel, ReadFromJSON) {
  QJsonObject googleJSON;
  QJsonArray authorsJSON;
  authorsJSON.append("Larry Page");
  authorsJSON.append("Sergey Brin");
  googleJSON.insert("authors", authorsJSON);
  googleJSON.insert("publication", "04 set 1998 00:00:00");
  googleJSON.insert("minRead", 10);

  ArticleModel article;
  article.readFromJSON(googleJSON);
  EXPECT_EQ(article.getPublication().toString(ArticleModel::format).toStdString(), "04 set 1998 00:00:00");
  EXPECT_EQ(article.getMinRead(), 10);

  QVector<QString> authors = article.getAuthors();
  EXPECT_EQ(authors[0], "Larry Page");
  EXPECT_EQ(authors[1], "Sergey Brin");
}

TEST(ArticleModel, WriteToJSON) {
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

  QJsonObject articleJSON;
  jarvisAI.writeToJSON(articleJSON);

  EXPECT_EQ(articleJSON.value("publication"), now.toString(ArticleModel::format));
  EXPECT_EQ(articleJSON.value("minRead").toInt(), 15);
  QJsonArray authorsJSON = articleJSON.value("authors").toArray();
  EXPECT_EQ(authorsJSON[0].toString(), "Mark Zuckerberg0");
  EXPECT_EQ(authorsJSON[1].toString(), "Mark Zuckerberg1");
}

TEST(VideoModel, ReadFromJSON) {
  QJsonObject youtubeJSON;
  youtubeJSON.insert("duration", "00:10:00");
  youtubeJSON.insert("platform", "youtube");

  VideoModel video;
  video.readFromJSON(youtubeJSON);

  EXPECT_EQ(video.getDuration().toString(VideoModel::format), "00:10:00");
  EXPECT_EQ(platformToString(video.getPlatform()), "youtube");
}

TEST(VideoModel, WriteToJSON) {
  VideoModel youtube("", "", "", QTime::fromString("00:10:00", VideoModel::format), VideoPlatform::youtube);

  QJsonObject youtubeJSON;
  youtube.writeToJSON(youtubeJSON);

  EXPECT_EQ(youtubeJSON.value("duration").toString(), "00:10:00");
  EXPECT_EQ(youtubeJSON.value("platform").toString(), "youtube");
}
