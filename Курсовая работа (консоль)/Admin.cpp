#include "Admin.h"
#include "Table.h"
#include "DataBase.h"

void Admin::menu()
{
	Menu admin;
	admin.setOptions({
		"Меню \"Аккаунты\"",
		"Меню \"Счета\"",
		"Назад"
		});
	bool exit = true;
	while (exit)
	{
		system("cls");
		int choise = admin.chooseOption();
		switch (choise)
		{
		case 0:
			accountsMenu();
			break;
		case 1:
			bankAccountsMenu();
			break;
		case 2:
			exit = false;
			break;
		default:
			break;
		}
	}
}

void Admin::accountsMenu()
{
	Menu admin;
	admin.setOptions({
		"Показать все аккаунты",
		"Сортировать",
		"Поиск по ключу",
		"Фильтр",
		"Добавить аккаунт",
		"Удалить аккаунт",
		"Изменить аккаунт",
		"Заблокировать аккаунт",
		"Подтвердить заявку",
		"Отменить последнее действие",
		"Вернуть последнее действие",
		"Назад"
		});
	bool exit = true;
	while (exit)
	{
		system("cls");
		int choise = admin.chooseOption();
		switch (choise)
		{
		case 0:
			showAllAccounts();
			break;
		case 1:
			sortAccountsMenu();
			break;
		case 2:
			searchAccountsMenu();
			break;
		case 3:
			filterMenu();
			break;
		case 4:
			additionMenu();
			break;
		case 5:
			deletionMenu();
			break;
		case 6:
			modificationMenu();
			break;
		case 7:
			blockAccountMenu();
			break;
		case 8:
			acceptAccountMenu();
			break;
		case 9:
			if (accounts.canUndo())
			{
				printVerificationMessage("Последнее действие отменено", 0);
				accounts.undo();
			}
			else
				printVerificationMessage("Нет последних действий", 0);
			break;
		case 10:
			if (accounts.canRedo())
			{
				accounts.redo();
				printVerificationMessage("Последнее действие возвращено", 0);
			}
			else
				printVerificationMessage("Нет отмен последних действий", 0);
			break;
		case 11:
			saveAccountsChanges();
			exit = false;
			break;
		default:
			break;
		}
	}
}

void Admin::showAllAccounts()
{
	system("cls");
	Table accounts_tab({ "Логин", "ID", "Статус", "Ф.И.О." });
	for (int i = 0; i < accounts.size(); i++)
		accounts_tab.addRow(accounts.at(i)->toArray());
	accounts_tab.print();
	system("pause");
}

void Admin::sortAccountsMenu()
{
	Menu sort;
	sort.setOptions({
		"По логину",
		"По ID",
		"По статусу",
		"По ФИО",
		"Назад"
		});
	system("cls");
	int choise = sort.chooseOption();
	switch (choise)
	{
	case 0:
		accounts.sort(Account::compareLogins);
		break;
	case 1:
		accounts.sort(Account::compareId);
		break;
	case 2:
		accounts.sort(Account::compareStatus);
		break;
	case 3:
		accounts.sort(Account::compareFIO);
		break;
	case 4:
		return;
		break;
	default:
		break;
	}
	Menu direction;
	direction.setOptions({
		"По возрастанию",
		"По убыванию"
		});
	system("cls");
	if (direction.chooseOption()) accounts.reverse();
}

void Admin::searchAccountsMenu()
{
	system("cls");
	std::cout << "Поиск по ключу: ";
	String key;
	Table finded_tab({ "Логин", "ID", "Статус", "Фамилия", "Имя", "Отчество" });
	key.getline(std::cin);
	for (int i = 0; i < accounts.size(); i++)
	{
		Vector<String> acc(accounts.at(i)->toArray(0));
		for (int j = 0; j < acc.size(); j++)
		{
			if (acc.at(j).toLower().find(key.toLower()))
			{
				finded_tab.addRow(acc);
				break;
			}
		}
	}
	finded_tab.print();
	system("pause");
}

void Admin::filterMenu()
{
	Menu filter;
	filter.setOptions({
		"Администараторов",
		"Клиентов",
		"Заблокированных пользователей",
		"Не рассмотренных новых пользователей",
		"Назад",
		});

	system("cls");
	std::cout << "Показать:" << std::endl;
	int choise = filter.chooseOption();
	if (choise == 4)
	{
		return;
	}
	Table accounts_tab({ "Логин", "ID", "Статус", "Фамилия", "Имя", "Отчество" });
	for (int i = 0; i < accounts.size(); i++)
	{
		if (choise == 0 && accounts.at(i)->getStatus() == Account::ADMIN
			|| choise == 1 && accounts.at(i)->getStatus() == Account::CLIENT
			|| choise == 2 && accounts.at(i)->getStatus() == Account::BLOCKED
			|| choise == 3 && accounts.at(i)->getStatus() == Account::WAITING)
		{
			accounts_tab.addRow(accounts.at(i)->toArray(0));
		}
	}
	if (accounts_tab.size() < 1)
	{
		printVerificationMessage("Пусто", 0);
		return;
	}
	system("cls");
	accounts_tab.print();
	system("pause");
}

void Admin::additionMenu()
{
	Menu addition;
	addition.setOptions({
		"Администратора",
		"Клиента",
		"Назад",
		});
	system("cls");
	int choise = addition.chooseOption();
	Account* temp = nullptr;
	switch (choise)
	{
	case 0:
		temp = new Admin;
		break;
	case 1:
		temp = new Client(Account::CLIENT);
		break;
	case 2:
		return;
		break;
	default:
		break;
	}

	while (true)
	{
		system("cls");
		if (temp->update())
		{
			if (accounts.indexOf(temp, Account::compareLogins) < 0)
			{
				accounts.add(temp);
				break;
			}
			else if (!printVerificationMessage("Логин уже зянят. Повторить попытку? ", 1, "Повторить", "Назад"))
			{
				break;
			}
		}
		else
		{
			delete temp;
			break;
		}
	}
}

void Admin::deletionMenu()
{
	system("cls");
	Table accounts_tab({ "Логин", "ID", "Статус", "Ф.И.О." });
	for (int i = 0; i < accounts.size(); i++)
		accounts_tab.addRow(accounts.at(i)->toArray());
	std::cout << "Выберите удаляемый аккаунт:" << std::endl;
	int index = accounts_tab.chooseRow();
	if (accounts.at(index) != this)
	{
		if (printVerificationMessage("Вы уверены, что хотите удалить этот аккаунт?"))
		{
			accounts.del(accounts.at(index));
		}
	}
	else
	{
		printVerificationMessage("Вы не можете удалить свой аккаунт.", 0);
	}
}

void Admin::blockAccountMenu()
{
	system("cls");
	Vector<Account*> clients;
	Table clients_tab({ "Логин", "ID", "Статус", "Ф.И.О." });
	for (int i = 0; i < accounts.size(); i++)
	{
		if (accounts.at(i)->getStatus() == Account::CLIENT)
		{
			clients.push(accounts.at(i));
			clients_tab.addRow(accounts.at(i)->toArray());
		}
	}
	if (clients.size() < 1)
	{
		printVerificationMessage("Нет клиентов, которых можно заблокировать", 0);
		return;
	}
	std::cout << "Выберите аккаунт, который нужно заблокировать:" << std::endl;
	int index = clients_tab.chooseRow();
	if (printVerificationMessage("Вы уверены, что хотите заблокировать этотого пользователя?"))
	{
		Account* temp = new Client(*clients.at(index));
		temp->setStatus(Account::BLOCKED);
		accounts.change(clients.at(index), temp);
	}
}

void Admin::acceptAccountMenu()
{
	system("cls");
	Vector<Account*> not_accepted_clients;
	Table clients_tab({ "Логин", "ID", "Статус", "Ф.И.О." });
	for (int i = 0; i < accounts.size(); i++)
	{
		if (accounts.at(i)->getStatus() == Account::WAITING)
		{
			not_accepted_clients.push(accounts.at(i));
			clients_tab.addRow(accounts.at(i)->toArray());
		}
	}
	if (not_accepted_clients.size() < 1)
	{
		printVerificationMessage("Нет неподтвержденных заявок", 0);
		return;
	}
	std::cout << "Выберите заявку, которую нужно подтвердить:" << std::endl;
	int index = clients_tab.chooseRow();
	if (printVerificationMessage("Вы уверены, что хотите подтвердить эту заявку?"))
	{
		Account* temp = new Client(*not_accepted_clients.at(index));
		temp->setStatus(Account::CLIENT);
		accounts.change(not_accepted_clients.at(index), temp);
	}
}

void Admin::modificationMenu()
{
	system("cls");
	Table accounts_tab({ "Логин", "ID", "Статус", "Ф.И.О." });
	for (int i = 0; i < accounts.size(); i++)
		accounts_tab.addRow(accounts.at(i)->toArray());
	std::cout << "Выберите изменяемый аккаунт:" << std::endl;
	Account* temp;
	int index = accounts_tab.chooseRow();
	if (accounts.at(index) != this)
	{
		if (accounts.at(index)->getStatus() == Account::ADMIN)
		{
			temp = new Admin(*accounts.at(index));
		}
		else
		{
			temp = new Client(*accounts.at(index));
		}
		while (true)
		{
			system("cls");
			if (temp->update())
			{
				if (accounts.indexOf(temp, Account::compareLogins) < 0 || accounts.indexOf(temp, Account::compareLogins) == index)
				{
					accounts.change(accounts.at(index), temp);
					break;
				}
				else if (!printVerificationMessage("Логин уже зянят. Повторить попытку? ", 1, "Повторить", "Назад"))
				{
					break;
				}
			}
			else
			{
				delete temp;
				break;
			}
		}
	}
	else
	{
		printVerificationMessage("Вы не можете изменить свой аккаунт.", 0);
	}
}

void Admin::saveAccountsChanges()
{
	if (accounts.canUndo())
	{
		if (!printVerificationMessage("Хотите сохранить последние изменения?"))
		{
			while (accounts.canUndo())
			{
				accounts.undo();
			}
		}
		else
		{
			for (int i = 0; i < bank_accounts.size(); i++)
			{
				int index = accounts.indexOfByPatameter(bank_accounts.at(i)->getClientId(), Account::compareId);
				if (index < 0 || accounts.at(index)->getStatus() == Account::BLOCKED)
				{
					bank_accounts.at(i)->setStatus(false);
				}
			}
		}
		accounts.clearUndoRedo();
		accounts.write();
		bank_accounts.write();
	}
}

void Admin::bankAccountsMenu()
{
	Menu admin;
	admin.setOptions({
		"Показать счета",
		"Показать депозиты/займы",
		"Сортировать",
		"Назад",
		});
	bool exit = true;
	while (exit)
	{
		system("cls");
		int choise = admin.chooseOption();
		switch (choise)
		{
		case 0:
			showBankAccounts();
			break;
		case 1:
			showDepLoans();
			break;
		case 2:
			sortBankAccountsMenu();
			break;
		case 3:
			exit = false;
			break;
		default:
			break;
		}
	}
}

void Admin::showBankAccounts()
{
	system("cls");
	Table bank_accounts_tab({ "ID счета", "ID клиента", "Статус", "Название", "Сумма" });
	for (int i = 0; i < bank_accounts.size(); i++)
		if (bank_accounts.at(i)->type() == 0)
			bank_accounts_tab.addRow(bank_accounts.at(i)->toArray());
	if (bank_accounts_tab.size() < 1)
	{
		printVerificationMessage("Нет открытых счетов", 0);
		return;
	}
	bank_accounts_tab.print();
	system("pause");
}

void Admin::showDepLoans()
{
	system("cls");
	Table deploans_tab({ "ID счета", "ID клиента", "Статус", "Название", "Сумма", "Тип", "Дата окончания" });
	for (int i = 0; i < bank_accounts.size(); i++)
		if (bank_accounts.at(i)->type() != 0)
			deploans_tab.addRow(bank_accounts.at(i)->toArray());
	if (deploans_tab.size() < 1)
	{
		printVerificationMessage("Нет открытых депозитов или займов", 0);
		return;
	}
	deploans_tab.print();
	system("pause");
}

void Admin::sortBankAccountsMenu()
{
	Menu sort;
	sort.setOptions({
		"По ID",
		"По ID клиента",
		"По названию",
		"По сумме",
		"Назад"
		});
	system("cls");
	int choise = sort.chooseOption();
	switch (choise)
	{
	case 0:
		bank_accounts.sort(BankAccount::compareId);
		break;
	case 1:
		bank_accounts.sort(BankAccount::compareClientId);
		break;
	case 2:
		bank_accounts.sort(BankAccount::compareName);
		break;
	case 3:
		bank_accounts.sort(BankAccount::compareCash);
		break;
	case 4:
		return;
		break;
	default:
		break;
	}
	Menu direction;
	direction.setOptions({
		"По возрастанию",
		"По убыванию"
		});
	system("cls");
	if (direction.chooseOption()) bank_accounts.reverse();
}
