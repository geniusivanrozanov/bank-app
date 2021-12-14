#include "Account.h"

bool Account::auth(const String& n_login, const String& n_password)
{
    return (this->login == n_login && this->password == n_password);
}

int Account::auth(Account* const& src1, Account* const& src2)
{
    return !src1->auth(src2->login, src2->password);
}

int Account::compareLogins(Account* const& src1, Account* const& src2)
{
    return String::compare(src1->login, src2->login);
}

int Account::compareId(Account* const& src1, Account* const& src2)
{
    return src1->id - src2->id;
}

Account::Account(int id, Status status, const String& login, const String& password)
    : id(id), status(status), login(login), password(password)
{
}

void Account::setLogin(const String& new_login)
{
    login = new_login;
}

void Account::setPassword(const String& new_password)
{
    password = new_password;
}

int Account::getId()
{
    return id;
}

Status Account::getStatus()
{
    return status;
}

void Account::print(std::ostream& out) const
{
    out << id <<  " " << login << " " << password << " " << status;
}

std::ostream& operator<<(std::ostream& out, const Account& src)
{
    src.print(out);
    return out;
}