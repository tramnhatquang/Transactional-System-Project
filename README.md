# Transactional System Project

## 1. Design Phase:
There are five classes, including the main function. The others are BSTree, Account, Transaction, and Bank classes. This assignment has two main data structures: a template queue from C++ standard library and my implementation binary search tree (BST). All the important methods and attributes are listed in the attached UML file. 
## 2. How Classes Interact:
  The Bank class reads the provided file name with each line corresponding to a proper transaction. After that, it will proceed with three phases. In Phase 1, each line will be processed to a proper Transaction object and push it to a queue. All lines from the text file will be processed after Phase 1 before continuing to other phases. In Phase 2, the queue will pop up each Transaction object until it is empty. For each 
Transaction object being popped out, we create an Account object for each opening Transaction and follow the proper procedures for each account like transferring, withdrawing, or depositing funds. We will create proper methods to avoid any transactions causing negative balances to each account’ funds. More details about the acceptable overdraft protection are in the assignment description.  
  Meanwhile, each new opening account must be inserted into the BST based on its unique account ID. After Phase 2, the queue must be empty, and all opening accounts are in the BST. In Phase 3, Bank object will print out all the accounts’ fund balances based on given transactions.  
## 3. Errors and how to handle: 
•	Assume all the inputs are correctly formatted and used 
•	Avoid some common errors like withdrawing and transferring funds can cause negative balances 
•	Avoid doing transactions with an invalid account ID 
•	Printing out proper error messages for each error 
•	Make sure all classes interact with each other as expected. Check memory leak if needed 
•	Make sure some linked fund can do overdraft protection (more details on the assignment description) 
# 4. Testing: 
•	Build more test cases to make sure the program compiled, run smoothly, and covers all the edge cases 
•	Make sure the program output is approximately like the given output (e.g., the BankTransOut.txt) 
