#ifndef INKMARK_BOOKMARK_H
#define INKMARK_BOOKMARK_H

#include <iostream>
#include <QString>
#include <QDateTime>
#include <QTime>
#include <QUrl>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>

class BookmarkModel {
 private:
  QUrl link;
  QString name;
  QString description;
  bool isImportant;

 public:
  BookmarkModel();
  BookmarkModel(QString l, QString n = "", QString d = "");
  virtual ~BookmarkModel() {}

  QUrl getLink() const;
  QString getName() const;
  QString getDescription() const;
  void editLink(const QUrl &newLink);
  void editName(const QString &newName);
  void editDescription(const QString &newDescription);
  bool isLinkValid() const;
  bool getIsImportant() const;
  void setImportance(bool newValue);
  virtual void writeToJSON(QJsonObject &json) const;

  // Conversione a QString per poter usare `qDebug() << bookmark`
  operator QString() const { return name + " " + link.toString() + description; }
};
std::ostream& operator<<(std::ostream &os, const BookmarkModel &bookmark);

class ArticleModel: public BookmarkModel {
 private:
  QDateTime publication;
  QVector<QString> authors;
  int minRead;

 public:
  ArticleModel();
  ArticleModel(QString l, QString n, QString d, QDateTime p, int mr = 0);

  void addAuthor(QString fullname = "");
  QDateTime getPublication() const;
  QVector<QString> getAuthors() const;
  int getMinRead() const;
  void writeToJSON(QJsonObject &json) const override;
  static QString format;
};

enum VideoPlatform { youtube, vimeo, twitch, noPlatform };

extern VideoPlatform stringToPlatform(QString platform);
extern QString platformToString(VideoPlatform platform);

class VideoModel: public BookmarkModel {
 private:
  QTime duration;
  VideoPlatform platform;

 public:
  VideoModel();
  VideoModel(QString l, QString n, QString d, QTime dur, VideoPlatform p = VideoPlatform::noPlatform);

  QTime getDuration() const;
  VideoPlatform getPlatform() const;
  void writeToJSON(QJsonObject &json) const override;
  static QString format;
};

// TODO SocialPost

#endif //INKMARK_BOOKMARK_H
