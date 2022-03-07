/**
 * Assignment 5
 * Author: Danny Tram
 * This header file represents all the needed prototypes for BSTree class
 */
#pragma once

#include "account.h"
#include <iostream>

using namespace std;

class BSTree {
public:
    /**
     * Default constructor initializes the root
     */
    BSTree();

    /**
     * Destructor deletes every new created Node
     */
    ~BSTree();

    /**
     * Inserts an Account object using a binary search tree
     *
     * @param account an Account pointer pointing to an inserting Account object
     * @return
     */
    bool Insert(Account *);

    /**
     * Retrieves the Account object that has the given account ID
     *
     * @param accountID  the account ID of the Account object
     * @param account an Account pointer pointing to found object, otherwise
     * nullptr
     * @return true if finding the Account object that has the given account ID.
     * Otherwise, returns false
     */
    bool Retrieve(const int &, Account *&) const;

    /**
     * Displays all the accounts' fund balances. Prints out an error if there are
     * no account opening
     */
    void Display() const;

    /**
     * Deletes all information in the Account binary search tree
     */
    void Empty();

    /**
     * Returns true if the Account binary search tree is empty. Otherwise,
     * returns false
     *
     * @return true if the Account binary search tree is empty. Otherwise,
     * returns false
     */
    bool isEmpty() const;


private:
    struct Node {
        Account *pAcct;
        Node *right = nullptr;
        Node *left = nullptr;
    };
    Node *root;

    /**
     * Traverses each Node using recursion through the Account binary search tree
     * and prints out each account' fund balances
     *
     * @param current a Node pointer pointing to the current Node
     */
    void recursiveDisplay(Node *current) const;

    /**
     * Traverses each Node using recursion through the Account binary search tree
     * and inserts each Node if found a nullptr Node
     *
     * @param current a Node pointer pointing to the current Node
     * @param account an Account pointer pointing to the inserting Account object
     * @return
     */
    bool recursiveInsert(Node *current, Account *account);

    /**
     * Traverses each Node using recursion through the Account binary search tree
     * and deletes each Node
     *
     * @param current a Node pointer pointing to the current Node
     */
    void recursiveDelete(Node *&current);

};