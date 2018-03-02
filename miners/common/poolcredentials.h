#ifndef POOLCREDENTIALS_H
#define POOLCREDENTIALS_H

struct PoolCredentials
{
  QString username;
  QString password;

  PoolCredentials()
  {
  }
  PoolCredentials(const QString &username, const QString &password) : username(username), password(password)
  {
  }
  PoolCredentials(const PoolCredentials &other) : username(other.username), password(other.password)
  {
  }
  PoolCredentials &operator=(const PoolCredentials &other)
  {
    username = other.username;
    password = other.password;

    return *this;
  }
};

#endif