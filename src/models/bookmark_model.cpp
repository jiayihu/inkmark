#include "bookmark_model.h"
#include <QMap>
#include <QDebug>

BookmarkModel::BookmarkModel() {}

BookmarkModel::BookmarkModel(QString l, QString n, QString d):
    link(QUrl::fromUserInput(l)), name(n), description(d), isImportant(false) {}

QUrl BookmarkModel::getLink() const { return link; }

QString BookmarkModel::getName() const { return name; }

QString BookmarkModel::getDescription() const { return description; }

void BookmarkModel::editLink(QString newLink) { link = QUrl::fromUserInput(newLink); }

void BookmarkModel::editName(QString newName) { name = newName; }

void BookmarkModel::editDescription(QString newDescription) { description = newDescription; }

bool BookmarkModel::isLinkValid() const { return link.isValid(); }

bool BookmarkModel::getIsImportant() const { return isImportant; }

void BookmarkModel::setImportance(bool newValue) { isImportant = newValue; }

bool BookmarkModel::hasWord(QString searchText) const {
  bool isInName = name.indexOf(searchText) != -1;
  bool isInLink = link.toString().indexOf(searchText) != -1;
  bool isInDesc = description.indexOf(searchText) != -1;

  return isInName || isInLink || isInDesc;
}

void BookmarkModel::readFromJSON(const QJsonObject &json) {
 name = json.value("name").toString();
 link = QUrl(json.value("link").toString());
 description = json.value("description").toString();
 isImportant = json.value("isImportant").toBool();
}

void BookmarkModel::writeToJSON(QJsonObject &json) const {
  json.insert("link", link.toString());
  json.insert("name", name);
  json.insert("description", description);
  json.insert("isImportant", isImportant);
}

std::ostream& operator<<(std::ostream &os, const BookmarkModel &bookmark) {
  os << bookmark.getName() << " " << bookmark.getLink().toString();
  return os;
}


/**
 * Article
 */

ArticleModel::ArticleModel() {}

ArticleModel::ArticleModel(QString l, QString n, QString d, QDateTime p, int mr)
    : BookmarkModel(l, n, d), publication(p), minRead(mr) {}

void ArticleModel::addAuthor(QString fullname) {
  authors.push_back(fullname);
}

QDateTime ArticleModel::getPublication() const { return publication; }

QVector<QString> ArticleModel::getAuthors() const { return authors; }

int ArticleModel::getMinRead() const { return minRead; }

bool ArticleModel::hasWord(QString searchText) const {
  bool isInAuthors = false;

  for (int i = 0; i < authors.size() && !isInAuthors; i++) {
    if (authors[i].indexOf(searchText) != -1) isInAuthors = true;
  }

  return BookmarkModel::hasWord(searchText) || isInAuthors;
}

void ArticleModel::readFromJSON(const QJsonObject &json) {
  BookmarkModel::readFromJSON(json);
  QString publicationString = json.value("publication").toString();
  publication = QDateTime::fromString(publicationString, ArticleModel::format);

  QJsonArray authorsJSON = json.value("authors").toArray();
  for (int i = 0; i < authorsJSON.size(); i++) {
    authors.push_back(authorsJSON[i].toString());
  }

  minRead = json.value("minRead").toInt();
}

void ArticleModel::writeToJSON(QJsonObject &json) const {
  json.insert("publication", publication.toString(ArticleModel::format));

  QJsonArray authorsJSON;
  for (int i = 0; i < authors.size(); i++) {
    QJsonValue authorJSON(authors[i]);
    authorsJSON.append(authorJSON);
  }
  json.insert("authors", authorsJSON);

  json.insert("minRead", minRead);
}

QString ArticleModel::format = "dd MMM yyyy hh:mm:ss";

/**
 * Video
 */

VideoPlatform stringToPlatform(QString platformString) {
  QMap<QString, VideoPlatform> platformMap = {
      { "youtube", VideoPlatform ::youtube },
      { "video", VideoPlatform::vimeo },
      { "twitch", VideoPlatform::twitch },
      { "no platform", VideoPlatform::noPlatform },
  };

  return platformMap[platformString];
}

QString platformToString(VideoPlatform platform) {
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
      qWarning() << "Could not convert VideoPlatform to string";
      return "";
  }
}

VideoModel::VideoModel() {}

VideoModel::VideoModel(QString l, QString n, QString d, QTime dur, VideoPlatform p): BookmarkModel(l, n, d), duration(dur), platform(p) {}

QTime VideoModel::getDuration() const { return duration; }

VideoPlatform VideoModel::getPlatform() const { return platform; }

bool VideoModel::hasWord(QString searchText) const {
  bool isInPlatform = platformToString(platform).indexOf(searchText) != -1;
  
  return BookmarkModel::hasWord(searchText) || isInPlatform;
}

void VideoModel::readFromJSON(const QJsonObject &json) {
  BookmarkModel::readFromJSON(json);
  QString durationString = json.value("duration").toString();
  duration = QTime::fromString(durationString, VideoModel::format);
  platform = stringToPlatform(json.value("platform").toString());
}

void VideoModel::writeToJSON(QJsonObject &json) const {
  json.insert("duration", duration.toString(VideoModel::format));
  json.insert("platform", platformToString(platform));
}

QString VideoModel::format = "hh:mm:ss";
