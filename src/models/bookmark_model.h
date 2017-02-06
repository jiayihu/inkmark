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
  virtual bool hasWord(const QString &searchText) const = 0;
};

class BookmarkModel: public BookmarkInterface {
 private:
  QUrl link;
  QString name;
  QString description;
  bool isImportant;

 public:
  BookmarkModel();
  BookmarkModel(const QString &l, const QString &n = "", const QString &d = "");

  QUrl getLink() const override;
  QString getName() const override;
  QString getDescription() const override;
  void editName(const QString &newName);
  void editLink(const QString &newLink);
  void editDescription(const QString &newDescription);
  bool isLinkValid() const override;
  bool getIsImportant() const override;
  void setImportance(bool newValue);

  virtual bool hasWord(const QString &searchText) const override;
  virtual void readFromJSON(const QJsonObject &json);
  virtual void writeToJSON(QJsonObject &json) const;

  // Conversione a QString per poter usare `qDebug() << bookmark`
  virtual operator QString() const { return name + " " + link.toString() + " " + description; }
};
// TODO Anche per classi derivate
std::ostream& operator<<(std::ostream &os, const BookmarkModel &bookmark);

class ArticleModel: public BookmarkModel {
 private:
  QDateTime publication;
  QVector<QString> authors;
  int minRead;

 public:
  ArticleModel();
  ArticleModel(const QString &l, const QString &n, const QString &d, const QDateTime &p, int mr = 0);

  void addAuthor(const QString &fullname = "");
  QDateTime getPublication() const;
  QVector<QString> getAuthors() const;
  int getMinRead() const;
  bool hasWord(const QString &searchText) const override;
  void readFromJSON(const QJsonObject &json) override;
  void writeToJSON(QJsonObject &json) const override;

  static QString format;
};

enum VideoPlatform { youtube, vimeo, twitch, noPlatform };

extern VideoPlatform stringToPlatform(const QString &platform);
extern QString platformToString(const VideoPlatform &platform);

class VideoModel: public BookmarkModel {
 private:
  QTime duration;
  VideoPlatform platform;

 public:
  VideoModel();
  VideoModel(const QString &l, const QString &n, const QString &d, const QTime &dur, const VideoPlatform &p = VideoPlatform::noPlatform);

  QTime getDuration() const;
  VideoPlatform getPlatform() const;
  bool hasWord(const QString &searchText) const override;
  void readFromJSON(const QJsonObject &json) override;
  void writeToJSON(QJsonObject &json) const override;

  static QString format;
};

// TODO SocialPost

#endif //INKMARK_BOOKMARK_H
