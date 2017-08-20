#include "application_model.h"
#include <QDebug>

QVector<BookmarkInterface*> ApplicationModel::getBookmarks() const {
  // Crea una copia del vettore utilizzabile localmente dalle views
  QVector<BookmarkInterface*> bookmarksInterfaces;
  for (int i = 0; i < bookmarks.size(); i++) bookmarksInterfaces.push_back(bookmarks[i]);

  return bookmarksInterfaces;
}

void ApplicationModel::clean() {
  for (int i = 0; i < bookmarks.size(); i++) delete bookmarks[i];
  for (int i = 0; i < users.size(); i++) delete users[i];
  delete currentUser;
}

ApplicationModel::~ApplicationModel() { clean(); }

void ApplicationModel::readFromJSON(const QJsonObject &json) {
  // Pulisco l'oggetto se conteneva dati
  clean();

  // Carica la lista di bookmarks dal JSON
  QJsonArray bookmarksJSON = json.value("bookmarks").toArray();
  for (int i = 0; i < bookmarksJSON.size(); i++) {
    BookmarkModel *bookmark = new BookmarkModel();
    bookmark->readFromJSON(bookmarksJSON[i].toObject());
    bookmarks.push_back(bookmark);
  }

  // Carica la lista di utenti dal JSON
  QJsonArray usersJSON = json.value("users").toArray();
  for (int i = 0; i < usersJSON.size(); i++) {
    UserModel *user = new UserModel();
    user->readFromJSON(usersJSON[i].toObject());
    users.push_back(user);
  }
}

void ApplicationModel::writeToJSON(QJsonObject &json) const {
  // Salva la lista di bookmarks
  QJsonArray bookmarksJSON;
  for (int i = 0; i < bookmarks.size(); i++) {
    QJsonObject bookmarkJSON;
    bookmarks[i]->writeToJSON(bookmarkJSON);
    bookmarksJSON.append(bookmarkJSON);
  }

  json.insert("bookmarks", bookmarksJSON);

  // Salva la lista di utenti
  QJsonArray usersJSON;
  for (int i = 0; i < users.size(); i++) {
    QJsonObject userJSON;
    users[i]->writeToJSON(userJSON);
    usersJSON.append(userJSON);
  }

  json.insert("users", usersJSON);
}

void ApplicationModel::addBookmark(const QString &name, const QString &link, const QString &description) {
  if (!currentUser || !currentUser->canAdd()) return;

  BookmarkModel *bookmark = new BookmarkModel(currentUser->getId(), link, name, description);
  bookmarks.push_back(bookmark);
  
  emit addedBookmark(bookmark);
}

void ApplicationModel::deleteBookmark(BookmarkInterface *bookmark) {
  if (!bookmark || !currentUser || !currentUser->canDelete(bookmark)) return;

  QVector<BookmarkModel*>::iterator it = bookmarks.begin();
  bool trovato = false;

  for (; it != bookmarks.end() && !trovato; it++) {
    if (*it == bookmark) {
      bookmarks.erase(it);
      trovato = true;
    }
  }

  if (!trovato) return;

  emit deletedBookmark(bookmark);
  // Cancella il bookmark dal heap dopo il signal
  delete bookmark;
}

void ApplicationModel::editBookmark(BookmarkInterface *bookmark, const QString &newName, const QString &newLink, const QString &newDesc) {
  if (!bookmark || !currentUser || !currentUser->canEdit(bookmark)) return;
  int bookmarkIndex = bookmarks.indexOf(static_cast<BookmarkModel*>(bookmark));

  if (bookmarkIndex == -1) return;

  BookmarkModel *foundBookmark = bookmarks[bookmarkIndex];
  foundBookmark->editName(newName);
  foundBookmark->editLink(newLink);
  foundBookmark->editDescription(newDesc);

  emit updatedBookmark(bookmark);
}

QVector<BookmarkInterface*> ApplicationModel::search(const QString &searchText) const {
  QVector<BookmarkInterface*> found;

  for (int i = 0; i < bookmarks.size(); i++) {
    if (bookmarks[i]->hasWord(searchText)) found.push_back(bookmarks[i]);
  }

  emit finishedSearch(found);
  return found;
}

void ApplicationModel::registerUser(bool isGuest, const QString &name, const QString &surname, const QString &email, const QString &password) {
  if (isGuest) currentUser = new GuestModel();
  else {
    currentUser = new UserModel(name, surname, email, password);
    // Gli utenti Guest non sono aggiunti
    users.push_back(currentUser);
  }

  emit registeredUser(currentUser);
  emit loggedUser(currentUser);
}

void ApplicationModel::deleteUser(UserInterface *user) {
  AdminModel *isAdmin = dynamic_cast<AdminModel*>(currentUser);
  if (!user || user == currentUser || !isAdmin) return;

  int userIndex = users.indexOf(static_cast<UserModel*>(user));
  if (userIndex == -1) return;
  else users.remove(userIndex);

  for (int i = 0; i < users.size(); i++) {
    qDebug() << users[i]->getName() << " " << users[i]->getSurname();
  }
}

void ApplicationModel::editUser(UserInterface *user, const QString &name, const QString &surname, const QString &email, const QString &password) {
  AdminModel *isAdmin = dynamic_cast<AdminModel*>(currentUser);
  if (!user || user == currentUser || !isAdmin) return;

  int userIndex = users.indexOf(static_cast<UserModel*>(user));
  if (userIndex == -1) return;

  UserModel *foundUser = users[userIndex];
  foundUser->editName(name);
  foundUser->editSurname(surname);
  foundUser->editEmail(email);
  foundUser->editPassword(password);

  emit updatedUser(user);
}

bool ApplicationModel::loginUser(const QString &email, const QString &password) {
  UserModel* foundUser = nullptr;
  bool trovato = false;

  for (int i = 0; i < users.size() && !trovato; i++) {
    UserModel *user = users[i];
    if (user && user->getEmail() == email && user->getPassword() == password) {
      foundUser = user;
      trovato = true;
    }
  }

  if (trovato) {
    currentUser = foundUser;
    emit loggedUser(foundUser);
  }

  return trovato;
}
