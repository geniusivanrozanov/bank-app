#include "Form.h"

void AuthForm::show()
{
	printField("\b\b\b\b\b\b�����:", String(width, ' '));
	pos.Y += 3;
	printField("\b\b\b\b\b\b\b������:", String(width, ' '));
	pos.Y += 3;
	printField("", button);
	pos.Y -= 5;
	pos.X += 1;
}

Account* AuthForm::init()
{
	bool flag = true;
	int index_of_account;
	Account temp;
	String login;
	String password;
	temp.setName("-");
	temp.setSurname("-");
	temp.setPatronymic("-");
	Menu menu({}, 3, '\0', '\0');
	while (flag)
	{
		pos.X--;
		pos.Y--;
		show();
		moveConsoleCursor(pos.X, pos.Y, 0, 0);
		temp.setLogin(login);
		temp.setPassword(password);
		menu.setOptions({
			login,
			String(password.size(), '*'),
			button
			});
		int choise = menu.chooseOption();
		switch (choise)
		{
		case 0:
			login.update(0, width, isALoginChar);
			menu++;
			break;
		case 1:
			password.update(1, width, isAPasswordChar);
			menu++;
			break;
		case 2:
			if (temp.validate())
			{
				index_of_account = accounts.indexOf(&temp, Account::auth);
				if (index_of_account >= 0)
					return accounts.at(index_of_account);
				else if(!printVerificationMessage("�������� ����� ��� ������. ��������� �������? ", 1, "���������", "�����"))
					return nullptr;
			}
			else if (!printVerificationMessage("��������� �������? ", 1, "���������", "�����"))
			{
				flag = false;
			}
			system("cls");
			break;
		default:
			break;
		}
	}
	return nullptr;
}

void Form::printField(const String& outer_text, const String& inner_text)
{
	COORD pos_copy = pos;
	moveConsoleCursor(pos_copy.X, pos_copy.Y++, 0, 0);
	std::cout << " " << String(width, char(151)) << " ";
	moveConsoleCursor(pos_copy.X, pos_copy.Y++, 0, 0);
	std::cout << outer_text << "|" << inner_text << "|";
	moveConsoleCursor(pos_copy.X, pos_copy.Y++, 0, 0);
	std::cout << " " << String(width, char(151)) << " ";
}

void RegForm::show()
{
	printField("\b\b\b\b\b\b�����:", String(width, ' '));
	pos.Y += 3;
	printField("\b\b\b\b\b\b\b������:", String(width, ' '));
	pos.Y += 3;
	printField("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b��������� ������:", String(width, ' '));
	pos.Y += 3;
	printField("\b\b\b\b\b\b\b\b�������:", String(width, ' '));
	pos.Y += 3;
	printField("\b\b\b\b���:", String(width, ' '));
	pos.Y += 3;
	printField("\b\b\b\b\b\b\b\b\b��������:", String(width, ' '));
	pos.Y += 3;
	printField("", button);
	pos.Y -= 17;
	pos.X += 1;
}

Account* RegForm::init()
{
	bool flag = true;
	int index_of_account;
	Account* temp = new Client(Account::WAITING);
	String login;
	String password;
	String sec_password;
	String surname;
	String name;
	String patronymic;
	Menu menu({}, 3, '\0', '\0');
	while (flag)
	{
		pos.X--;
		pos.Y--;
		show();
		moveConsoleCursor(pos.X, pos.Y, 0, 0);
		temp->setLogin(login);
		temp->setPassword(password);
		temp->setSurname(surname);
		temp->setName(name);
		temp->setPatronymic(patronymic);
		menu.setOptions({
			login,
			String(password.size(), '*'),
			String(sec_password.size(), '*'),
			surname,
			name,
			patronymic,
			button
			});
		int choise = menu.chooseOption();
		switch (choise)
		{
		case 0:
			login.update(0, width, isALoginChar);
			menu++;
			break;
		case 1:
			password.update(1, width, isAPasswordChar);
			menu++;
			break;
		case 2:
			sec_password.update(1, width, isAPasswordChar);
			menu++;
			break;
		case 3:
			surname.update(0, width, isANameChar);
			menu++;
			break;
		case 4:
			name.update(0, width, isANameChar);
			menu++;
			break;
		case 5:
			patronymic.update(0, width, isANameChar);
			menu++;
			break;
		case 6:
			if (temp->validate())
			{
				if (password == sec_password)
				{
					index_of_account = accounts.indexOf(temp, Account::compareLogins);
					if (index_of_account < 0)
						return temp;
					else if (!printVerificationMessage("����� ��� �����. ��������� �������? ", 1, "���������", "�����"))
					{
						delete temp;
						return nullptr;
					}
				}
				else
				{
					printVerificationMessage("������ �� ���������. ��������� �������? ", 1, "���������", "�����");
				}
			}
			else if (!printVerificationMessage("��������� �������? ", 1, "���������", "�����"))
			{
				flag = false;
			}
			system("cls");
			break;
		default:
			break;
		}
	}
	return nullptr;
}

void MainForm::show()
{
	printField("", "       �����        ");
	pos.Y += 3;
	printField("", " ������������������ ");
	pos.Y += 3;
	printField("", "       �����        ");
	pos.Y -= 5;
	pos.X += 1;
}

Account* MainForm::init()
{
	int exit = true;
	Menu main_menu({
		"       �����        ",
		" ������������������ ",
		"       �����        "
	}, 3, '\0', '\0');
	Form* form = nullptr;
	Account* curr_account = nullptr;
	while (exit)
	{
		pos.X--;
		pos.Y--;
		show();
		moveConsoleCursor(pos.X, pos.Y, 0, 0);
		int choise = main_menu.chooseOption();
		system("cls");
		switch (choise)
		{
		case 0:
			form = new AuthForm(MAX_LOGIN_SIZE);
			curr_account = form->init();
			if (curr_account)
			{
				if (curr_account->getStatus() == Account::BLOCKED)
				{
					printVerificationMessage("��� ������� ��� ������������", 0);
				}
				else if (curr_account->getStatus() == Account::WAITING)
				{
					printVerificationMessage("��������. ����� ������������� ������ ���� ������", 0);
				}
				else
				{
					printVerificationMessage("����� ����������, " + curr_account->getFIO(), 0);
					curr_account->menu();
				}
			}
			curr_account = nullptr;
			break;
		case 1:
			form = new RegForm(MAX_LOGIN_SIZE);
			curr_account = form->init();
			if (curr_account)
			{
				printVerificationMessage("��������. ����� ������������� ������ ���� ������", 0);
				accounts.add(curr_account);
			}
			curr_account = nullptr;
			break;
		case 2:
			exit = false;
			break;
		default:
			break;
		}
		system("cls");
	}
	return nullptr;
}
