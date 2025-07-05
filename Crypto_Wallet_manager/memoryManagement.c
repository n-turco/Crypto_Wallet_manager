#include "Assignment3.h"
//
//FUNCTION : initializeWallet
//DESCRIPTION : This function creates the stack by allocating a specific number of slots that are the size of the walletSlot struck.
//PARAMETERS : 	does not have any parameters.
//RETURNS : returns a pointer to the array of a given size able to hold the transactions when they are added.
//
int* intializeWallet(void) {
	//creates a pointer to allocate memory in the size of the struct walletSlot
	walletSlot* wallet = (double*)malloc(sizeof(walletSlot));
	if (wallet == NULL) {
		fprintf(stderr, "Memory allocation failed.\n");
		return 1;
	}
	//allocates a specified size of memory to hold an array of structs to size of walletSlot
	wallet = (double*)malloc(MAX_WALLET_SIZE * (sizeof(walletSlot)));
	if (wallet == NULL) {
		fprintf(stderr, "Memory allocation failed.\n");
		return 1;
	}
	return wallet;
}
//
//FUNCTION : newTransaction
//DESCRIPTION : This function takes a number value from the user and creates a new walletSlot to add the to array
//PARAMETERS : 	double currencyAmount - a number stored as a double data type
//RETURNS : returns a walletSlot* pointer to the new transaction being created
//
walletSlot* newTransaction(double currencyAmount) {
	//allocates memory for a new walletSlot to hold the transaction information.
	walletSlot* nuTransaction = (walletSlot*)malloc(sizeof(walletSlot));
	if (nuTransaction == NULL) {
		printf("No memory available.\n");
		return 1;
	}
	//intializes a new transaction and sets the dollar amount to the user supplied value, processed and refund flag to false.
	currencyAmount = nuTransaction->dollarAmount; 
	nuTransaction->processed = false;
	nuTransaction->refunded = false;
	return nuTransaction;
}

void addTransaction(walletSlot* transaction, double currencyAmount) {
	if (transaction == NULL) {
		transaction = intializeWallet();
	}
	walletSlot* addTransaction = newTransaction(currencyAmount);
}
//
//FUNCTION : pushToWallet
//DESCRIPTION : This function takes a pointer to the wallet and a pointer to the transaction to be added.
//PARAMETERS : 	walletSlot* transactions - pointer to the stack
//				walletSlot* transactionToAdd - pointer to the transaction to be added
//RETURNS : does not have a return value.
//
void pushToWallet(walletSlot* transactions, walletSlot* transactionToAdd) {
	if (isWalletFull(transactions)) {
		printf("Wallet is Full.\n");
		return 1;
	}
	printf("Adding Transaction...\n");
	transactions[++transactions->topIndex] = *transactionToAdd;
}
//
//FUNCTION : freeAllocatedMemory
//DESCRIPTION : This function takes a pointer to the array and frees the each transaction.
//PARAMETERS : 	walletSlot* transaction - pointer to the stack
//RETURNS : does not have a return value.
//
void freeAllocatedMemory(walletSlot* transaction) {
	if (transaction != NULL) {
		if (transaction->dollarAmount != NULL) {
			free(transaction->dollarAmount);
		}
		free(transaction);
	}
	else {
		printf("No memory to be freed.\n");
	}
	//transaction = NULL;
 }
