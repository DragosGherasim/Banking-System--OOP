#pragma once
#include "BankAcc.h"
#include <iostream>

/*
	*** GoldBankAcc ***

-> max_balance : 10000 RON;
-> max_deposit : 5000 RON;
-> max_withdrawal : 3500 RON;
-> tax_withdraw : 6% of the withdrawn amount;
-> max_deposits : 1 ("per24h");
-> max_withdrawals : 1 ("per24h").

	-- Advantages --
-> bonus_deposit : 3% if the amount deposited is greater than or equal to 4700;
-> tax_withdraw_reduce : 5% if the amount withdrawn is greater than or equal to 3200 RON;
-> the possibility to receive an amount less than or equal to 4000 RON from a user of our bank with a Gold or Diamond bank account;
-> the possibility to send an amount less than or equal to 2000 RON to a user of our bank with a Silver, Gold or Diamond bank account.

*/

class GoldBankAcc : public BankAcc
{
private:
	static constexpr unsigned int _max_balance = 10000;
	static constexpr unsigned int _max_deposit = 5000;
	static constexpr unsigned int _max_withdrawal = 3500;
	static constexpr double _tax_withdraw = 0.06;
	static constexpr double _bonus_deposit = 0.05;
	static constexpr double _bonus_tax_withdraw = 0.04;
	static constexpr unsigned int _max_amount_received = 4000;
	static constexpr unsigned int _max_transfer = 2000;
	static constexpr bool _pos_transfer = true;
	static constexpr unsigned int _max_deposits = 1;
	static constexpr unsigned int _max_withdrawals = 1;

public:
	virtual ~GoldBankAcc() {}
	virtual bool deposit(unsigned int) override;
	virtual bool withdraw(unsigned int) override;
	virtual bool transfer(unsigned int);
	virtual unsigned int getMaxNumDep() override { return _max_deposits; }
	virtual unsigned int getMaxNumWith() override { return _max_withdrawals; }
	virtual unsigned int getMaxAmountReceived() override { return _max_amount_received; }
	virtual bool getPosTransf() override { return _pos_transfer; }
	virtual unsigned int getMaxBal() override { return _max_balance; }
};

bool GoldBankAcc::deposit(unsigned int amount)
{
	if (amount > _max_deposit)
	{
		std::cout << "\n\tThe deposit amount allowed for your account must not be more than " << _max_deposit << " RON !\n";
		return false;
	}

	if (amount + _balance > _max_balance)
	{
		std::cout << "\n\tThe balance of your account should not exceed the amount of " << _max_balance << " RON !\n";
		return false;
	}

	if (!(amount >= 4700))
		_balance += amount;
	else
		_balance += amount + amount * _bonus_deposit;

	return true;
}

bool GoldBankAcc::withdraw(unsigned int amount)
{
	if (amount > _max_withdrawal)
	{
		std::cout << "\n\tThe amount of withdrawal allowed for your account must not be more than" << _max_withdrawal << " RON !\n";
		return false;
	}

	if (_balance - amount < 0)
	{
		std::cout << "\n\tYour account balance should not be less than 0 RON !\n";
		return false;
	}

	if (amount > 3200)
		_balance -= (amount + amount * _bonus_tax_withdraw);
	else
		_balance -= (amount + amount * _tax_withdraw);

	return true;

}

bool GoldBankAcc::transfer(unsigned int amount)
{
	if (_balance > amount)
	{
		if (amount <= _max_transfer)
			return true;
		else
		{
			std::cout << "\n\tThe transfer amount is higher than the maximum accepted for your account ( " << _max_transfer << " RON ) !\n";
			return false;
		}
	}

	std::cout << "\n\tThe transfer amount is higher than your balance ( " << _balance << " RON ) !\n";
	return false;
}