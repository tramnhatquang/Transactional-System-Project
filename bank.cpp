/**
 * Assignment 5
 * Author: Danny Tram
 * This file represents all the function prototypes of bank.h with details
 * implementations
 */

#include "bank.h"
#include <sstream>

/**
 * Default constructor
 */
Bank::Bank() = default;

/**
 * Default destructor
 */
Bank::~Bank() = default;

/**
 * Processes each line with corresponding Transaction objects and pushes each
 * Transaction object into a queue, which is called Phase 1. In Phase 2, we
 * pop up each Transaction object from the queue and process it with
 * appropriate methods
 *
 * @param fileName the given string file name
 */
void Bank::processTransactions(const string &fileName) {
    fstream myFile(fileName);
    string line;

    if (!myFile) {
        cout << "ERROR: Unable to open file";
        // Exits the method
        return;
    }

    if (myFile.peek() == std::ifstream::traits_type::eof()) {
        cout << "ERROR: The file is empty. Please use a different file" << endl;
        // Exits the method
        return;
    }

    // read each transaction into a transactionQueue
    while (getline(myFile, line) && (!line.empty())) {
        istringstream extractWord(line);
        char transactionType;
        // get the first character of each line
        extractWord >> transactionType;

        // the default fundType is 10 which is undefined until getting from
        // each line
        int fundType = 10;

        // the default accountID, amount is 0
        int accountID = 0, amount = 0;

        if (transactionType == 'O') {
            string firstName, lastName;
            extractWord >> firstName >> lastName >> accountID;
            Transaction current(transactionType, firstName, lastName,
                                accountID);
            transactionQueue.push(current);

        } else if (transactionType == 'D') {
            extractWord >> accountID >> amount;
            fundType = accountID % 10;
            accountID /= 10;
            Transaction current(transactionType, accountID, fundType, amount);
            transactionQueue.push(current);
        } else if (transactionType == 'W') {
            extractWord >> accountID >> amount;
            fundType = accountID % 10;
            accountID /= 10;
            Transaction current(transactionType, accountID, fundType, amount);
            transactionQueue.push(current);
        } else if (transactionType == 'T') {
            int transferringID, transferringType;
            extractWord >> accountID >> amount >> transferringID;
            fundType = accountID % 10;
            accountID /= 10;
            transferringType = transferringID % 10;
            transferringID /= 10;
            Transaction current(transactionType, accountID, fundType, amount,
                                transferringID, transferringType);
            transactionQueue.push(current);
        } else { // transactionType == 'H'
            extractWord >> accountID;
            if (accountID >= 10000 && accountID <= 99999) {
                fundType = accountID % 10;
                accountID /= 10;

            }
            Transaction current(transactionType, accountID, fundType);
            transactionQueue.push(current);
        }
    }

    while (!transactionQueue.empty()) {
        Transaction current = transactionQueue.front();
        if (current.getTransactionType() == 'O') {
            auto *account = new Account(current.getFirstName(), current
                    .getLastName(), current.getAccountID());
            // insert into the BStree
            accounts.Insert(account);

        } else {
            Account *account;
            if (accounts.Retrieve(current.getAccountID(), account)) {
                if (current.getTransactionType() == 'D' || current
                                                                   .getTransactionType() ==
                                                           'W') {
                    account->updateAmount(current.getTransactionType(), current
                            .getFundType(), current.getAmount());
                } else if (current.getTransactionType() == 'T') {
                    Account *receivingAccount;
                    // check for a valid receiving account
                    if (accounts.Retrieve(current.getTransferringID(),
                                          receivingAccount)) {
                        account->updateAmount(current.getTransactionType(),
                                              current.getFundType(),
                                              current.getAmount(),
                                              current.getTransferringID(),
                                              current
                                                      .getTransferringType(),
                                              receivingAccount);
                    } else
                        cout << "ERROR: Could not find the transfer-to "
                                "accountID "
                                "" <<
                             current.getTransferringID()
                             << ". Transfer transaction "
                                "refused." << endl;
                } else // transactionType == 'H'
                {
                    if (current.getFundType() == 10) // the default fundType
                        // of each Account object
                        account->printAllTransactionType();
                    else
                        account->printTransactionByType(current.getFundType());
                }
            } else {
                if (current.getTransactionType() == 'W')
                    cout << "ERROR: Could not find accountID " << current
                            .getAccountID() << ". Withdrawal transaction "
                                               "refused." << endl;
                else if (current.getTransactionType() == 'T')
                    cout << "ERROR: Could not find transfer-from ID " <<
                         current
                                 .getAccountID() << ". Transfer transaction "
                                                    "refused." << endl;
                else
                    cout << "ERROR: Could not find the accountID " << current
                    .getAccountID() << " to deposit. Deposit transaction "
                                       "refused." << endl;
            }

        }
        transactionQueue.pop();
    }
    // close the fstream
    myFile.close();
}

/**
 * Display all the accounts' balances
 */
void Bank::displayAllBankBalances() const {
    cout << endl;
    cout << "Processing Done. Final Balances." << endl;
    accounts.Display();
}


