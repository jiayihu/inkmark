#include "application_model.h"
#include <QDebug>

void ApplicationModel::clean() {
  for (int i = 0; i < bookmarks.size(); i++) delete bookmarks[i];
  for (int i = 0; i < users.size(); i++) delete users[i];
}

bool ApplicationModel::authenticate(const QString &email, const QString &password) {
  UserModel* foundUser = nullptr;
  bool trovato = false;

  for (int i = 0; i < users.size() && !trovato; i++) {
    UserModel *user = users[i];
    if (user && user->getEmail() == email && user->getPassword() == password) {
      foundUser = user;
      trovato = true;
    }
  }

  if (trovato) currentUser = foundUser;
  else emit hadUserError("There is no user with provided email and password.");

  return trovato;
}

ApplicationModel::~ApplicationModel() { clean(); }

QVector<BookmarkInterface*> ApplicationModel::getBookmarks() const {
  QVector<BookmarkInterface*> items;
  for (int i = 0; i < bookmarks.size(); i++) items.push_back(bookmarks[i]);

  return items;
}

QVector<UserInterface*> ApplicationModel::getUsers() const {
  QVector<UserInterface*> items;
  for (int i = 0; i < users.size(); i++) items.push_back(users[i]);

  return items;
}

void ApplicationModel::readFromJSON(const QJsonObject &json) {
  // Pulisco l'oggetto se conteneva dati
  clean();

  // Carica la lista di bookmarks dal JSON
  QJsonArray bookmarksJSON = json.value("bookmarks").toArray();
  for (int i = 0; i < bookmarksJSON.size(); i++) {
    QJsonObject bookmarkJSON = bookmarksJSON[i].toObject();
    BookmarkModel *bookmark = nullptr;
    BookmarkType type = stringToBookmarkType(bookmarkJSON.value("type").toString());

    if (type == BookmarkType::none) bookmark = new BookmarkModel();
    else if (type == BookmarkType::article) bookmark = new ArticleModel();
    else if (type == BookmarkType::video) bookmark = new VideoModel();
    else {
      qDebug() << "ApplicationModel::readFromJSON(): not supported bookmark type" << type;
      return;
    }

    bookmark->readFromJSON(bookmarkJSON);
    bookmarks.push_back(bookmark);
  }

  // Carica la lista di utenti dal JSON
  QJsonArray usersJSON = json.value("users").toArray();
  int maxId = 0;
  for (int i = 0; i < usersJSON.size(); i++) {
    QJsonObject userJSON = usersJSON[i].toObject();
    QString userRole = userJSON.value("role").toString();
    UserModel *user = nullptr;
    if (userRole == "admin") user = new AdminModel();
    else user = new UserModel();

    user->readFromJSON(userJSON);
    users.push_back(user);

    if (user->getId() > maxId) maxId = user->getId();
  }

  // Nuovi id per utenti partono almeno da questo valore
  UserModel::setIdCount(maxId);
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

void ApplicationModel::addBookmark(
  const QString &name,
  const QString &link,
  const QString &description,
  const BookmarkType &type,
  const QDate &pubblication,
  const QTime &minRead,
  const QTime &duration) {
  // Bisogna essere almeno UserModel per poter aggiungere bookmarks
  UserModel *user = dynamic_cast<UserModel *>(currentUser);
  if (!user || !user->canAdd()) return;

  if (name.isEmpty() || link.isEmpty()) {
    emit hadUserError("Name and link are required.");
    return;
  }

  BookmarkModel *bookmark = nullptr;

  if (type == BookmarkType::none) {
    bookmark = new BookmarkModel(user->getId(), link, name, description);
  } else if (type == BookmarkType::article) {
    bookmark = new ArticleModel(user->getId(), link, name, description, pubblication, minRead);
  } else if (type == BookmarkType::video) {
    VideoPlatform platform = VideoModel::platformFromLink(link);
    bookmark = new VideoModel(user->getId(), link, name, description, duration, platform);
  } else {
    qWarning() << "ApplicationModel::addBookmark(): Umknown bookmark type passed";
  }

  bookmarks.push_back(bookmark);
  
  emit addedBookmark(bookmark);
}

void ApplicationModel::deleteBookmark(BookmarkInterface *bookmark) {
  if (!bookmark || !currentUser || !currentUser->canDelete(bookmark)) return;

  int index = bookmarks.indexOf(dynamic_cast<BookmarkModel*>(bookmark));
  if (index == -1) return;
  bookmarks.remove(index);

  emit deletedBookmark(bookmark);
  // Cancella il bookmark dal heap dopo il signal
  delete bookmark;
}

void ApplicationModel::editBookmark(
  BookmarkInterface *bookmark,
  const QString &newName,
  const QString &newLink,
  const QString &newDesc,
  const QDate &newPublication,
  const QTime &newMinRead,
  const QTime &newDuration
) {
  if (!bookmark || !currentUser || !currentUser->canEdit(bookmark)) return;
  int bookmarkIndex = bookmarks.indexOf(dynamic_cast<BookmarkModel*>(bookmark));

  if (bookmarkIndex == -1) return;

  if (newName.isEmpty() || newLink.isEmpty()) {
    emit hadUserError("Name and link are required.");
    return;
  }

  BookmarkModel *foundBookmark = bookmarks[bookmarkIndex];
  foundBookmark->editName(newName);
  foundBookmark->editLink(newLink);
  foundBookmark->editDescription(newDesc);

  ArticleModel *article = dynamic_cast<ArticleModel*>(bookmark);
  VideoModel *video = dynamic_cast<VideoModel*>(bookmark);

  if (article) {
    article->editPublication(newPublication);
    article->editMinRead(newMinRead);
  } else if (video) {
    VideoPlatform platform = VideoModel::platformFromLink(newLink);
    video->editPlatform(platform);
    video->editDuration(newDuration);
  }

  emit updatedBookmark(bookmark);
}

QVector<BookmarkInterface*> ApplicationModel::search(const QString &searchText) const {
  QVector<BookmarkInterface*> found;

  for (int i = 0; i < bookmarks.size(); i++) {
    if (bookmarks[i]->hasText(searchText)) found.push_back(bookmarks[i]);
  }

  if (!found.empty()) emit finishedSearch(found);
  else emit hadUserError("No bookmark found with this text.");

  return found;
}

void ApplicationModel::registerUser(
  const QString &name,
  const QString &surname,
  const QString &email,
  const QString &password,
  const QString &passwordConfirm) {
  if (name.isEmpty() || surname.isEmpty() || email.isEmpty() || password.isEmpty()) {
    emit hadUserError("All fields are required.");
    return;
  }

  if (password != passwordConfirm) {
    emit hadUserError("Passwords do not match");
    return;
  }

  currentUser = new UserModel(name, surname, email, password);
  users.push_back(static_cast<UserModel *>(currentUser));

  emit registeredUser(currentUser);
  emit loggedInUser(currentUser);
}

void ApplicationModel::deleteUser(UserInterface *user) {
  AdminModel *isAdmin = dynamic_cast<AdminModel*>(currentUser);
  if (!user || user == currentUser || !isAdmin) return;

  int userIndex = users.indexOf(static_cast<UserModel*>(user));
  if (userIndex == -1) return;

  users.remove(userIndex);

  emit deletedUser(user);
  // Cancella l'utente dal heap dopo il signal
  delete user;
}

void ApplicationModel::editUser(UserInterface *user, const QString &name, const QString &surname, const QString &email, const QString &password) {
  AdminModel *isAdmin = dynamic_cast<AdminModel*>(currentUser);
  if (!user || !isAdmin) return;

  int userIndex = users.indexOf(static_cast<UserModel*>(user));
  if (userIndex == -1) return;

  UserModel *foundUser = users[userIndex];
  foundUser->editName(name);
  foundUser->editSurname(surname);
  foundUser->editEmail(email);
  foundUser->editPassword(password);

  emit updatedUser(user);
}

void ApplicationModel::changeUserRole(UserInterface *user, const QString &newRole) {
  AdminModel *isAdmin = dynamic_cast<AdminModel*>(currentUser);
  if (!user || !isAdmin || user->getRole() == newRole) return;

  if (user == currentUser) {
    emit hadUserError("You cannot set the role for youself.");
    return;
  }

  UserModel* userModel = static_cast<UserModel *>(user);
  UserModel *newUser = nullptr;

  // Sostituisci l'utente con un nuovo con ruolo diverso ma stessi campi dati
  if (newRole == "user") newUser = new UserModel(*userModel);
  else if (newRole == "admin") newUser = new AdminModel(*userModel);

  newUser->setId(userModel->getId());

  int userIndex = users.indexOf(userModel);
  if (userIndex == -1) return;

  users.replace(userIndex, newUser);

  emit changedUserRole(user, newUser);
  // Cancella il vecchio utente dopo il SIGNAL
  delete user;
}

bool ApplicationModel::loginUser(const QString &email, const QString &password) {
  bool isSuccessful = authenticate(email, password);
  if (isSuccessful) emit loggedInUser(currentUser);

  return isSuccessful;
}

bool ApplicationModel::loginAdmin(const QString &email, const QString &password) {
  bool isSuccessful = authenticate(email, password);
  if (isSuccessful) emit loggedInAdmin(currentUser);

  return isSuccessful;
}

void ApplicationModel::loginAsGuest() {
  currentUser = new GuestModel();
  emit loggedInUser(currentUser);
}

void ApplicationModel::logout() {
  currentUser = nullptr;
  emit loggedOut();
}
