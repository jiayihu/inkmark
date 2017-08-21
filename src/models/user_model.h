#ifndef INKMARK_ROLES_MODEL_H
#define INKMARK_ROLES_MODEL_H

#include <QString>
#include "bookmark_model.h"

class UserInterface {
 public:
  virtual ~UserInterface() {};
  virtual QString getName() const = 0;
  virtual QString getSurname() const = 0;
  virtual QString getEmail() const = 0;
  virtual QString getPassword() const = 0;
  virtual bool canEdit(BookmarkInterface*) const = 0;
  virtual bool canAdd() const = 0;
  virtual bool canDelete(BookmarkInterface*) const = 0;
  virtual bool canAccessAdmin() const = 0;
};

class UserModel: public UserInterface {
 private:
  int id;
  QString name;
  QString surname;
  QString email;
  QString password;

 public:
  UserModel();
  UserModel(const QString &n, const QString &s, const QString &e, const QString &pw);
  UserModel(const UserModel &user);

  int getId() const;
  QString getName() const override;
  QString getSurname() const override;
  QString getEmail() const override;
  QString getPassword() const override;
  void editName(const QString &newName);
  void editSurname(const QString &newSurname);
  void editEmail(const QString &newEmail);
  void editPassword(const QString &newPassword);
  bool canEdit(BookmarkInterface *bookmark) const override;
  bool canAdd() const override;
  bool canDelete(BookmarkInterface *bookmark) const override;
  bool canAccessAdmin() const override;

  virtual void readFromJSON(const QJsonObject &json);
  virtual void writeToJSON(QJsonObject &json) const;

  UserModel& operator=(const UserModel& copy);

  static int idCount;
};

class AdminModel: public UserModel {
 public:
  AdminModel();
  AdminModel(const QString &n, const QString &s, const QString &e, const QString &pw);

  bool canEdit(BookmarkInterface *bookmark) const override;
  bool canAdd() const override;
  bool canDelete(BookmarkInterface *bookmark) const override;
  bool canAccessAdmin() const override;

  void writeToJSON(QJsonObject &json) const override;
};

class GuestModel: public UserModel {
 public:

  bool canEdit(BookmarkInterface *bookmark) const override;
  bool canAdd() const override;
  bool canDelete(BookmarkInterface *bookmark) const override;
};

#endif //INKMARK_ROLES_MODEL_H
