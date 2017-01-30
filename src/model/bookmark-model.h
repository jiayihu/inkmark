#ifndef INKMARK_BOOKMARK_H
#define INKMARK_BOOKMARK_H

#include <QString>
#include <QDateTime>
#include <QTime>
#include <QUrl>
#include <QVector>

class Bookmark {
 private:
  QUrl link;
  QString name;
  QString description;
  bool isImportant;

 public:
  Bookmark();
  Bookmark(QString l, QString n = "", QString d = "");
  virtual ~Bookmark() {}

  QUrl getLink() const;
  QString getName() const;
  QString getDescription() const;
  void editLink(const QUrl &newLink);
  void editName(const QString &newName);
  void editDescription(const QString &newDescription);
  bool isLinkValid() const;
  void setImportance(bool newValue);
};

class Article: public Bookmark {
 private:
  QDateTime publication;
  QVector<QString> authors;
  int minRead;

 public:
  Article();
  Article(QDateTime p, int mr = 0);

  void addAuthor(QString fullname = "");
  QDateTime getPublication() const;
  QVector<QString> getAuthors() const;
  int getMinRead() const;
};

enum VideoPlatform { youtube, vimeo, twitch, noPlatform };

class Video: public Bookmark {
 private:
  QTime duration;
  VideoPlatform platform;

 public:
  Video();
  Video(QTime d, VideoPlatform p = VideoPlatform::noPlatform);

  QTime getDuration() const;
  VideoPlatform getPlatform() const;
};

// TODO SocialPost

#endif //INKMARK_BOOKMARK_H
