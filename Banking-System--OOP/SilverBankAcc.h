#pragma once
#include "BankAcc.h"
#include <iostream>

/*
	*** BankAccSilver ***

-> max_balance : 5000 RON;
-> max_deposit : 2500 RON;
-> max_withdrawal : 1000 RON;
-> tax_withdraw : 8% of the withdrawn amount;
-> max_deposits: 1 ("per24h");
-> max_withdrawals : 1 ("per24h");
-> unable to transfer any money to any other account in our bank.

	-- Advantages --
-> bonus_deposit : 3% if the amount deposited is greater than or equal to 2000 RON;
-> tax_withdraw_reduce : 5% if the amount withdrawn is greater than or equal to 800 RON;
-> the possibility to receive an amount of money less than or equal to 2000 RON from a user of our bank with a Gold or Diamond bank account.

*/

class SilverBankAcc : public BankAcc
{
private:
	static constexpr unsigned int _max_balance = 5000;
	static constexpr unsigned int _max_deposit = 2500;
	static constexpr unsigned int _max_withdrawal = 1000;
	static constexpr double _tax_withdraw = 0.08;
	static constexpr double bonus_deposit = 0.03;
	static constexpr double _tax_withdraw_reduce = 0.05;
	static constexpr unsigned int _max_amount_received = 2000;
	static constexpr bool _pos_transfer = false;
	static constexpr unsigned int _max_deposits = 1;
	static constexpr unsigned int _max_withdrawals = 1;

public:
	virtual ~SilverBankAcc() {}
	virtual bool deposit(unsigned int) override;
	virtual bool withdraw(unsigned int) override;
	virtual bool transfer(unsigned int) override;
	virtual unsigned int getMaxNumDep() override { return _max_deposits; }
	virtual unsigned int getMaxNumWith() override { return _max_withdrawals; }
	virtual unsigned int getMaxAmountReceived() override { return _max_amount_received; }
	virtual bool getPosTransf() override { return _pos_transfer; }
	virtual unsigned int getMaxBal() override { return _max_balance; }
};

bool SilverBankAcc::deposit(unsigned int amount)
{
	if (amount > _max_deposit)
	{
		std::cout << "\n\tThe deposit amount allowed to your account must not be more than " << _max_deposit << " RON !\n";
		return false;
	}

	if (amount + _balance > _max_balance)
	{
		std::cout << "\n\tThe balance of your account must not exceed the amount of " << _max_balance << " RON !\n";
		return false;
	}

	if (!(amount > 2000))
		_balance += amount;
	else
		_balance += amount + amount * bonus_deposit;

	return true;
}

bool SilverBankAcc::withdraw(unsigned int amount)
{
	if (amount > _max_withdrawal)
	{
		std::cout << "\n\tThe amount of withdrawal allowed for your account must not be more than " << _max_withdrawal << " RON !\n";
		return false;
	}

	if (_balance - amount < 0)
	{
		std::cout << "\n\tBalance of your account must not be less than 0 RON !\n";
		return false;
	}

	if (amount > 800)
		_balance -= (amount + amount * _tax_withdraw_reduce);
	else
		_balance -= (amount + amount * _tax_withdraw);

	return true;
}

bool SilverBankAcc::transfer(unsigned int amount)
{
	std::cout << "\n\tYour account does not have access to the transfer option !\n";
	return false;
}