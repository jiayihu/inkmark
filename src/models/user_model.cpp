#include "user_model.h"

int UserModel::idCount = 0;

void UserModel::setIdCount(int value) {
  idCount = value;
}

UserModel::UserModel(): id(++idCount) {}

UserModel::UserModel(const QString &n, const QString &s, const QString &e, const QString &pw)
  : id(++idCount), name(n), email(e), surname(s), password(pw) {}

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

int UserModel::getId() const { return id; }
QString UserModel::getName() const { return name; }
QString UserModel::getSurname() const { return surname; }
QString UserModel::getEmail() const { return email; }
QString UserModel::getPassword() const { return password; }
void UserModel::editName(const QString &newName) { name = newName; }
void UserModel::editSurname(const QString &newSurname) { surname = newSurname; }
void UserModel::editEmail(const QString &newEmail) { email = newEmail; }
void UserModel::editPassword(const QString &newPassword) { email = newPassword; }

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
  json.insert("role", "user");
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

bool AdminModel::canEdit(BookmarkInterface *bookmark) const { return true; }

bool AdminModel::canAdd() const { return true; }

bool AdminModel::canDelete(BookmarkInterface *bookmark) const { return true; }

bool AdminModel::canAccessAdmin() const { return true; }

void AdminModel::writeToJSON(QJsonObject &json) const {
  UserModel::writeToJSON(json);
  // Rimpiazza il ruolo "user" della classe base con "admin"
  json.insert("role", "admin");
}

/**
 * GuestModel
 */

QString GuestModel::getName() const { return "Guest"; }
QString GuestModel::getSurname() const { return "User"; }

bool GuestModel::canEdit(BookmarkInterface *bookmark) const { return false; }

bool GuestModel::canAdd() const { return false; }

bool GuestModel::canDelete(BookmarkInterface *bookmark) const { return false; }
