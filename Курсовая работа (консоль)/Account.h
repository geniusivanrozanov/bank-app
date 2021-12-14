#pragma once
#include "String.h"
#include <iostream>

enum Status
{
	BLOCKED = -1,
	CLIENT,
	ADMIN,
};

class Account
{
private:
	const int id;
	const Status status;

	String login;
	String password;
public:
	Account(int, Status, const String&, const String&);

	void setLogin(const String&);
	void setPassword(const String&);

	int getId();
	Status getStatus();

	bool auth(const String&, const String&);

	static int auth(Account *const&, Account *const&);
	static int compareLogins(Account *const&, Account *const&);
	static int compareId(Account *const&, Account *const&);

	virtual void print(std::ostream&) const;

	friend std::ostream& operator<<(std::ostream&, const Account&);
};