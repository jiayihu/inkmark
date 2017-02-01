#include "bookmark_model.h"

BookmarkModel::BookmarkModel() {}

BookmarkModel::BookmarkModel(QString l, QString n, QString d):
    link(QUrl::fromUserInput(l)), name(n), description(d), isImportant(false) {}

QUrl BookmarkModel::getLink() const { return link; }

QString BookmarkModel::getName() const { return name; }

QString BookmarkModel::getDescription() const { return description; }

void BookmarkModel::editLink(const QUrl &newLink) { link = newLink; }

void BookmarkModel::editName(const QString &newName) { name = newName; }

void BookmarkModel::editDescription(const QString &newDescription) { description = newDescription; }

bool BookmarkModel::isLinkValid() const { return link.isValid(); }

bool BookmarkModel::getIsImportant() const { return isImportant; }

void BookmarkModel::setImportance(bool newValue) { isImportant = newValue; }

QJsonObject* BookmarkModel::toJSON() const {
  QJsonObject *json = new QJsonObject();
  json->insert("link", link.toString());
  json->insert("name", name);
  json->insert("description", description);
  json->insert("isImportant", isImportant);

  return json;
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

QJsonObject* ArticleModel::toJSON() const {
  QJsonObject *json = BookmarkModel::toJSON();
  json->insert("publication", publication.toString("dd MMMM yyyy hh:mm:ss"));

  QJsonArray authorsJSON;
  for (int i = 0; i < authors.size(); i++) {
    QJsonValue authorJSON(authors[i]);
    authorsJSON.append(authorJSON);
  }
  json->insert("authors", authorsJSON);

  json->insert("minRead", minRead);

  return json;
}

/**
 * Video
 */

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
      return "";
  }
}

VideoModel::VideoModel() {}

VideoModel::VideoModel(QString l, QString n, QString d, QTime dur, VideoPlatform p): BookmarkModel(l, n, d), duration(dur), platform(p) {}

QTime VideoModel::getDuration() const { return duration; }

VideoPlatform VideoModel::getPlatform() const { return platform; }

QJsonObject* VideoModel::toJSON() const {
  QJsonObject *json = BookmarkModel::toJSON();
  json->insert("duration", duration.toString("hh:mm:ss"));
  json->insert("platform", platformToString(platform));

  return json;
}
