#pragma once
#include <iostream>
#include "String.h"
#include "Array.h"
#include "Identifier.h"


class BankAccount
{
private:
	int id;
	int client_id;
	unsigned int cash;
	bool status;
	String name;
public:
	BankAccount() : id(Identifier<BankAccount>::getFreeId()), client_id(0), cash(0), status(1)
	{}

	int getClientId() const { return client_id; }
	int getId() const { return id; }
	unsigned int getCash() const { return cash; }
	bool getStatus() const { return status; }
	String getName() const { return name; }

	void setClientId(int);
	void setId(int);
	void setCash(unsigned int);
	void setStatus(bool);
	void setName(const String&);
	bool update();

	static int compareId(BankAccount* const& src1, BankAccount* const& src2);
	static int compareId(BankAccount* const& src1, const int& src2_id);
	static int compareClientId(BankAccount* const& src1, BankAccount* const& src2);
	static int compareName(BankAccount* const& src1, BankAccount* const& src2);
	static int compareCash(BankAccount* const& src1, BankAccount* const& src2);

	virtual int type() const;
	virtual void print(std::ostream&) const;
	virtual void read(std::istream&);
	virtual Vector<String> toArray() const;
	
	void transfer(int, BankAccount*);
	void withdraw(int);
	void topUp(int);

	friend std::ostream& operator<<(std::ostream&, const BankAccount&);
	friend std::istream& operator>>(std::istream&, BankAccount&);
};

