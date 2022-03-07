/**
 * Assignment 5
 * Author: Danny Tram
 * This header file represents all the needed prototypes for Bank class
 */

#pragma once

#include "BSTree.h"
#include <fstream>
#include <queue>
#include "transaction.h"

using namespace std;

class Bank {

public:
    /**
     * Default constructor
     */
    Bank();

    /**
     * Default destructor
     */
    ~Bank();

    /**
     * Processes each line with corresponding Transaction objects and pushes each
     * Transaction object into a queue, which is called Phase 1. In Phase 2, we
     * pop up each Transaction object from the queue and process it with
     * appropriate methods
     *
     * @param fileName the given string file name
     */
    void processTransactions(const string &fileName);

    /**
     * Display all the accounts' balances
     */
    void displayAllBankBalances() const;

private:
    BSTree accounts;
    queue<Transaction> transactionQueue;
};
