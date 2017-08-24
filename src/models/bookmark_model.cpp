#include "bookmark_model.h"
#include <QMap>
#include <QDebug>

BookmarkType stringToBookmarkType(const QString &typeString) {
  if (typeString == "none") return BookmarkType::none;
  if (typeString == "article") return BookmarkType::article;
  if (typeString == "video") return BookmarkType::video;

  qDebug() << "stringToBookmarkType(): not supported bookmark type" << typeString;
  return BookmarkType::none;
}

QString bookmarkTypeToString(const BookmarkType &type) {
  switch (type) {
    case BookmarkType::none :
      return "none";
    case BookmarkType::article :
      return "article";
    case BookmarkType::video :
      return "video";
    default:
      qWarning() << "bookmarkTypeToString(): Could not convert Bookmark type to string";
      return "";
  }
}

bool BookmarkModel::hasInsensitiveText(const QString &text, const QString &query) const {
  return text.indexOf(query, 0, Qt::CaseInsensitive) != -1;
}

BookmarkModel::BookmarkModel() {}

BookmarkModel::BookmarkModel(int ai, const QString &l, const QString &n, const QString &d):
    link(QUrl::fromUserInput(l)), name(n), description(d), authorId(ai), isImportant(false) {}

QUrl BookmarkModel::getLink() const { return link; }

QString BookmarkModel::getName() const { return name; }

QString BookmarkModel::getDescription() const { return description; }

int BookmarkModel::getAuthorId() const { return authorId; }

BookmarkType BookmarkModel::getType() const { return BookmarkType::none; }

void BookmarkModel::editLink(const QString &newLink) { link = QUrl::fromUserInput(newLink); }

void BookmarkModel::editName(const QString &newName) { name = newName; }

void BookmarkModel::editDescription(const QString &newDescription) { description = newDescription; }

bool BookmarkModel::isLinkValid() const { return link.isValid(); }

bool BookmarkModel::getIsImportant() const { return isImportant; }

void BookmarkModel::setImportance(bool newValue) { isImportant = newValue; }

bool BookmarkModel::hasText(const QString &searchText) const {
  bool isInName = hasInsensitiveText(name, searchText);
  bool isInLink = hasInsensitiveText(link.toString(), searchText);
  bool isInDesc = hasInsensitiveText(description, searchText);

  return isInName || isInLink || isInDesc;
}

void BookmarkModel::readFromJSON(const QJsonObject &json) {
  authorId = json.value("authorId").toInt();
  name = json.value("name").toString();
  link = QUrl(json.value("link").toString());
  description = json.value("description").toString();
  isImportant = json.value("isImportant").toBool();
}

void BookmarkModel::writeToJSON(QJsonObject &json) const {
  json.insert("type", bookmarkTypeToString(getType()));
  json.insert("authorId", authorId);
  json.insert("link", link.toString());
  json.insert("name", name);
  json.insert("description", description);
  json.insert("isImportant", isImportant);
}

std::ostream& operator<<(std::ostream &os, const BookmarkModel &bookmark) {
  // Conversione da QString a std::string necessaria per poter usare l'operatore <<
  os << bookmark.getName().toStdString() << " " << bookmark.getLink().toString().toStdString();
  return os;
}


/**
 * Article
 */

QString ArticleModel::format = "dd MMMM yyyy";

ArticleModel::ArticleModel() {}

ArticleModel::ArticleModel(int ai, const QString &l, const QString &n, const QString &d, const QDate &p, QTime mr)
    : BookmarkModel(ai, l, n, d), publication(p), minRead(mr) {}

BookmarkType ArticleModel::getType() const { return BookmarkType::article; }

QDate ArticleModel::getPublication() const { return publication; }

QTime ArticleModel::getMinRead() const { return minRead; }

void ArticleModel::readFromJSON(const QJsonObject &json) {
  BookmarkModel::readFromJSON(json);
  QString publicationString = json.value("publication").toString();
  publication = QDate::fromString(publicationString, ArticleModel::format);
  minRead = QTime::fromString(json.value("minRead").toString());
}

void ArticleModel::writeToJSON(QJsonObject &json) const {
  BookmarkModel::writeToJSON(json);
  json.insert("publication", publication.toString(ArticleModel::format));
  json.insert("minRead", minRead.toString());
}

/**
 * Video
 */

VideoPlatform stringToPlatform(const QString &platformString) {
  if (platformString == "youtube") return VideoPlatform ::youtube;
  if (platformString == "vimeo") return VideoPlatform::vimeo;
  if (platformString == "twitch") return VideoPlatform::twitch;
  if (platformString == "no platform") return VideoPlatform::noPlatform;

  qDebug() << "stringToPlatform(): not supported video platform" << platformString;
  return VideoPlatform::noPlatform;
}

QString platformToString(const VideoPlatform &platform) {
  switch (platform) {
    case VideoPlatform::youtube :
      return "youtube";
    case VideoPlatform::vimeo :
      return "vimeo";
    case VideoPlatform::twitch :
      return "twitch";
    case VideoPlatform::noPlatform :
      return "no platform";
    default:
      qWarning() << "platformToString(): Could not convert VideoPlatform to string";
      return "";
  }
}

QString VideoModel::format = "hh:mm:ss";

VideoModel::VideoModel(): platform(VideoPlatform::noPlatform) {}

VideoModel::VideoModel(int ai, const QString &l, const QString &n, const QString &d, const QTime &dur, const VideoPlatform &p)
  : BookmarkModel(ai, l, n, d), duration(dur), platform(p) {}

BookmarkType VideoModel::getType() const { return BookmarkType::video; }

QTime VideoModel::getDuration() const { return duration; }

VideoPlatform VideoModel::getPlatform() const { return platform; }

bool VideoModel::hasText(const QString &searchText) const {
  bool isInPlatform = hasInsensitiveText(platformToString(platform), searchText);

  return BookmarkModel::hasText(searchText) || isInPlatform;
}

void VideoModel::readFromJSON(const QJsonObject &json) {
  BookmarkModel::readFromJSON(json);
  QString durationString = json.value("duration").toString();
  duration = QTime::fromString(durationString, VideoModel::format);
  platform = stringToPlatform(json.value("platform").toString());
}

void VideoModel::writeToJSON(QJsonObject &json) const {
  BookmarkModel::writeToJSON(json);
  json.insert("duration", duration.toString(VideoModel::format));
  json.insert("platform", platformToString(platform));
}
