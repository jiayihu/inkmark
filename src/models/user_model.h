#ifndef INKMARK_ROLES_MODEL_H
#define INKMARK_ROLES_MODEL_H

#include <QString>
#include "bookmark_model.h"

/**
 * Interfaccia utenti usate dalle views con solo metodi const, per evitare
 * modifiche dirette
 */
class UserInterface {
 public:
  virtual ~UserInterface() {};
  virtual QString getName() const = 0;
  virtual QString getSurname() const = 0;
  virtual QString getEmail() const = 0;
  virtual QString getPassword() const = 0;
  virtual QString getRole() const = 0;
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
  static int idCount;
  static void setIdCount(int value);

  UserModel();
  UserModel(const QString &n, const QString &s, const QString &e, const QString &pw);
  UserModel(const UserModel &user);

  /**
   * Setta l'id. Utile per la copia senza cambiare l'id, cosa che avviene con
   * il costruttore di copia e l'operatore di assegnazione
   */
  void setId(int newId);
  int getId() const;
  QString getName() const override;
  QString getSurname() const override;
  QString getEmail() const override;
  QString getPassword() const override;
  QString getRole() const override;
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

  virtual UserModel& operator=(const UserModel& copy);
};

class AdminModel: public UserModel {
 public:
  AdminModel();
  AdminModel(const QString &n, const QString &s, const QString &e, const QString &pw);
  // E' disponibile la copia da UserModel, AdminModel non ha nessun campo dati in più
  AdminModel(const UserModel &copy);

  QString getRole() const override;
  bool canEdit(BookmarkInterface *bookmark) const override;
  bool canAdd() const override;
  bool canDelete(BookmarkInterface *bookmark) const override;
  bool canAccessAdmin() const override;

};

class GuestModel: public UserInterface {
 public:

  QString getName() const override;
  QString getSurname() const override;
  QString getEmail() const override;
  QString getPassword() const override;
  QString getRole() const override;
  bool canEdit(BookmarkInterface *bookmark) const override;
  bool canAdd() const override;
  bool canDelete(BookmarkInterface *bookmark) const override;
  bool canAccessAdmin() const override;
};

#endif //INKMARK_ROLES_MODEL_H
