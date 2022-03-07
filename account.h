/**
 * Assignment 5
 * Author: Danny Tram
 * This header file represents all the needed prototypes for Account class
 */
#pragma once

#include <iostream>

using namespace std;

class Account {
    /**
     * Overloading << operator returns all account owner's balances
     *
     * @param out an ostream reference
     * @param acc a constant Account reference
     * @return all account owner's balances
     */
    friend ostream &operator<<(ostream &out, const Account &acc);

public:
    /**
     * Overloading constructor initializes corresponding member variables
     *
     * @param firstName the provided first name
     * @param lastName the provided last name
     * @param id the provided account accountID
     */
    Account(string firstName, string lastName, int id);

    /**
     * The default constructor
     */
    Account();

    /**
     * This method updates the given amount based on the transaction type and
     * prints out any necessary error messages like withdrawing/transferring from
     * a fund with insufficient amount. For the linked fund types (i.e. Money
     * Market and Prime Money Market, or Long-Term and Short-Term Bond), we
     * accept overdraft protections which can transfer the desire amount to cover
     * a transaction between two linked fund types.
     *
     * @param transactionType the given transaction type (either a withdrawal, or a transfer)
     * @param fundType the given fund (must be from the pre-defined 0 to 9 fund
     * type)
     * @param amount the given amount (either to withdraw or transfer this amount)
     * @param transferringAccountID the receiving account for transfer
     * transaction. The default value is 0 for withdrawals
     * @param transferringFundType the receiving fund type. The default value is
     * @param receivingAccount a pointer to the receiving account. the default
     * value is nullptr.
     */
    void updateAmount(char transactionType, int fundType, int amount, int
    transferringAccountID = 0, int transferringFundType = 0,
                      Account *receivingAcct =
                      nullptr);

    /**
     * Returns the object's accountID
     *
     * @return the object's accountID
     */
    int getAccountID() const;

    /**
     * Prints all the funds' balances of an Account object without corresponding
     * transactions
     */
    void printAllTransactionType() const;

    /**
     * Prints all transactions corresponding to a given fund type
     *
     * @param fundType the given fund type
     */
    void printTransactionByType(int fundType) const;

private:
    string firstName;
    string lastName;
    int accountID = 0;
    static const int TOTAL_MAX_FUND_TYPES = 10;
    string transactionHistory[TOTAL_MAX_FUND_TYPES] = {"", "", "", "", "",
                                                          "",
                                                       "",
                                                       "", "", ""};

    int amountFundTypes[TOTAL_MAX_FUND_TYPES] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    /**
     * This method is only for withdrawals. If the amount of the
     * firstLinkedFundType cannot cover the given withdrawing amount, then desire
     * amount (only the partial amount needed to cover the withdrawal) from the
     * secondLinkedFundType will cover. After that, updating the transaction
     * history of both fund types.
     *
     * @param firstLinkedFundType the withdrawing account
     * @param secondLinkedFundType the covering account
     * @param amount the withdrawing amount
     */
    void updateOverDraft(int firstLinkedFundType, int
    secondLinkedFundType, int amount);
};
