/**
 * Assignment 5
 * Author: Danny Tram
 * This file represents all the function prototypes of account.h with details
 * implementations
 */

#include "account.h"
#include <sstream>

/**
 * Overloading constructor initializes corresponding member variables
 *
 * @param firstName the provided first name
 * @param lastName the provided last name
 * @param id the provided account accountID
 */
Account::Account(string firstName, string lastName, int id) : firstName{
        firstName},
                                                              lastName{
                                                                      lastName},
                                                              accountID{id} {}

/**
 * Overloading << operator returns all account owner's balances
 *
 * @param out an ostream reference
 * @param acc a constant Account reference
 * @return all account owner's balances
 */
ostream &operator<<(ostream &out, const Account &acc) {
    out << acc.firstName << " " << acc.lastName << " Account ID: " << acc
            .accountID << endl;
    out << "\tMoney Market: $" << acc.amountFundTypes[0] << endl;
    out << "\tPrime Money Market: $" << acc.amountFundTypes[1] << endl;
    out << "\tLong-Term Bond: $" << acc.amountFundTypes[2] << endl;
    out << "\tShort-Term Bond: $" << acc.amountFundTypes[3] << endl;
    out << "\t500 Index Fund: $" << acc.amountFundTypes[4] << endl;
    out << "\tCapital Value Fund: $" << acc.amountFundTypes[5] << endl;
    out << "\tGrowth Equity Fund: $" << acc.amountFundTypes[6] << endl;
    out << "\tGrowth Index Fund: $" << acc.amountFundTypes[7] << endl;
    out << "\tValue Fund: $" << acc.amountFundTypes[8] << endl;
    out << "\tValue Stock Index: $" << acc.amountFundTypes[9] << endl;
    return out;
}

/**
 * Returns the object's accountID
 *
 * @return the object's accountID
 */
int Account::getAccountID() const {
    return accountID;
}

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
void Account::updateAmount(char transactionType, int fundType, int amount,
                           int transferringAccountID, int transferringFundType,
                           Account *
                           receivingAccount) {
    stringstream ss, ss1;
    ss << "\t" << transactionType << " " << accountID << fundType << " " <<
       amount;

    if (transactionType == 'D') {
        // update the amount
        amountFundTypes[fundType] += amount;
        transactionHistory[fundType] += ss.str() + "\n";
    } else // transactionType is either a withdrawal 'W' or a transfer 'T'
    {
        if (amount <= amountFundTypes[fundType]) {
            //update the amount from the sending/withdrawing account
            amountFundTypes[fundType] -= amount;

            if (transactionType == 'W')
                transactionHistory[fundType] += ss.str() + "\n";
            else {
                // transactionType == "T"
                // update the amount of the receiving account
                receivingAccount->amountFundTypes[transferringFundType] += amount;

                // update the transaction history for the transfer-from account
                ss << " " << transferringAccountID << transferringFundType;
                transactionHistory[fundType] += ss.str() + "\n";

                // update the transaction history for the transfer-to account
                ss1 << "\tD " << transferringAccountID <<
                    transferringFundType << " " << amount << "\n";

                if (receivingAccount != this) //if the transfer is between
                    // accounts of different accountIDs
                {
                    receivingAccount->transactionHistory[transferringFundType
                    ] += ss1.str();
                } else
                    transactionHistory[transferringFundType] += ss1.str();

            }
        } else // withdrawal amount > available fund
        {
            // check for linked funds with the valid overdraft protection
            if (((fundType == 0 || fundType == 1) && amountFundTypes[0] +
                                                     amountFundTypes[1] >=
                                                     amount) ||
                ((fundType == 2 || fundType
                                   == 3) &&
                 amountFundTypes[2] + amountFundTypes[3] >= amount)) {

                if (fundType == 0)
                    updateOverDraft( 0, 1, amount);
                else if (fundType == 1)
                    updateOverDraft( 1, 0, amount);
                else if (fundType == 2)
                    updateOverDraft( 2, 3, amount);
                else
                    updateOverDraft( 3, 2, amount);

                // update the transaction history of the first (primary)
                // linked fund type
                if (transactionType == 'W')
                    transactionHistory[fundType] += ss.str() + "\n";
                else {
                    ss << " " << transferringAccountID <<
                       transferringFundType;
                    transactionHistory[fundType] += ss.str() + "\n";
                    // update the amount of receiving fund type
                    receivingAccount->amountFundTypes[transferringFundType] += amount;
                    // update the transaction history for the transfer-to account
                    ss1 << "\tD " << transferringAccountID <<
                        transferringFundType << " " << amount << "\n";

                    //if the transfer is between accounts of different
                    // accountIDs
                    if (receivingAccount != this) {
                        receivingAccount->transactionHistory[transferringFundType
                        ] += ss1.str();
                    } else
                        transactionHistory[transferringFundType] += ss1.str();
                }
            } else {
                // print out the error messages for either a withdrawal or a
                // transfer for unlinked funds with insufficient balances
                if (transactionType == 'W')
                    transactionHistory[fundType] += ss.str() + " (Failed)\n";
                else {
                    ss << " " << transferringAccountID << transferringFundType;
                    transactionHistory[fundType] += ss.str() + " (Failed)\n";
                }
            }
        }
    }
}


/**
 * Prints all the funds' balances of an Account object without corresponding
 * transactions
 */
void Account::printAllTransactionType() const {
    cout << "Displaying Transaction History for " << firstName << " " <<
         lastName << " by fund." << endl;
    cout << "Money Market: $" << amountFundTypes[0] << endl;
    cout << transactionHistory[0];
    cout << "Prime Money Market: $" << amountFundTypes[1] << endl;
    cout << transactionHistory[1];
    cout << "Long-Term Bond: $" << amountFundTypes[2] << endl;
    cout << transactionHistory[2];
    cout << "Short-term Bond: $" << amountFundTypes[3] << endl;
    cout << transactionHistory[3];
    cout << "500 Index Fund: $" << amountFundTypes[4] << endl;
    cout << transactionHistory[4];
    cout << "Capital Value Fund: $" << amountFundTypes[5] << endl;
    cout << transactionHistory[5];
    cout << "Growth Equity Fund: $" << amountFundTypes[6] << endl;
    cout << transactionHistory[6];
    cout << "Growth Index Fund: $" << amountFundTypes[7] << endl;
    cout << transactionHistory[7];
    cout << "Value Fund: $" << amountFundTypes[8] << endl;
    cout << transactionHistory[8];
    cout << "Value Stock Index: $" << amountFundTypes[9] << endl;
    cout << transactionHistory[9];
}

/**
 * Prints all transactions corresponding to a given fund type
 *
 * @param fundType the given fund type
 */
void Account::printTransactionByType(int fundType) const {

    string str = "Displaying Transaction History for " + firstName + " " +
                 lastName + "'s ";
    switch (fundType) {
        case 0:
            str += "Money Market: $";
            break;
        case 1:
            str += "Prime Money Market: $";
            break;
        case 2:
            str += "Long-Term Bond: $";
            break;
        case 3:
            str += "Short-Term Bond: $";
            break;
        case 4:
            str += "500 Index Fund: $";
            break;
        case 5:
            str += "Capital Value Fund: ";
            break;
        case 6:
            str += "Growth Equity Fund: $";
            break;
        case 7:
            str += "Growth Index Fund: $";
            break;
        case 8:
            str += "Value Fund: $";
            break;
        default:
            str += "Value Stock Index: $";
    }
    cout << str << amountFundTypes[fundType] << endl;
    cout << transactionHistory[fundType] << endl;
}

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
void Account::updateOverDraft(int firstLinkedFundType, int
secondLinkedFundType, int amount) {
    stringstream ss, ss1;
    int remainingAmount = amount - amountFundTypes[firstLinkedFundType];
    ss << "\tERROR: Transferring $" << remainingAmount << " from ";
    if (remainingAmount <= 0)
        amountFundTypes[firstLinkedFundType] -= amount;
    else {
        amountFundTypes[firstLinkedFundType] = 0;
        amountFundTypes[secondLinkedFundType] -= remainingAmount;
    }
    switch (firstLinkedFundType) {
        case 0:
            ss << "Prime Money Market to Money Market to cover "
                  "for the transaction below\n";
            break;
        case 1:
            ss << "Money Market to Prime Money Market to cover "
                  "for the transaction below\n";
            break;
        case 2:
            ss << "Short-Term Bond to Long-Term Bond to cover "
                  "for the transaction below\n";
            break;
        default:
            ss << "Long-Term Bond to Short-Term Bond to cover "
                  "for the transaction below\n";
    }
    // update the transaction history of the first linked fund type
    transactionHistory[firstLinkedFundType] += ss.str();

    // update the transaction history for the second linked fund type
    ss1 << "\tW " << accountID << secondLinkedFundType << " " <<
        remainingAmount << "\n";
    transactionHistory[secondLinkedFundType] += ss1.str();

}

/**
 * The default constructor
 */
Account::Account() = default;