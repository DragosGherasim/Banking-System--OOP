# Banking-System -- OPP | C++

Banking system it is my first project implemented in C++, using the concept of Object Oriented Programming.

The access to the bank account is based on *Login* process. For the new users, there is a *Register* option.

The bank has 3 bank accounts (***Silver, Gold, Diamond Bank Account***), each with different deposit limits, withdrawal limits, fees etc. ( *more details in .h files* )

The project is based on a *Menu Program*, each option is realized when pressing the corresponding digit of the process.



### UML Class Diagram
![](https://i.imgur.com/SRNJsQ8.png)



The following classes are implemented :
- ***UserAcc*** ( used to create a bank user's account );
- ***BankAcc*** ( is an abstract class, belonging to UserAccount, which determines the type of bank account and account's balance );
- ***SilverBankAcc, GoldBankAcc, DiamondBankAcc*** ( are classes inherited from BankAcc, which determine the details of each bank account );
- ***Bank*** ( is used to store all accounts in the Bank DataBase, update it, making the user login to his account, registration of a new account, etc. ).


In addition to this :
* ***DataBase.txt*** ( Bank database );
* ***encryp_decryp_pass.cpp*** ( the user's password is encrypted in the database, using a *key*, basically, each letter of the alphabet, each digit and symbols gets reaplaced by another character );
* ***hidingpass.cpp*** \****borrowed code***\* ( while typing the password from the keyboard , a number of \'\*' will be displayed, depending on the number of characters ).


### Defining The Type of A Bank Account
 The process of defining the ***Type of a Bank Account*** is realized using the principle of *Polymorphism*. Each user owns a *code* ("SBA73852"), consisting of a *head_code* ("SBA") and *tale_code* ("73852"). UserAccount *has* a *shared_ptr* to the abstract class, BankAcc. Depending on the head_code, the BankAcc object will be used as a specific bank account type.
