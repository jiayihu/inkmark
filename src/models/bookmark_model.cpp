#include "bookmark_model.h"
#include <QMap>
#include <QDebug>

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

QString ArticleModel::format = "dd MMM yyyy hh:mm:ss";

ArticleModel::ArticleModel() {}

ArticleModel::ArticleModel(int ai, const QString &l, const QString &n, const QString &d, const QDateTime &p, int mr)
    : BookmarkModel(ai, l, n, d), publication(p), minRead(mr) {}

void ArticleModel::addAuthor(const QString &fullname) {
  authors.push_back(fullname);
}

QDateTime ArticleModel::getPublication() const { return publication; }

QVector<QString> ArticleModel::getAuthors() const { return authors; }

int ArticleModel::getMinRead() const { return minRead; }

bool ArticleModel::hasText(const QString &searchText) const {
  bool isInAuthors = false;

  for (int i = 0; i < authors.size() && !isInAuthors; i++) {
    if (hasInsensitiveText(authors[i], searchText)) isInAuthors = true;
  }

  return BookmarkModel::hasText(searchText) || isInAuthors;
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

/**
 * Video
 */

VideoPlatform stringToPlatform(const QString &platformString) {
  QMap<QString, VideoPlatform> platformMap = {
      { "youtube", VideoPlatform ::youtube },
      { "video", VideoPlatform::vimeo },
      { "twitch", VideoPlatform::twitch },
      { "no platform", VideoPlatform::noPlatform },
  };

  return platformMap[platformString];
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
      qWarning() << "Could not convert VideoPlatform to string";
      return "";
  }
}

QString VideoModel::format = "hh:mm:ss";

VideoModel::VideoModel(): platform(VideoPlatform::noPlatform) {}

VideoModel::VideoModel(int ai, const QString &l, const QString &n, const QString &d, const QTime &dur, const VideoPlatform &p)
  : BookmarkModel(ai, l, n, d), duration(dur), platform(p) {}

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
  json.insert("duration", duration.toString(VideoModel::format));
  json.insert("platform", platformToString(platform));
}
