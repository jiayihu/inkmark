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

/**
 * Vera implementazione della classe BookmarkModel
 */
class BookmarkModel: virtual public BookmarkInterface {
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

std::ostream& operator<<(std::ostream &os, const BookmarkModel &bookmark);


/**
 * Bookmarks articoli
 */

/**
 * Interfaccia per i bookmarks articoli, da usare nelle views
 */
class ArticleInterface: virtual public BookmarkInterface {
 public:
  virtual QDate getPublication() const = 0;
  virtual QTime getMinRead() const = 0;
};

/**
 * Vera implementazione della classe ArticleModel
 */
class ArticleModel: public BookmarkModel, public ArticleInterface {
 private:
  QDate publication;
  QTime minRead;

 public:
  static QString format;

  ArticleModel();
  ArticleModel(int ai, const QString &l, const QString &n, const QString &d, const QDate &p, QTime mr);

  BookmarkType getType() const override;
  QDate getPublication() const override ;
  QTime getMinRead() const override ;
  void readFromJSON(const QJsonObject &json) override;
  void writeToJSON(QJsonObject &json) const override;
};


/**
 * Bookmarks video
 */

enum VideoPlatform { youtube, vimeo, twitch, noPlatform };

extern VideoPlatform stringToPlatform(const QString &platform);
extern QString platformToString(const VideoPlatform &platform);

/**
 * Interfaccia per i bookmarks video, da usare nelle views
 */
class VideoInterface: virtual public BookmarkInterface {
 public:
  virtual QTime getDuration() const = 0;
  virtual VideoPlatform getPlatform() const = 0;
};

/**
 * Vera implementazione della classe VideoModel
 */
class VideoModel: public BookmarkModel, public VideoInterface {
 private:
  QTime duration;
  VideoPlatform platform;

 public:
  static QString format;
  static VideoPlatform platformFromLink(const QString &link);

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
  QTime getDuration() const override;
  VideoPlatform getPlatform() const override;
  bool hasText(const QString &searchText) const override;
  void readFromJSON(const QJsonObject &json) override;
  void writeToJSON(QJsonObject &json) const override;
};

// TODO SocialPost

#endif //INKMARK_BOOKMARK_H
