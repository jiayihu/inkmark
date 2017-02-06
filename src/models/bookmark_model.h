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

/**
 * Interfaccia di Bookmark da usare nelle views e controllers. Contiene solo metodi const,
 * quindi non ammette modifiche
 */
class BookmarkInterface {
 public:
  virtual ~BookmarkInterface() {}
  virtual QUrl getLink() const = 0;
  virtual QString getName() const = 0;
  virtual QString getDescription() const = 0;
  virtual bool isLinkValid() const = 0;
  virtual bool getIsImportant() const = 0;
  virtual bool hasWord(QString searchText) const = 0;
};

class BookmarkModel: public BookmarkInterface {
 private:
  QUrl link;
  QString name;
  QString description;
  bool isImportant;

 public:
  BookmarkModel();
  BookmarkModel(QString l, QString n = "", QString d = "");

  QUrl getLink() const override;
  QString getName() const override;
  QString getDescription() const override;
  void editName(QString newName);
  void editLink(QString newLink);
  void editDescription(QString newDescription);
  bool isLinkValid() const override;
  bool getIsImportant() const override;
  void setImportance(bool newValue);

  virtual bool hasWord(QString searchText) const override;
  virtual void readFromJSON(const QJsonObject &json);
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
  bool hasWord(QString searchText) const override;
  void readFromJSON(const QJsonObject &json) override;
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
  bool hasWord(QString searchText) const override;
  void readFromJSON(const QJsonObject &json) override;
  void writeToJSON(QJsonObject &json) const override;

  static QString format;
};

// TODO SocialPost

#endif //INKMARK_BOOKMARK_H
