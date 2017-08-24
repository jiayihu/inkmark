#ifndef INKMARK_MODEL_H
#define INKMARK_MODEL_H

#include <QString>
#include <QVector>
#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include "bookmark_model.h"
#include "user_model.h"

/**
 * Classe che gestisce il model dell'applicazione. Nessun'altra classa può
 * modificare il model dell'applicazione, infatti tutti i metodi ritornano al
 * massimo puntatori di tipo BookmarkInterface, che contiene solo metodi virtuali
 * marcati const.
 *
 * Per ogni modifica/aggiunta al model bisogna richiamarne un metodo, che provvederà
 * a fare la modifica e fare emit di un SIGNAL di cui è in ascolto qualunque
 * parte dell'applicazione sia interessata.
 *
 * Esiste inoltre un'unica istanza di ApplicationModel, che contiene tutti i dati
 * di interesse globale per l'applicazione come la lista di bookmarks.
 */
class ApplicationModel: public QObject {
  Q_OBJECT

 private:
  QVector<BookmarkModel*> bookmarks;
  // Lista di utenti registrati, non ci possono essere GuestModel
  QVector<UserModel*> users;
  // Utente loggato, può essere GuestModel, UserModel o AdminModel
  UserInterface* currentUser;

  void clean();
  bool authenticate(const QString &email, const QString &password);

 public:
  // Solo il distruttore è necessario per ora, non è previsto l'uso di costruttore
  // di copia o operatore di assegnazione per l'ApplicationModel
  ~ApplicationModel();

  // Restituisce un vettore di bookmarks da usare nelle views
  QVector<BookmarkInterface*> getBookmarks() const;
  // Restituisce un vettore di utenti da usare nelle views
  QVector<UserInterface*> getUsers() const;

  void readFromJSON(const QJsonObject &json);
  void writeToJSON(QJsonObject &json) const;

 public slots:
  void addBookmark(
    const QString &name,
    const QString &link,
    const QString &description,
    const BookmarkType &type,
    const QDate &pubblication,
    const QTime &minRead,
    const QTime &duration
  );
  void deleteBookmark(BookmarkInterface *bookmark);
  void editBookmark(BookmarkInterface *bookmark, const QString &newName, const QString &newLink, const QString &newDesc);
  QVector<BookmarkInterface*> search(const QString &searchText) const;

  void registerUser(const QString &name, const QString &surname, const QString &email, const QString &password, const QString &passwordConfirm);
  void deleteUser(UserInterface *user);
  void editUser(UserInterface *user, const QString &name, const QString &surname, const QString &email, const QString &password);
  void changeUserRole(UserInterface *user, const QString &newRole);
  void loginAsGuest();
  bool loginUser(const QString &email, const QString &password);
  bool loginAdmin(const QString &email, const QString &password);
  void logout();

 signals:
  void hadUserError(QString message) const;

  void addedBookmark(BookmarkInterface *bookmark);
  void deletedBookmark(BookmarkInterface *bookmark);
  void updatedBookmark(BookmarkInterface *bookmark);
  void finishedSearch(QVector<BookmarkInterface*> results) const;

  void registeredUser(UserInterface *user) const;
  void deletedUser(UserInterface *user) const;
  void updatedUser(UserInterface *user) const;
  void changedUserRole(UserInterface *oldUser, UserInterface *newUser) const;
  void loggedInUser(UserInterface *user) const;
  void loggedInAdmin(UserInterface *user) const;
  void loggedOut() const;
};

#endif //INKMARK_MODEL_H
