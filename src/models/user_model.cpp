#include <QDebug>
#include "user_model.h"

int UserModel::idCount = 0;

void UserModel::setIdCount(int value) {
  idCount = value;
}

UserModel::UserModel(): id(++idCount) {}

UserModel::UserModel(const QString &n, const QString &s, const QString &e, const QString &pw)
  : id(++idCount), name(n), surname(s), email(e), password(pw) {}

UserModel::UserModel(const UserModel &user)
  : id(++idCount), name(user.name), surname(user.surname), email(user.email), password(user.password) {}

UserModel& UserModel::operator=(const UserModel &copy) {
  if (&copy != this) {
    id = ++idCount;
    name = copy.name;
    surname = copy.surname;
    email = copy.email;
    password = copy.password;
  }

  return *this;
}

void UserModel::setId(int newId) { id = newId; }

int UserModel::getId() const { return id; }
QString UserModel::getName() const { return name; }
QString UserModel::getSurname() const { return surname; }
QString UserModel::getEmail() const { return email; }
QString UserModel::getPassword() const { return password; }
QString UserModel::getRole() const { return "user"; }
void UserModel::editName(const QString &newName) { name = newName; }
void UserModel::editSurname(const QString &newSurname) { surname = newSurname; }
void UserModel::editEmail(const QString &newEmail) { email = newEmail; }
void UserModel::editPassword(const QString &newPassword) { password = newPassword; }

bool UserModel::canEdit(BookmarkInterface *bookmark) const {
  return bookmark->getAuthorId() == id;
}

bool UserModel::canAdd() const { return true; }

bool UserModel::canDelete(BookmarkInterface *bookmark) const {
  return bookmark->getAuthorId() == id;
}

bool UserModel::canAccessAdmin() const { return false; }

void UserModel::readFromJSON(const QJsonObject &json) {
  id = json.value("id").toInt();
  name = json.value("name").toString();
  surname = json.value("surname").toString();
  email = json.value("email").toString();
  password = json.value("password").toString();
}

void UserModel::writeToJSON(QJsonObject &json) const {
  json.insert("id", id);
  json.insert("role", getRole());
  json.insert("name", name);
  json.insert("surname", surname);
  json.insert("email", email);
  json.insert("password", password);
}


/**
 * AdminModel
 */

AdminModel::AdminModel(): UserModel() {}

AdminModel::AdminModel(const QString &n, const QString &s, const QString &e, const QString &pw)
  : UserModel(n, s, e, pw) {}

AdminModel::AdminModel(const UserModel &user)
  : UserModel(user) {}

QString AdminModel::getRole() const { return "admin"; }

bool AdminModel::canEdit(BookmarkInterface *bookmark) const {
  Q_UNUSED(bookmark);
  return true;
}

bool AdminModel::canAdd() const { return true; }

bool AdminModel::canDelete(BookmarkInterface *bookmark) const {
  Q_UNUSED(bookmark);
  return true;
}

bool AdminModel::canAccessAdmin() const { return true; }

/**
 * GuestModel
 */

QString GuestModel::getName() const { return "Guest"; }
QString GuestModel::getSurname() const { return "User"; }
QString GuestModel::getEmail() const {
  qDebug() << "Guests don't have an email address";
  return "";
}
QString GuestModel::getPassword() const {
  qDebug() << "Guests don't have a password";
  return "";
}
QString GuestModel::getRole() const { return "guest"; }

bool GuestModel::canEdit(BookmarkInterface *bookmark) const {
  Q_UNUSED(bookmark);
  return false;
}

bool GuestModel::canAdd() const { return false; }

bool GuestModel::canDelete(BookmarkInterface *bookmark) const {
  Q_UNUSED(bookmark);
  return false;
}

bool GuestModel::canAccessAdmin() const { return false; }
