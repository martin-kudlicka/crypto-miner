#ifndef POOLCREDENTIALS_H
#define POOLCREDENTIALS_H

struct PoolCredentials
{
  PoolCredentials()
  {
  }
  PoolCredentials(const QString &wallet, const QString &password) : wallet(wallet), password(password)
  {
  };
  PoolCredentials(const PoolCredentials &other) : wallet(other.wallet), password(other.password)
  {
  };

  QString wallet;
  QString password;
};

#endif