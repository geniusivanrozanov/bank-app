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

void Account::setId(int)
{
}

void Account::setLogin(const String&)
{
}

void Account::setPassword(const String&)
{
}

void Account::print(std::ostream& out) const
{
    out << id << " " << login << " " << password << " " << status;
}

void Account::read(std::istream& in)
{
    in >> id >> login >> password >> status;
}

std::ostream& operator<<(std::ostream& out, const Account& src)
{
    src.print(out);
    return out;
}

std::istream& operator>>(std::istream& in, Account& src)
{
    src.read(in);
    return in;
}

void Account::setFreeId(const Account& src)
{
    Account::free_id = src.id + 1;
}

int Account::getFreeId()
{
    return Account::free_id++;
}

int Account::free_id = 0;

