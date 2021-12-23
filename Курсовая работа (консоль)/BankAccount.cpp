#include "BankAccount.h"
#include "Menu.h"

void BankAccount::setClientId(int id)
{
	client_id = id;
}

void BankAccount::setId(int id)
{
	this->id = id;
}

void BankAccount::setCash(unsigned int cash)
{
	this->cash = cash;
}

void BankAccount::setStatus(bool st)
{
	status = st;
}

void BankAccount::setName(const String& new_name)
{
	name = new_name;
}

bool BankAccount::update()
{
	BankAccount copy(*this);
	Menu update_menu;
	bool exit = true;
	while (exit)
	{
		update_menu.setOptions({
			"Название: " + name,
			"Завершить"
			});
		system("cls");
		int choise = update_menu.chooseOption();
		switch (choise)
		{
		case 0:
			name.update(0, 20, isANameChar);
			update_menu++;
			break;
		case 1:
			if (name.size() > 0)
			{
				return true;
			}
			else if (!printVerificationMessage("Название должно иметь хотя бы один символ. Повторить попытку? ", 1, "Повторить", "Назад"))
			{
				*this = copy;
				return false;
			}
			break;
		default:
			break;
		}
	}
	return false;
}

int BankAccount::compareId(BankAccount* const& src1, BankAccount* const& src2)
{
	return src1->id - src2->id;
}

int BankAccount::compareId(BankAccount* const& src1, const int& src2_id)
{
	return src1->id - src2_id;
}

int BankAccount::compareClientId(BankAccount* const& src1, BankAccount* const& src2)
{
	return src1->client_id - src2->client_id;
}

int BankAccount::compareName(BankAccount* const& src1, BankAccount* const& src2)
{
	return String::compare(src1->name, src2->name);
}

int BankAccount::compareCash(BankAccount* const& src1, BankAccount* const& src2)
{
	return static_cast<int>(src1->cash) - src2->cash;
}

int BankAccount::type() const
{
	return 0;
}

void BankAccount::print(std::ostream& out) const
{
	out << type() << " " << id << " " << client_id << " " << cash << " " << status << " " << name;
}

void BankAccount::read(std::istream& in)
{
	in >> id >> client_id >> cash >> status >> name;
}

Vector<String> BankAccount::toArray() const
{
	Vector<String> res;
	res.reserve(5);
	res.push(String::toString(id));
	res.push(String::toString(client_id));
	res.push(status ? "Активен" : "Заморожен");
	res.push(name);
	res.push(String::toString(cash));
	return res;
}

void BankAccount::transfer(int sum, BankAccount* dest)
{
	withdraw(sum);
	dest->topUp(sum);
}

void BankAccount::withdraw(int sum)
{
	if (sum > cash)
		throw -1;
	cash -= sum;
}

void BankAccount::topUp(int sum)
{
	cash += sum;
}

std::ostream& operator<<(std::ostream & out, const BankAccount & src)
{
	src.print(out);
	return out;
}

std::istream& operator>>(std::istream& in, BankAccount& src)
{
	src.read(in);
	return in;
}
