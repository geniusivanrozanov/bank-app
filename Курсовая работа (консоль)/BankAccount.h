#pragma once
#include <iostream>


class BankAccount
{
private:
	int id;
	int client_id;
	unsigned int cash;
	bool status;
public:
	int getClientId() const;
	int getId() const;
	unsigned int getCash() const;
	bool getStatus() const;

	void setClientId(int);
	void setId(int);
	void setCash(unsigned int);
	void setStatus(bool);

	static int compareId(BankAccount* const& src1, BankAccount* const& src2);
	static int compareClientId(BankAccount* const& src1, BankAccount* const& src2);
	static int compareCash(BankAccount* const& src1, BankAccount* const& src2);

	virtual int type() const;
	virtual void print(std::ostream&) const;
	virtual void read(std::istream&);

	friend std::ostream& operator<<(std::ostream&, const BankAccount&);
	friend std::istream& operator>>(std::istream&, BankAccount&);
};

