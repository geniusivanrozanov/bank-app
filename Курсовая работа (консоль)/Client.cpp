#include "Client.h"
#include "DataBase.h"
#include "Table.h"

void Client::menu()
{
	for (int i = 0; i < bank_accounts.size(); i++)
	{
		if (bank_accounts.at(i)->getClientId() == this->getId())
		{
			my_bank_accounts.push(bank_accounts.at(i));
		}
	}
	Menu client;
	client.setOptions({
		"���� \"��� �����\"",
		"���� \"��� ��������/�����\"",
		"�����"
		});
	bool exit = true;
	while (exit)
	{
		system("cls");
		int choise = client.chooseOption();
		switch (choise)
		{
		case 0:
			bankAccountsMenu();
			break;
		case 1:
			depLoansMenu();
			break;
		case 2:
			exit = false;
			break;
		default:
			break;
		}
	}
}

void Client::bankAccountsMenu()
{
	Menu menu;
	menu.setOptions({
		"�������� ��� �����",
		"������� ����� ����",
		"��������� ����/����� �� �����/��������� �� ������ ����",
		"�����",
		});
	bool exit = true;
	while (exit)
	{
		system("cls");
		int choise = menu.chooseOption();
		switch (choise)
		{
		case 0:
			showBankAccounts();
			break;
		case 1:
			addBankAccountMenu();
			break;
		case 2:
			operationsMenu();
			break;
		case 3:
			exit = false;
			break;
		default:
			break;
		}
	}
}

void Client::showBankAccounts()
{
	system("cls");
	Table bank_accounts_tab({ "ID �����", "ID �������", "������", "��������", "�����" });
	for (int i = 0; i < my_bank_accounts.size(); i++)
		if (my_bank_accounts.at(i)->type() == 0)
			bank_accounts_tab.addRow(my_bank_accounts.at(i)->toArray());
	if (bank_accounts_tab.size() < 1)
	{
		printVerificationMessage("� ��� ��� �������� ������", 0);
		return;
	}
	bank_accounts_tab.print();
	system("pause");
}

void Client::addBankAccountMenu()
{
	BankAccount* temp = new BankAccount;
	temp->setClientId(this->getId());
	system("cls");
	if (temp->update())
	{
		my_bank_accounts.push(temp);
		bank_accounts.push(temp);
	}
	else
	{
		delete temp;
	}
}

void Client::operationsMenu()
{
	system("cls");
	Table bank_accounts_tab({ "ID �����", "ID �������", "������", "��������", "�����" });
	for (int i = 0; i < my_bank_accounts.size(); i++)
		if (my_bank_accounts.at(i)->type() == 0)
			bank_accounts_tab.addRow(my_bank_accounts.at(i)->toArray());
	if (bank_accounts_tab.size() < 1)
	{
		printVerificationMessage("� ��� ��� �������� ������", 0);
		return;
	}
	std::cout << "�������� ���� ��� ���������� ��������:" << std::endl;
	int index = bank_accounts_tab.chooseRow();

	if (!my_bank_accounts.at(index)->getStatus())
	{
		printVerificationMessage("���� ���� ���������. �������� � ��� ����������", 0);
		return;
	}

	system("cls");
	Menu operation_menu({ "��������� ����", "����� �� �����", "��������� �� ������ ����"});
	int operation = operation_menu.chooseOption();
	system("cls");
	if (operation == 0)
	{
		unsigned int sum;
		correctInput("������� ����� ��� ����������: ", sum);
		if (sum <= 100000)
		{
			my_bank_accounts.at(index)->topUp(sum);
			printVerificationMessage("���� ��� �������� �� " + String::toString(sum), 0);
		}
		else
			printVerificationMessage("����� �� ������ ��������� 100000", 0);
	}
	else if (operation == 1)
	{
		unsigned int sum;
		correctInput("������� ����� ��� ������: ", sum);
		if (sum <= 100000)
		{
			if (sum <= my_bank_accounts.at(index)->getCash())
			{
				my_bank_accounts.at(index)->withdraw(sum);
				printVerificationMessage("�� ����� ���� ����� " + String::toString(sum), 0);
			}
			else
				printVerificationMessage("�� ���� ����� ��� ����� ����� :(", 0);
		}
		else
			printVerificationMessage("����� �� ������ ��������� 100000", 0);
	}
	else if (operation == 2)
	{
		int dest_id;
		correctInput("������� ID ����� �� ������� ��������� �����: ", dest_id);
		int dest_index = bank_accounts.indexOfByPatameter(dest_id, BankAccount::compareId);
		if (dest_index < 0)
		{
			printVerificationMessage("�� ���������� ������ �����", 0);
			return;
		}

		unsigned int sum;
		correctInput("������� ����� ��� ��������: ", sum);
		if (sum <= 100000)
		{
			if (sum <= my_bank_accounts.at(dest_index)->getCash())
			{
				if (bank_accounts.at(dest_index) != bank_accounts.at(index) && bank_accounts.at(dest_index)->type() == 0)
				{
					my_bank_accounts.at(index)->transfer(sum, bank_accounts.at(dest_index));
					printVerificationMessage("�� ����� ���� ���������� " + String::toString(sum) + " �� ������ ����", 0);
				}
				else
				{
					printVerificationMessage("����� ��������� �� ���� ����", 0);
				}
			}
			else
				printVerificationMessage("�� ���� ����� ��� ����� ����� :(", 0);
		}
		else
			printVerificationMessage("����� �� ������ ��������� 100000", 0);
	}
}

void Client::depLoansMenu()
{
	Menu menu;
	menu.setOptions({
		"�������� ��� ��������/�����",
		"������� ����� �������/����",
		"�������� �������/����",
		"�����",
		});
	bool exit = true;
	while (exit)
	{
		system("cls");
		int choise = menu.chooseOption();
		switch (choise)
		{
		case 0:
			showDepLoans();
			break;
		case 1:
			addDepLoanMenu();
			break;
		case 2:
			//operationsMenu();
			break;
		case 3:
			exit = false;
			break;
		default:
			break;
		}
	}
}

void Client::showDepLoans()
{
	system("cls");
	Table deploans_tab({ "ID �����", "ID �������", "������", "��������", "�����", "���", "���� ��������" });
	for (int i = 0; i < my_bank_accounts.size(); i++)
		if (my_bank_accounts.at(i)->type() != 0)
			deploans_tab.addRow(my_bank_accounts.at(i)->toArray());
	if (deploans_tab.size() < 1)
	{
		printVerificationMessage("� ��� ��� ��������� ��� ������", 0);
		return;
	}
	deploans_tab.print();
	system("pause");
}

void Client::addDepLoanMenu()
{
	DepLoan* temp = nullptr;
	Menu dep_or_loan({
		"������� ��� 10%",
		"���� ��� 15%",
		"�����",
	});
	system("cls");
	std::cout << "�������:" << std::endl;
	int choise = dep_or_loan.chooseOption();
	if (choise == 2)
	{
		return;
	}
	temp = new DepLoan(!choise, Date() + Date(1, 0, 0));
	temp->setClientId(this->getId());
	if (!temp->update())
	{
		return;
	}
	system("cls");
	std::cout << "�������� ����, "
		<< (choise ? "�� ������� ��������� ������ � �����" : "� �������� ��������� ������ �� ���������� ����")
		<< std::endl;
	Table bank_accounts_tab({ "ID �����", "ID �������", "������", "��������", "�����" });
	for (int i = 0; i < my_bank_accounts.size(); i++)
		if (my_bank_accounts.at(i)->type() == 0)
			bank_accounts_tab.addRow(my_bank_accounts.at(i)->toArray());
	if (bank_accounts_tab.size() < 1)
	{
		printVerificationMessage("� ��� ��� �������� ������", 0);
		return;
	}
	int index = bank_accounts_tab.chooseRow();
	unsigned int sum;
	system("cls");
	correctInput("������� �����: ", sum);
	if (sum <= 100000)
	{
		if (!choise)
		{
			if (sum <= my_bank_accounts.at(index)->getCash())
			{
				my_bank_accounts.at(index)->withdraw(sum);
				temp->setCash(sum * 1.1);
				my_bank_accounts.push(temp);
				bank_accounts.push(temp);
				printVerificationMessage("������� ������, ����� ��� �� ������� ������� " + String::toString(temp->getCash()), 0);
			}
			else
				printVerificationMessage("�� ���� ����� ��� ����� ����� :(", 0);
		}
		else
		{
			my_bank_accounts.at(index)->topUp(sum);
			temp->setCash(sum * 1.15);
			my_bank_accounts.push(temp);
			bank_accounts.push(temp);
			printVerificationMessage("���� ������, � ������� ���� ��������� ���� ���� �� " + String::toString(temp->getCash()), 0);
		}
	}
	else
		printVerificationMessage("����� �� ������ ��������� 100000", 0);
}