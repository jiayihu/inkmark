#include "bookmark-model.h"

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

Article::Article() {}
Article::Article(QDateTime p, int mr): publication(p), minRead(mr) {}
void Article::addAuthor(QString fullname) {
  authors.push_back(fullname);
}
QDateTime Article::getPublication() const { return publication; }
QVector<QString> Article::getAuthors() const { return authors; }
int Article::getMinRead() const { return minRead; }

Video::Video() {}
Video::Video(QTime d, VideoPlatform p): duration(d), platform(p) {}
QTime Video::getDuration() const { return duration; }
VideoPlatform Video::getPlatform() const { return platform; }
