#include "bookmark-model.h"

Bookmark::Bookmark() {}
Bookmark::Bookmark(QString l, QString n, QString d): link(QUrl::fromUserInput(l)), name(n), description(d) {}
QUrl Bookmark::getLink() const { return link; }
QString Bookmark::getName() const { return name; }
QString Bookmark::getDescription() const { return description; }
void Bookmark::editLink(const QUrl &newLink) { link = newLink; }
void Bookmark::editName(const QString &newName) { name = newName; }
void Bookmark::editDescription(const QString &newDescription) { description = newDescription; }
bool Bookmark::isLinkValid() const { return link.isValid(); }
void Bookmark::setImportance(bool newValue) { isImportant = newValue; }

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
