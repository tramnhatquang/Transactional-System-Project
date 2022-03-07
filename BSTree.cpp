/**
 * Assignment 5
 * Author: Danny Tram
 * This file represents all the function prototypes of BSTree.h with details
 * implementations
 */
#include "BSTree.h"

/**
 * Default constructor initializes the root
 */
BSTree::BSTree() : root(nullptr) {}

/**
 * Destructor deletes every new created Node
 */
BSTree::~BSTree() {
    recursiveDelete(root);
}

/**
 * Inserts an Account object using a binary search tree
 *
 * @param account an Account pointer pointing to an inserting Account object
 * @return
 */
bool BSTree::Insert(Account *account) {
    int accountID = account->getAccountID();
    if (accountID < 1000 || accountID > 9999) {
        cout << "ERROR: Account number " << accountID << " is not a 4 digit "
                                                         "type "
                                                         "account. "
                                                         "Open transaction "
                                                         "refused." << endl;
        return false;
    }

    if (root == nullptr) {
        root = new Node();
        root->pAcct = account;
        return true;
    }
    return recursiveInsert(root, account);

}


/**
 * Retrieves the Account object that has the given account ID
 *
 * @param accountID  the account ID of the Account object
 * @param account an Account pointer pointing to found object, otherwise
 * nullptr
 * @return true if finding the Account object that has the given account ID.
 * Otherwise, returns false
 */
bool BSTree::Retrieve(const int &accountID, Account *&account) const {
    Node *current = root;
    if (current == nullptr) {
        cout << "ERROR: Could not find account " << accountID << ". "
                                                                 "Transaction refused."
             << endl;
        account = nullptr;
    }
    while (current != nullptr) {
        if (current->pAcct->getAccountID() == accountID) {
            account = current->pAcct;
            return true;
        } else if (accountID < current->pAcct->getAccountID())
            current = current->left;
        else
            current = current->right;
    }
    return false;
}

/**
 * Displays all the accounts' fund balances. Prints out an error if there are
 * no account opening
 */
void BSTree::Display() const {
    if (isEmpty()) {
        cout << "ERROR: There are no account opening." << endl;
        return;
    }
    recursiveDisplay(root);
}

/**
 * Deletes all information in the Account binary search tree
 */
void BSTree::Empty() {
    delete root;
    root = nullptr;
}

/**
 * Returns true if the Account binary search tree is empty. Otherwise,
 * returns false
 *
 * @return true if the Account binary search tree is empty. Otherwise,
 * returns false
 */
bool BSTree::isEmpty() const {
    return root == nullptr;
}

/**
 * Traverses each Node using recursion through the Account binary search tree
 * and prints out each account' fund balances
 *
 * @param current a Node pointer pointing to the current Node
 */
void BSTree::recursiveDisplay(BSTree::Node *current) const {
    if (current == nullptr)
        return;
    recursiveDisplay(current->left);
    cout << *(current->pAcct) << endl;
    recursiveDisplay(current->right);

}

/**
 * Traverses each Node using recursion through the Account binary search tree
 * and deletes each Node
 *
 * @param current a Node pointer pointing to the current Node
 */
void BSTree::recursiveDelete(BSTree::Node *&current) {
    if (current != nullptr) {
        recursiveDelete(current->left);
        recursiveDelete(current->right);
        delete current;
        current = nullptr;
    }
}

/**
 * Traverses each Node using recursion through the Account binary search tree
 * and inserts each Node if found a nullptr Node
 *
 * @param current a Node pointer pointing to the current Node
 * @param account an Account pointer pointing to the inserting Account object
 * @return
 */
bool BSTree::recursiveInsert(BSTree::Node *current, Account *account) {
    if (account->getAccountID() == current->pAcct->getAccountID()) {
        cout << "ERROR: AccountID " << account->getAccountID() << " is already "
                                                                "open. "
                                                                "Transaction "
                                                                "refused." <<
             endl;
        return false;
    } else if (account->getAccountID() < current->pAcct->getAccountID()) {
        if (current->left == nullptr) {
            Node *newNode = new Node();
            newNode->pAcct = account;
            current->left = newNode;
            return true;
        }
        return recursiveInsert(current->left, account);
    } else {
        if (current->right == nullptr) {
            Node *newNode = new Node();
            newNode->pAcct = account;
            current->right = newNode;
            return true;
        }
        return recursiveInsert(current->right, account);
    }

}



