#include "Account.h"

bool Account::auth(const String& n_login, const String& n_password)
{
	return (this->login == n_login && this->password == n_password);
}

bool Account::validate()
{
	if (login.size() < MIN_LOGIN_SIZE)
	{
		printVerificationMessage("Короткий логин (мин. " + String::toString(MIN_LOGIN_SIZE)
			+ " символов). Повторить попытку? ", 0);
		return false;
	}
	else if (password.size() < MIN_PASSWORD_SIZE)
	{
		printVerificationMessage("Короткий пароль (мин. " + String::toString(MIN_PASSWORD_SIZE)
			+ " символов). Повторить попытку? ", 0);
		return false;
	}
	else if (!surname.size() || !name.size() || !patronymic.size())
	{
		return printVerificationMessage("Фамилия, Имя или Отчество не были заполнены. Повторить попытку? ", 0);
		return false;
	}
	return true;
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

int Account::compareId(Account* const& src, const int& src_id)
{
	return src->id - src_id;
}

int Account::compareStatus(Account* const& src1, Account* const& src2)
{
	return src1->status - src2->status;
}

int Account::compareFIO(Account* const& src1, Account* const& src2)
{
	int res = String::compare(src1->surname, src2->surname);
	if (!res)
	{
		res = String::compare(src1->name, src2->name);
	}
	if (!res)
	{
		res = String::compare(src1->patronymic, src2->patronymic);
	}
	return res;
}

void Account::setLogin(const String& new_login)
{
	login = new_login;
}

void Account::setPassword(const String& new_password)
{
	password = new_password;
}

void Account::setSurname(const String& new_surname)
{
	surname = new_surname;
}

void Account::setName(const String& new_name)
{
	name = new_name;
}

void Account::setPatronymic(const String& new_patronymic)
{
	patronymic = new_patronymic;
}

bool Account::update()
{
	Account copy(*this);
	Menu update_menu;
	bool exit = true;
	while (exit)
	{
		update_menu.setOptions({
			"Логин: " + login,
			"Пароль: " + password,
			"Фамилия: " + surname,
			"Имя: " + name,
			"Отчество: " + patronymic,
			"Завершить",
		});
		system("cls");
		int choise = update_menu.chooseOption();
		switch (choise)
		{
		case 0:
			login.update(0, MAX_LOGIN_SIZE, isALoginChar);
			update_menu++;
			break;
		case 1:
			password.update(0, MAX_PASSWORD_SIZE, isAPasswordChar);
			update_menu++;
			break;
		case 2:
			surname.update(0, MAX_LOGIN_SIZE, isANameChar);
			uppercase(surname.at(0));
			update_menu++;
			break;
		case 3:
			name.update(0, MAX_LOGIN_SIZE, isANameChar);
			uppercase(name.at(0));
			update_menu++;
			break;
		case 4:
			patronymic.update(0, MAX_LOGIN_SIZE, isANameChar);
			uppercase(patronymic.at(0));
			update_menu++;
			break;
		case 5:
			if (validate())
			{
				return true;
			}
			else if (!printVerificationMessage("Повторить попытку? ", 1, "Повторить", "Назад"))
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

int Account::getId()
{
	return id;
}

Account::Status Account::getStatus()
{
	return status;
}

String Account::getFIO()
{
	String FIO(surname);
	FIO += " ";
	FIO += name.at(0);
	FIO += ".";
	FIO += patronymic.at(0);
	FIO += ".";
	return FIO;
}

void Account::print(std::ostream& out) const
{
	out << status << " " << login << " " << password << " " << id
		<< " " << surname << " " << name << " " << patronymic;
}

void Account::read(std::istream& in)
{
	in.get();
	in >> login >> password >> id >> surname >> name >> patronymic;
}

Vector<String> Account::toArray(bool shorted)
{
	Vector<String> arr;
	arr.reserve(shorted ? 4 : 6);
	arr.push(login);
	arr.push(String::toString(id));
	switch (status)
	{
	case WAITING:
		arr.push("Не подтвержден");
		break;
	case BLOCKED:
		arr.push("Заблокирован");
		break;
	case CLIENT:
		arr.push("Клиент");
		break;
	case ADMIN:
		arr.push("Администратор");
		break;
	default:
		break;
	}
	if (shorted)
	{
		arr.push(getFIO());
	}
	else
	{
		arr.push(surname);
		arr.push(name);
		arr.push(patronymic);
	}
	return arr;
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
