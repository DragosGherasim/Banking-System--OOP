#pragma once
#include "UserAcc.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>


class Bank
{
private:
	std::vector<UserAcc> _vec;
	static std::string _key;
	static std::string _characters;

public:
	void inputUsers();
	bool userVerif(std::string, std::string, UserAcc&);
	bool userRegist(UserAcc&);
	bool verifAmountInput(unsigned int);
	void modifBankAfterDepWithTransfSwap(const UserAcc&);
	std::string codeGen(std::string);
	bool transferProcess(UserAcc&, std::string, unsigned int);
	bool existingCodeVerif(std::string);
	bool modifSwapAcc(UserAcc&, std::string);
	void bankModifDeleteUs(std::vector<UserAcc>::iterator&);
	bool deleteUs(const UserAcc&);
};

std::string Bank::_key = "PHQGUMEAYLNFDXIRCVSBWKOZTJpregxnvystmwcqikfzaldobjuh8012594736><=?"; // encrypted _characters by each position
std::string Bank::_characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789#$!&"; // characters (alphabet + digits + 4 symbols)
std::string takePasswdFromUser(char); // return a password displayed by '*' in console
std::string encrypted_pass(std::string, std::string, std::string); // return a encrypted password
std::string decrypted_pass(std::string, std::string, std::string); // return the decrypted password
unsigned int num_pass_tries{}; // counts the number of incorrectly written passwords, in the registration process, when checking the first password

/* Adds in _vec member from Bank class, a vector of UserAccs from DataBase.txt */
void Bank::inputUsers()
{
	std::ifstream file;
	file.open("DataBase.txt");

	UserAcc temp;
	std::string code, name, user, pass;
	double balance;

	while (file >> code >> name >> balance >> user >> pass)
	{
		temp.setUsCode(code);
		temp.setName(name);
		temp.setAccBal(balance);
		temp.setUser(user);
		temp.setPass(pass);
		_vec.push_back(temp);
	}

	file.close();
}

/* Returns true if there is a UserAcc(searched by the user and pass) in _vec, also it initializes the us_acc with the informations about
his UserAcc, and return false if the user is not registered in the bank database or if the user inputs a wrong user or password */
bool Bank::userVerif(std::string user, std::string pass, UserAcc& us_acc)
{
	std::vector<UserAcc>::iterator it;

	it = std::find_if(_vec.begin(), _vec.end(), [&](const UserAcc& us_acc1) {return us_acc1.getUser() == user; });
	if (it == _vec.end())
	{
		system("CLS");
		std::cout << "\n\tThis user is not registered in our bank !\n";
		return false;
	}

	it = std::find_if(_vec.begin(), _vec.end(), [&](const UserAcc& us_acc1) {return pass == decrypted_pass(us_acc1.getPass(), _key, _characters); });
	if (it == _vec.end())
	{
		system("CLS");
		std::cout << "\n\tYou entered the wrong password !\n";
		return false;
	}

	us_acc.setNumUsDep(0);
	us_acc.setNumUsWith(0);
	us_acc.setUser(user);
	us_acc.setPass(pass);
	us_acc.setName(it->getName());
	us_acc.setUsCode(it->getUsCode());
	us_acc.setAccBal(it->getAccBal());

	return true;
}

/* Generates a random tale_code (19304) of 5 digits and concatenates it with head_code and returns it if there is no other identical user code in the bank's database */
std::string Bank::codeGen(std::string head_code)
{
	std::string tale_code;
	std::string user_code;

	srand(time(nullptr));

	while (true)
	{
		for (std::size_t i{ 0 }; i < 5; ++i)
			tale_code += '0' + rand() % 10;

		user_code = head_code + tale_code;
		std::vector<UserAcc>::iterator it;
		it = std::find_if(_vec.begin(), _vec.end(), [&](const UserAcc& us_acc) { return us_acc.getUsCode() == user_code; });

		if (it == _vec.end())
			break;
	}

	return user_code;
}


/* The registration process consists in choosing the type of bank account the user wants to use, the bank sets up his bank account, name, user (checks if the user is already used to someone else )
, password (checks if it meets the necessary requirements and encrypts it ), adds the UserAcc to the _vec ( sorts the _vec ascending by the user code ), prints it on the DataBase file, then
returns true. if the user is undecided during the choice of the bank account account, he can choose the option to exit the registration process, and the function returns false */
bool Bank::userRegist(UserAcc& us_acc)
{
	std::cout << "\n\tChoose one of our options for Bank Accounts, please type the corresponding digit : \n";

	while (true)
	{
		std::cout << "\t\t1. Silver Bank Account; \n\t\t2. Gold Bank Account; \n\t\t3. Diamond Bank Account.\n";
		std::cout << "\n\tAnswer : ";

		std::size_t op_acc{};
		std::cin >> op_acc;
		std::string head_code;
		system("CLS");

		if (op_acc == 1)
		{
			std::cout << "\n\t\t\t============== You chose option ~ Silver Bank Account ~! ==============\n\n";
			std::cout << "\n\t\tDetails SBA: ";
			std::cout << " \n\n\t-> max_balance : 5000 RON;\n\t-> max_deposit : 2500 RON;\n\t-> max_withdraw : 1000 RON;\n\t-> tax_withdraw : 8 % of the withdrawn amount;\n\t-> max_deposits : 1 (""per24h"");\n\t-> max_withdrawals : 1 (""per24h"");\n\t-> unable to transfer any money to any other account in our bank.\n\n\t\t\t-- Advantages --\n\n\t-> bonus_deposit : 3 % if the amount deposited is greater than or equal to 2000;\n\t-> tax_withdraw_reduce : 3 % if the amount deposited is greater than or equal to 20000 RON;\n\t-> the possibility to receive an amount of money less than or equal to 2000 RON from a user of our bank with a Gold or Diamond bank account.\n";
			head_code = "SBA";
		}
		else if (op_acc == 2)
		{
			std::cout << "\n\t\t\t============== You chose option ~ Gold Bank Account ~! ==============\n\n";
			std::cout << "\n\t\tDetails GBA: ";
			std::cout << "\n\n\t-> max_balance : 10000 RON;\n\t-> max_deposit : 5000 RON;\n\t-> max_withdraw : 3500 RON;\n\t-> tax_withdraw : 6 % of the withdrawn amount;\n\t-> max_deposits : 1 (""per24h"");\n\t-> max_withdrawals : 1 (""per24h"");\n\n\t\t\t-- Advantages --\n\n\t-> bonus_deposit : 3 % if the amount deposited is greater than or equal to 4700;\n\t-> tax_withdraw_reduce : 5 % if the amount deposited is greater than or equal to 3200 RON;\n\t->  the possibility to receive an amount less than or equal to 4000 RON from a user of our bank with a Gold or Diamond bank account;\n\t->  the possibility to send an amount less than or equal to 2000 RON to a user of our bank with a Silver, Gold or Diamond bank account.\n";
			head_code = "GBA";
		}

		else
		{
			std::cout << "\n\t\t\t============== You chose option ~ Diamond Bank Account ~! ==============\n\n";
			std::cout << "\n\t\tDetails DBA: ";
			std::cout << "\n\n\t-> max_balance : 50000 RON;\n\t-> max_deposit : 10000 RON;\n\t-> max_withdraw : 7000 RON;\n\t-> tax_withdraw : 3 % of the withdrawn amount;\n\t-> tax_deposit : 3 % of the deposit amount;\n\t-> max_deposits : 1 (""per24h"");\n\t-> max_withdrawals : 2 (""per24h"");\n\t\t\t-- Advantages --\n\n\t-> bonus_tax_deposit : 1 % if the amount deposited is greater than or equal to 9500 RON;\n\t-> bonus_tax_withdraw : 1 % if the amount deposited is greater than or equal to 6700 RON.\n\t->  the possibility to receive an amount less than or equal to 8500 RON from a user of our bank with a Gold or Diamond bank account;\n\t->  possibility to send an amount less than or equal to 5000 RON to a user of our bank with a Silver, Gold or Diamond bank account.\n";
			head_code = "DBA";
		}

		std::cout << "\n\n\t1. Continue registration;\n\t2. If you want to choose another type of Bank Account (return to the menu of choosing the type of Bank Account);\n\t3. Exit the registration option.\n";
		std::size_t res_bank_acc{};
		std::cout << "\n\tAnswer: ";
		std::cin >> res_bank_acc;

		if (res_bank_acc == 2)
		{
			system("CLS");
			std::cout << "\n\tChoose one of our options for Bank Accounts, please type the corresponding digit : \n";
			continue;
		}
		else if (res_bank_acc == 3)
			return false;

		std::string user_code{ codeGen(head_code) };

		us_acc.setUsCode(user_code);
		std::cin.ignore();
		break;
	}

	system("CLS");
	us_acc.setAccBal(0.0);

	std::cout << "\n\tEnter your bank account details!\n";
	std::cout << "\n\tName: ";
	std::string name;
	std::getline(std::cin, name);
	us_acc.setName(name);

	while (true)
	{
		std::string user;
		std::cout << "\tUser : ";
		std::getline(std::cin, user);

		std::vector<UserAcc>::iterator it;
		it = std::find_if(_vec.begin(), _vec.end(), [&](const UserAcc& us_acc) { return us_acc.getUser() == user; });

		if (it != _vec.end())
		{
			system("CLS");
			std::cout << "\n\tThe username has already been used, try typing a new one!\n";
			continue;
		}

		us_acc.setUser(user);
		break;
	}

	std::string pass;
	std::cout << "\n\tThe password must contain at least 8 characters, minimum one digit, minimum one capital letter, minimum one symbol from the given ones : #, $, !, &.\n";

	while (true)
	{
		num_pass_tries = 0;
		std::cout << "\n\tPassword: ";
		pass = takePasswdFromUser('*');

		if (pass.size() < 8)
		{
			std::cout << "\n\tThe password is too short, try again please ! (at least 8 characters)\n";
			continue;
		}

		unsigned int num_upp_case{ 0 }, num_digits{ 0 }, num_symbols{ 0 };

		for (std::string::iterator it{ pass.begin() }; it != pass.end(); ++it)
		{
			if (isupper(pass[it - pass.begin()]))
				++num_upp_case;

			if (isdigit(pass[it - pass.begin()]))
				++num_digits;

			if (pass[it - pass.begin()] == '#' || pass[it - pass.begin()] == '!' || pass[it - pass.begin()] == '&' || pass[it - pass.begin()] == '$')
				++num_symbols;
		}

		if (num_digits > 0 && num_upp_case > 0 && num_symbols > 0)
		{
			while (true)
			{
				std::cout << "\n\tEnter your password again : ";
				std::string same_pass;
				same_pass = takePasswdFromUser('*');

				if (pass == same_pass)
					break;

				std::cout << "\n\tThe second password is not identical to the first, try again !\n";
				++num_pass_tries;

				if (num_pass_tries == 3)
					break;

				continue;
			}

			if (num_pass_tries == 3)
			{
				system("CLS");
				std::cout << "\n\tYou have entered 3 times a password different from the first, try to write a new one.\n";
				continue;
			}

			us_acc.setPass(encrypted_pass(pass, _key, _characters));
			break;
		}
		else
		{
			std::cout << "\tThe password must contain minimum one digit, minimum one capital letter, minimum one symbol from the given ones : #, $, !, & .\n";
			continue;
		}
	}

	_vec.push_back(us_acc);
	std::sort(_vec.begin(), _vec.end(), [](UserAcc& us_acc1, UserAcc& us_acc2) {return us_acc1.getUsCode() < us_acc2.getUsCode(); });

	std::ofstream file;
	file.open("DataBase.txt");
	for (auto& v : _vec)
		file << v.getUsCode() << " " << v.getName() << " " << v.getAccBal() << " " << v.getUser() << " " << v.getPass() << "\n";

	file.close();

	return true;
}

bool Bank::verifAmountInput(unsigned int amount)
{
	if (amount % 5 == 0)
		return true;

	std::cout << "\n\tThe amount entered is incorrect, must be multiple of 5!\n";
	return false;
}

/* After a deposit, withdrawal, transfer, swapping bank accounts process, the function changes the UserAcc from _vec and also the Bank database */
void Bank::modifBankAfterDepWithTransfSwap(const UserAcc& us_acc)
{
	std::vector<UserAcc>::iterator it;
	it = find_if(_vec.begin(), _vec.end(), [&](const UserAcc& us_acc1) {return us_acc.getUser() == us_acc1.getUser(); });

	if (it->getUsCode() != us_acc.getUsCode())
		it->setUsCode(us_acc.getUsCode());

	if (it->getAccBal() != us_acc.getAccBal())
		it->setAccBal(us_acc.getAccBal());

	std::ofstream file;
	file.open("DataBase.txt");

	for (auto& v : _vec)
		file << v.getUsCode() << " " << v.getName() << " " << v.getAccBal() << " " << v.getUser() << " " << v.getPass() << "\n";

	file.close();
}

/* It is used in the transfer process to check if there is in the database of the bank the user_code for transferring the amount of money */
bool Bank::existingCodeVerif(std::string code_transf)
{
	std::vector<UserAcc>::iterator it;
	it = std::find_if(_vec.begin(), _vec.end(), [&](const UserAcc& us_acc1) { return us_acc1.getUsCode() == code_transf; });

	if (it != _vec.end())
		return true;

	std::cout << "\n\tThe user code entered is not in the DataBase of our bank !\n";
	return false;
}

/* Realizes the transfer process ,then modifies the banl database, but also check if it is possible depending on the amount given*/
bool Bank::transferProcess(UserAcc& us_acc, std::string code_transf, unsigned int amount)
{
	std::vector<UserAcc>::iterator it;
	it = std::find_if(_vec.begin(), _vec.end(), [&](const UserAcc& us_acc1) { return us_acc1.getUsCode() == code_transf; });

	if (it->getMaxBalUs() >= amount)
	{
		double check_bal = it->getAccBal() + amount;
		if (check_bal <= it->getMaxBalUs())
		{
			it->setAccBal(check_bal);
			us_acc.setAccBal(us_acc.getAccBal() - amount);
			modifBankAfterDepWithTransfSwap(us_acc);
			return true;
		}

		else
		{
			std::cout << "\n\tThe amount sent is too high for the user who receives it, his balance will exceed the maximum granted for his type of bank account .\n";
			return false;
		}
	}
	else
	{
		std::cout << "\n\tThe amount sent is greater than the maximum amount that the user can accept for his type of bank account .\n";
		return false;
	}
}

/* Realizes the swapping process, then modifies the bank database. Returns false if the password confirmation process failed */
bool Bank::modifSwapAcc(UserAcc& us_acc, std::string head_code)
{
	std::cout << "\n\tPlease confirm the swapping process typing your password .\n";
	std::cout << "\n\tPassword : ";
	std::string pass = takePasswdFromUser('*');

	if (pass == us_acc.getPass())
	{
		double temp_balance{ us_acc.getAccBal() };
		us_acc.setUsCode(codeGen(head_code));
		us_acc.setAccBal(temp_balance);
		modifBankAfterDepWithTransfSwap(us_acc);
		return true;
	}

	system("CLS");
	std::cout << "\n\tThe password is incorect !\n";
	return false;
}

/* Modifies the Bank database by displaying _vec after deleting a UserAcc */
void Bank::bankModifDeleteUs(std::vector<UserAcc>::iterator& us_acc)
{
	_vec.erase(us_acc);

	std::ofstream file;
	file.open("DataBase.txt");

	for (auto& v : _vec)
		file << v.getUsCode() << " " << v.getName() << " " << v.getAccBal() << " " << v.getUser() << " " << v.getPass() << "\n";

	file.close();
}

/* Deletes a UserAcc from _vec, the modifies the bank database. Returns false if the password confirmation process failed */
bool Bank::deleteUs(const UserAcc& us_acc)
{
	std::cout << "\n\tPassword : ";
	std::string pass = takePasswdFromUser('*');

	std::vector<UserAcc>::iterator it;
	it = std::find_if(_vec.begin(), _vec.end(), [&](const UserAcc& us_acc1) { return us_acc1.getUser() == us_acc.getUser() && us_acc.getPass() == pass; });

	if (it != _vec.end())
	{
		bankModifDeleteUs(it);
		return true;
	}

	std::cout << "\n\tPassword entered is not correct !\n";
	return false;
}