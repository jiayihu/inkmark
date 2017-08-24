#ifndef INKMARK_BOOKMARK_H
#define INKMARK_BOOKMARK_H

#include <iostream>
#include <QString>
#include <QDate>
#include <QTime>
#include <QUrl>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>

enum BookmarkType { none, article, video };

extern BookmarkType stringToBookmarkType(const QString &bookmarkType);
extern QString bookmarkTypeToString(const BookmarkType &bookmarkType);

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
  virtual int getAuthorId() const = 0;
  virtual BookmarkType getType() const = 0;
  virtual bool isLinkValid() const = 0;
  virtual bool getIsImportant() const = 0;
  virtual bool hasText(const QString &searchText) const = 0;
};

class BookmarkModel: public BookmarkInterface {
 private:
  QUrl link;
  QString name;
  QString description;
  int authorId;
  bool isImportant;

 protected:
  bool hasInsensitiveText(const QString &text, const QString &query) const;

 public:
  BookmarkModel();
  BookmarkModel(int ai, const QString &l, const QString &n = "", const QString &d = "");

  QUrl getLink() const override;
  QString getName() const override;
  QString getDescription() const override;
  int getAuthorId() const override;
  void editName(const QString &newName);
  void editLink(const QString &newLink);
  void editDescription(const QString &newDescription);
  BookmarkType getType() const override;
  bool isLinkValid() const override;
  bool getIsImportant() const override;
  void setImportance(bool newValue);

  bool hasText(const QString &searchText) const override;
  virtual void readFromJSON(const QJsonObject &json);
  virtual void writeToJSON(QJsonObject &json) const;

  // Conversione a QString per poter usare `qDebug() << bookmark`
  virtual operator QString() const { return name + " " + link.toString() + " " + description; }
};
// TODO Anche per classi derivate
std::ostream& operator<<(std::ostream &os, const BookmarkModel &bookmark);

class ArticleModel: public BookmarkModel {
 private:
  QDate publication;
  QTime minRead;

 public:
  static QString format;

  ArticleModel();
  ArticleModel(int ai, const QString &l, const QString &n, const QString &d, const QDate &p, QTime mr);

  BookmarkType getType() const override;
  QDate getPublication() const;
  QTime getMinRead() const;
  void readFromJSON(const QJsonObject &json) override;
  void writeToJSON(QJsonObject &json) const override;
};

enum VideoPlatform { youtube, vimeo, twitch, noPlatform };

extern VideoPlatform stringToPlatform(const QString &platform);
extern QString platformToString(const VideoPlatform &platform);

class VideoModel: public BookmarkModel {
 private:
  QTime duration;
  VideoPlatform platform;

 public:
  static QString format;

  VideoModel();
  VideoModel(
    int ai,
    const QString &l,
    const QString &n,
    const QString &d,
    const QTime &dur,
    const VideoPlatform &p = VideoPlatform::noPlatform
  );

  BookmarkType getType() const override;
  QTime getDuration() const;
  VideoPlatform getPlatform() const;
  bool hasText(const QString &searchText) const override;
  void readFromJSON(const QJsonObject &json) override;
  void writeToJSON(QJsonObject &json) const override;
};

// TODO SocialPost

#endif //INKMARK_BOOKMARK_H
