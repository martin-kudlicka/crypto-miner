#ifndef POOLCREDENTIALS_H
#define POOLCREDENTIALS_H

struct PoolCredentials
{
  PoolCredentials()
  {
  }
  PoolCredentials(const QString &username, const QString &password) : username(username), password(password)
  {
  };
  PoolCredentials(const PoolCredentials &other) : username(other.username), password(other.password)
  {
  };

  QString username;
  QString password;
};

#endif