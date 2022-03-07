#include "bank.h"
#include <iostream>
#include <string>

using namespace std;

/**
 * Runs all the test cases through using text files' names as program arguments
 *
 * Test 01: Reading an empty file
 * Test 02: Reading a file with only one account with multiple
 * deposits/withdrawals/transfers
 * Test 03:
 */
int main(int argc, char *argv[]) {

    Bank bank;

    // Note that tests were done in BankTransIn.txt
    for (int i = 1; i < argc; i++) {
        cout << "The command line argument(s) was " << argv[i] << endl;
        string fileName = argv[i];
        bank.processTransactions(fileName);
        bank.displayAllBankBalances();
        cout << "Passed " << argv[i] << endl;
        cout << "*************************************************************"
             << endl;
    }
    cout << "Successfully passed all tests." << endl;
    return 0;
}