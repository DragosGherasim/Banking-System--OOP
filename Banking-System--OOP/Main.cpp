#include "Bank.h"
#include <iostream>

int main()
{
	Bank bank;
	bank.inputUsers();

	UserAcc us_acc;

	while (true)
	{
		system("CLS");
		std::cout << "\n\t\t\t\t============== Welcome to ~~ OOP Bank ~~~ ==============\n\n\n\tChoose one of the options given by the main menu :\n";
		std::cout << "\t\t1. Log into your bank account;\n\t\t2. Register new account;\n\t\t3. Exit from menu.\n";
		std::size_t opt_princ_menu{ 0 }, stop_princ_menu{ 0 };
		std::cout << "\n\tAnswer : ";
		std::cin >> opt_princ_menu;

		std::string user, pass;

		while (true)
		{
			system("CLS");
			std::size_t res_princ_menu{ 0 };
			switch (opt_princ_menu)
			{
			case 1:
			{
				std::cin.ignore();
				std::cout << "\n\t\t\t\t\t============== Log In ============== ";
				std::cout << "\n\n\t\tUser : ";
				std::getline(std::cin, user);

				std::cout << "\n\t\tPassword : ";
				pass = takePasswdFromUser('*');

				if (!bank.userVerif(user, pass, us_acc))
				{
					std::cout << "\n\tIf you want to make an account at our bank, type 1. If you think you entered the wrong user or password, type 2 to resume the login process, otherwise, type 0, to return to the main menu.\n";
					std::size_t op_regist{ 0 };
					std::cout << "\n\tAnswer : ";
					std::cin >> op_regist;

					if (op_regist == 0)
					{
						res_princ_menu = 1;
						break;
					}
					else if (op_regist == 2)
					{
						opt_princ_menu = 1;
						break;
					}

					opt_princ_menu = 2;
					break;
				}
				while (true)
				{
					system("CLS");
					std::cout << "\n\t\t\t============== Welcome to your account " << us_acc.getName() << " ! ============== \n";

					std::cout << "\n\n\tChoose the option you want to use from the menu displayed by typing the digit in front of the option : \n";
					std::cout << "\t\t1. Deposit;\n\t\t2. Withdraw;\n\t\t3. Transfer;\n\t\t4. Change your bank account type;\n\t\t5. Delete User;\n\t\t9. Exit.\n";
					std::cout << "\n\tAnswer : ";
					std::size_t opt_acc_menu{ 0 };
					std::cin >> opt_acc_menu;
					std::cin.ignore();

					std::size_t stop_acc_menu{ 0 };

					switch (opt_acc_menu)
					{

					case 1:
					{
						if (us_acc.getMaxNumAccDep() > us_acc.getNumUsDep())
						{

							while (true)
							{
								system("CLS");
								std::cout << "\n\tYou have chosen the Bank Deposit option. What amount you want to deposit ? (amount must be multiple of 5)\n";
								std::cout << "\n\tAmount : ";
								unsigned int amount{ 0 };
								std::cin >> amount;

								if (!bank.verifAmountInput(amount))
								{
									std::cout << "\n\tThe deposit process has failed !\n";
									std::cout << "\n\tIf you want to re-enter a correct amount, type 1, otherwise, if you want to return to the Account Menu, type 0.\n";
									std::size_t rel_sum_dep{ 0 };
									std::cout << "\n\tAnswer : ";
									std::cin >> rel_sum_dep;

									if (rel_sum_dep == 1)
										continue;

									break;
								}


								if (!us_acc.deposit(amount))
								{
									std::cout << "\tThe deposit process has failed !\n";
									std::cout << "\n\tIf you want to resume the deposit process, type 1, otherwise, if you want to return to the Account Menu, type 0.\n";
									std::size_t res_dep{ 0 };
									std::cout << "\n\tAnswer : ";
									std::cin >> res_dep;

									if (res_dep == 1)
										continue;

									break;
								}

								system("CLS");
								std::cout << "\n\tThe deposit transaction took place successfully!\n";
								bank.modifBankAfterDepWithTransfSwap(us_acc);
								std::cout << "\n\tYour updated balance is : " << us_acc.getAccBal() << " ron.\n";
								std::cout << "\n\tPress ENTER to return to the Account Menu ... ";
								std::cin.ignore();
								std::cin.get();
								break;
							}
						}
						else
						{
							system("CLS");
							std::cout << "\n\tYou have exceeded the maximum number of deposits for your bank account type, in 24h! You will return to to the bank account menu.\n";
							std::cout << "\n\tPress ENTER to return to the Account Menu ... ";
							std::cin.get();
							break;
						}

						break;
					}

					case 2:
					{
						if (us_acc.getMaxNumAccWith() > us_acc.getNumUsWith())
						{

							while (true)
							{
								system("CLS");
								std::cout << "\n\tYou have chosen the Bank Withdrawal option. What amount you want to withdraw (amount must be multiple of 5) : \n";
								std::cout << "\n\tAmount : ";
								unsigned int amount{ 0 };
								std::cin >> amount;

								if (!bank.verifAmountInput(amount))
								{
									std::cout << "\tThe withdrawal transaction failed!\n";
									std::cout << "\n\tIf you want to re-enter a correct amount, type 1, otherwise, if you want to return to the Account Menu, type 0.\n";
									std::size_t res_amount_with{ 0 };
									std::cout << "\n\tAnswer : ";
									std::cin >> res_amount_with;

									if (res_amount_with == 1)
										continue;

									break;
								}


								if (!us_acc.withdraw(amount))
								{
									std::cout << "\tThe withdrawal transaction failed!\n";
									std::cout << "\n\tIf you want to resume the withdrawal process, type 1, otherwise, if you want to return to the Account Menu, type 0.\n";
									std::size_t res_with{ 0 };
									std::cout << "\n\tAnswer : ";
									std::cin >> res_with;

									if (res_with == 1)
										continue;

									break;
								}

								system("CLS");
								std::cout << "\n\tThe withdrawal transaction was successful!!\n";
								bank.modifBankAfterDepWithTransfSwap(us_acc);
								std::cout << "\n\tYour updated balance is : " << us_acc.getAccBal() << " ron.\n";
								std::cout << "\n\tPress ENTER to return to the Account Menu ... ";
								std::cin.ignore();
								std::cin.get();
								break;
							}
						}
						else
						{
							system("CLS");
							std::cout << "\n\tYou have exceeded the maximum number of withdrawals for your bank account type, in 24h! You will return to to the bank account menu.\n";
							std::cout << "\n\tPress ENTER to return to the Account Menu ... ";
							std::cin.get();
							break;
						}

						break;
					}

					case 3:
					{
						if (us_acc.posTransfer())
						{
							while (true)
							{
								system("CLS");
								std::cout << "\n\tYou have chosen the Bank Transfer option ! Choose the person to whom you want to transfer an amount of money (multiple of 5) by typing his user code. ( Do not use your own code :) ! )\n";
								std::cout << "\n\tEnter the user's code : ";
								std::string transf_code;
								std::getline(std::cin, transf_code);

								if (us_acc.getUsCode() != transf_code && bank.existingCodeVerif(transf_code))
								{
									while (true)
									{
										std::cout << "\n\tAmount : ";
										unsigned int amount{};
										std::cin >> amount;
										std::cin.ignore();

										if (bank.verifAmountInput(amount) && us_acc.transferAmount(amount) && bank.transferProcess(us_acc, transf_code, amount))
										{
											std::cout << "\n\tThe transfer transaction was successful ! Your account balance is: " << us_acc.getAccBal() << " RON !\n";
											std::cout << "\n\tPress ENTER to return to the Account Menu ... ";
											std::cin.get();
											break;
										}
										else
										{
											std::cout << "\n\tIf you want to enter a new amount of money, type 1, otherwise, type 0, if you want to return to your bank account menu .\n";
											unsigned int opt_amount{};
											std::cout << "\n\tAnswer : ";
											std::cin >> opt_amount;
											if (opt_amount)
												continue;
											break;
										}
									}

									break;
								}

								else
								{
									std::cout << "\n\tThe transfer process failed !\n";
									std::cout << "\n\tIf you want to enter a new user code, type 1, otherwise, if you want to return to your bank account menu, type 0.\n";
									std::size_t res_input_user_code;
									std::cout << "\n\tAnswer : ";
									std::cin >> res_input_user_code;
									std::cin.ignore();
									if (res_input_user_code == 1)
										continue;
									break;
								}
							}
						}
						else
						{
							system("CLS");
							std::cout << "\n\tYour bank account does not have the option to make a bank transfer, you will be redirected to the your Account Menu!\n";
							std::cout << "\n\tPress ENTER to return to the Account Menu ... ";
							std::cin.get();
							break;
						}

						break;
					}

					case 4:
					{
						while (true)
						{
							system("CLS");
							std::cout << "\n\tYou have chosen the option to Change Your Bank Account Type ! Choose one of our accounts : \n";
							std::cout << "\n\t\t1. Silver Bank Account;\n\t\t2. Gold Bank Account;\n\t\t3. Diamond Bank Account.\n";
							std::cout << "\n\tAnswer : ";
							std::size_t opt_bank_acc_type{ 0 };
							std::cin >> opt_bank_acc_type;

							std::string head_code;
							if (opt_bank_acc_type == 1)
								head_code = "SBA";
							else if (opt_bank_acc_type == 2)
								head_code = "GBA";
							else
								head_code = "DBA";

							if (bank.modifSwapAcc(us_acc, head_code))
							{
								std::cout << "\n\tThe move took place successfully! You will return to the bank account menu .\n";
								std::cout << "\n\tPress ENTER to return to the Account Menu ... ";
								std::cin.ignore();
								std::cin.get();
								break;
							}
							else
							{
								std::cout << "\n\tThe swappingping process has failed !\n";
								std::cout << "\n\tIf you want to resume the swapping process, type 1, otherwise, if you want to return to the Account Menu, type 0.\n";
								std::size_t res_swapping{ 0 };
								std::cout << "\n\tAnswer : ";
								std::cin >> res_swapping;

								if (res_swapping == 1)
									continue;

								break;
							}
						}
						break;
					}

					case 5:
					{
						if (us_acc.getAccBal() < 5)
						{
							while (true)
							{
								system("CLS");
								std::cout << "\n\tYou have chosen the option to Delete Your UserAcc at our bank ! Enter your password again .\n";
								if (!bank.deleteUs(us_acc))
								{
									std::cout << "\n\tAccount deletion failed! Type 1, if you want to resume the process of deleting the account, otherwise, type 0 if you want to return to the bank account menu!\n";
									std::size_t op_deleting;
									std::cout << "\n\tAnswer : ";
									std::cin >> op_deleting;

									if (op_deleting == 1)
										continue;
									break;
								}
								std::cout << "\n\tThe deletion of the account took place successfully! You will be redirected to the main menu of the bank.\n";
								stop_acc_menu = 1;
								std::cout << "\n\tPress ENTER to return to the Account Menu ... ";
								std::cin.get();
								break;
							}
						}
						else
						{
							system("CLS");
							std::cout << "\n\tDeleting the account failed because you have an amount greater than or equal to 5 ron in your balance! We recommend that you withdraw the maximum amount you can!\n";
							std::cout << "\n\tPress ENTER to return to the Account Menu ... ";
							std::cin.get();
							break;
						}

						break;
					}

					case 9:
					{
						system("CLS");
						std::cout << "\n\tYou have chosen to exit the Bank Account Menu.\n";
						std::cout << "\n\tPress ENTER to return to the Account Menu ... ";
						std::cin.get();
						stop_acc_menu = 1;
						break;
					}

					default:
						system("CLS");
						std::cout << "\n\tYou did no type the digit corresponding to the given menu options. Try again !\n";
						break;
					}

					if (stop_acc_menu == 1)
					{
						res_princ_menu = 1;
						break;
					}
				}

				break;
			}

			case 2:
			{
				std::cin.ignore();
				std::cout << "\n\tWe are glad that you have chosen to register in our bank !\n";
				if (bank.userRegist(us_acc))
				{
					system("CLS");
					std::cout << "\n\tCongratulations " << us_acc.getName() << ", your account has been successfully created!\n";
					std::cout << "\n\tIf you want to return to the main menu, type 1, otherwise, if you want to exit the program type 0!\n";
					std::cout << "\n\tAnswer : ";
					std::size_t res_regist;
					std::cin >> res_regist;

					if (res_regist == 1)
					{
						res_princ_menu = 1;
						break;
					}

					opt_princ_menu = 3;
					break;
				}
				else
				{
					system("CLS");
					std::cout << "\n\tRegistration process has stopped !\n";
					std::cout << "\n\n\tIf you want to exit the program, type 0, otherwise, type 1, to return to the main menu.\n";
					std::cout << "\n\tAnswer : ";
					std::size_t res_regist;
					std::cin >> res_regist;

					if (res_regist == 1)
					{
						res_princ_menu = 1;
						break;
					}

					opt_princ_menu = 3;
					break;
				}
			}

			case 3:
			{
				system("CLS");
				std::cout << "\n\tYou have chosen to close the program. We welcome you next time !\n";
				stop_princ_menu = 1;
				res_princ_menu = 1;
				break;
			}

			default:
			{
				system("CLS");
				std::cout << "\n\tYou did not type the digit corresponding to the given menu options. Try again !\n";
				res_princ_menu = 1;
				break;
			}
			}

			if (res_princ_menu == 1)
				break;
		}

		if (stop_princ_menu == 1)
			break;
	}

	return 0;
}


