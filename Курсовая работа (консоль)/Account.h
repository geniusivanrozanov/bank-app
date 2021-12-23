#pragma once
#include "String.h"
#include "Array.h"
#include "Identifier.h"
#include "Menu.h"
#include <iostream>



class Account
{
public:
	enum Status
	{
		WAITING = -2,
		BLOCKED,
		CLIENT,
		ADMIN,
	};

private:
	int id;
	Status status;

	String login;
	String password;

	String surname;
	String name;
	String patronymic;
public:

	Account() : id(Identifier<Account>::getFreeId()) {};
	Account(Status st, int id) : status(st), id(id) {};
	Account(const Account& src)
		: id(src.id), status(src.status), login(src.login), password(src.password),
		surname(src.surname), name(src.name), patronymic(src.patronymic)
	{}
	virtual void menu() {};

	void setLogin(const String&);
	void setPassword(const String&);
	void setStatus(Status st) { status = st; }
	void setSurname(const String&);
	void setName(const String&);
	void setPatronymic(const String&);
	bool update();

	int getId();
	Status getStatus();
	String getFIO();

	const String& getLogin() { return login; }
	const String& getPassword() { return password; }
	const String& getSurname() { return surname; }
	const String& getName() { return name; }
	const String& getPatronymic() { return patronymic; }

	bool auth(const String&, const String&);
	bool validate();

	static int auth(Account* const&, Account* const&);
	static int compareLogins(Account* const&, Account* const&);
	static int compareId(Account* const&, Account* const&);
	static int compareId(Account* const&, const int&);
	static int compareStatus(Account* const&, Account* const&);
	static int compareFIO(Account* const&, Account* const&);

	virtual void print(std::ostream&) const;
	virtual void read(std::istream&);

	Vector<String> toArray(bool = 1);

	friend std::ostream& operator<<(std::ostream&, const Account&);
	friend std::istream& operator>>(std::istream&, Account&);
};

const int MIN_LOGIN_SIZE = 4;
const int MAX_LOGIN_SIZE = 20;
const int MIN_PASSWORD_SIZE = 4;
const int MAX_PASSWORD_SIZE = 20;