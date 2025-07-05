#include "Assignment3.h"
//
//FUNCTION : initializeWallet
//DESCRIPTION : This function creates the stack by allocating a specific number of slots that are the size of the walletSlot struck.
//PARAMETERS : 	does not have any parameters.
//RETURNS : returns a pointer to the array of a given size able to hold the transactions when they are added.
//
int* intializeWallet(void) {
	//creates a pointer to allocate memory in the size of the struct walletSlot
	walletSlot* wallet = (int*)malloc(sizeof(walletSlot));
	if (wallet == NULL) {
		fprintf(stderr, "Memory allocation failed.\n");
		return 1;
	}
	//allocates a specified size of memory to hold an array of structs to size of walletSlot
	wallet = (int*)malloc(MAX_WALLET_SIZE * (sizeof(walletSlot)));
	if (wallet == NULL) {
		fprintf(stderr, "Memory allocation failed.\n");
		return 1;
	}
	return wallet;
}
//
//FUNCTION : freeAllocatedMemory
//DESCRIPTION : This function takes a pointer to the array and frees the each transaction.
//PARAMETERS : 	walletSlot* transaction - pointer to the stack
//RETURNS : does not have a return value.
//
void freeAllocatedMemory(walletSlot* transaction) {
	if (transaction == NULL) {
		printf("No memory to be freed.\n");
	}
	else {
		while (transaction != NULL) {
			free(transaction);
		}
	}
	transaction = NULL;
 }