#pragma once
#include "String.h"
#include "DataBase.h"
#include <iostream>

class Account
{
private:
	int id;
	String login;
	String password;
	int status;

	static int free_id;
public:
	static int getFreeId();
	static void setFreeId(const Account&);

	void setId(int);
	void setLogin(const String&);
	void setPassword(const String&);
	void setStatus(int);

	bool auth(const String&, const String&);

	static int auth(Account *const&, Account *const&);
	static int compareLogins(Account *const&, Account *const&);
	static int compareId(Account *const&, Account *const&);

	virtual void print(std::ostream&) const;
	virtual void read(std::istream&);

	friend std::ostream& operator<<(std::ostream&, const Account&);
	friend std::istream& operator>>(std::istream&, Account&);
};