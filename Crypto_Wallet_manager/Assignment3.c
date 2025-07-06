#include "Assignment3.h"
#include <stdlib.h>



int main() {
	//intialize wallet
    wallet* walletPtr = initializeWallet();
    if (walletPtr) {
        printf("Wallet initialized successfully.\n");  
    }
	
	addTransaction(walletPtr);
	printWallet(walletPtr);
	freeWallet(walletPtr);

    return 0;
}

wallet* initializeWallet(void) {
    printf("sizeof(wallet): %zu\n", sizeof(wallet));
    printf("sizeof(walletSlot): %zu\n", sizeof(walletSlot));

    wallet* newWallet = (wallet*)malloc(sizeof(wallet));
    if (newWallet == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }

    newWallet->transactions = (walletSlot*)malloc(sizeof(walletSlot) * WALLET_CAPACITY);
    if (newWallet->transactions == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(newWallet);
        return NULL;
    }

    newWallet->topIndex = -1;
    newWallet->capacity = WALLET_CAPACITY;
    

    return newWallet;
}
//
//FUNCTION : resizeWallet
//DESCRIPTION : This function takes a pointer to the wallet and frees each transaction.
//PARAMETERS : 	wallet* walletPtr - pointer to the wallet
//RETURNS : does not have a return value.
//
bool resizeWallet(wallet* walletPtr) {
	int newCapacity = walletPtr->capacity * 2;
	walletSlot* resizedArray = (walletSlot*)realloc(walletPtr->transactions, sizeof(walletSlot) * newCapacity);
	if (resizedArray == NULL) {
		fprintf(stderr, "Failed to resize wallet.\n");
		return false;
	}

	walletPtr->transactions = resizedArray;
	walletPtr->capacity = newCapacity;
	return true;
}
//
//FUNCTION : newTransaction
//DESCRIPTION : This function takes a number value from the user and creates a new walletSlot to add the to array
//PARAMETERS : 	double currencyAmount - a number stored as a double data type
//RETURNS : returns a walletSlot struct to be added to the array
//
walletSlot newTransaction(double dollarAmount) {
    walletSlot newWalletSlot;
    //intializes a new transaction and sets the dollar amount to the user supplied value, processed and refund flag to false.
    newWalletSlot.transactionAmount = dollarAmount;
    newWalletSlot.processed = false;
    newWalletSlot.refunded = false;
    return newWalletSlot;
}
//
//FUNCTION : addTransaction
//DESCRIPTION : This function takes a pointer to the wallet and a number value from the user to create the new transaction.
//				It continues to accept transaction values until the user enters -1.
//PARAMETERS : 	walletSlot* transaction - pointer to the stack	
//RETURNS : does not have a return value.
//
void addTransaction(wallet* walletPtr) {
	//check it wallet is intialized
	if (walletPtr == NULL || walletPtr->transactions == NULL) {
		printf("Wallet not initialized properly.\n");
		return;
	}

	if (walletPtr == NULL) {
		printf("Wallet not Initialized");
		return;
	}
	double currencyAmount = 0;
	while (1) {
		printf("Enter Transaction Amount (-1 to stop): ");
if (scanf_s("%lf", &currencyAmount) != 1) {
			printf("Invalid input, enter a number.\n");
			while (getchar() != '\n');
			continue;
		}
		if (currencyAmount == -1) {
			break;
		}
		if (isWalletFull(walletPtr)) {
			printf("Wallet is full.\n");
			break;
		}
		walletSlot newSlot = newTransaction(currencyAmount);
		pushToWallet(walletPtr, newSlot);
	}
}
//
//FUNCTION : pushToWallet
//DESCRIPTION : This function takes a pointer to the wallet and a pointer to the transaction to be added.
//PARAMETERS : 	walletSlot* walletPtr - pointer to the wallet
//				walletSlot* transactionToAdd - pointer to the transaction to be added
//RETURNS : does not have a return value.
//
void pushToWallet(wallet* walletPtr, walletSlot transactionToAdd) {
	//check it wallet is intialized
	if (walletPtr == NULL || walletPtr->transactions == NULL) {
		printf("Wallet not initialized properly.\n");
		return;
	}

	if (isWalletFull(walletPtr)) {
		//checks if resizeWallet returns false
		if (!resizeWallet(walletPtr)) {
			printf("Cannot add transaction — resizing failed.\n");
			return;
		}
	}
	walletPtr->topIndex++;
	walletPtr->transactions[walletPtr->topIndex] = transactionToAdd;
}
//
//FUNCTION : IsWalletEmpty
//DESCRIPTION : This function checks if the wallet is empty.
//PARAMETERS : 	takes a struct pointer to the wallet.
//RETURNS : True if walletPtr == -1 else it returns false.
//
bool isWalletEmpty(wallet* walletPtr) {
	return walletPtr->topIndex == -1;
}
//
//FUNCTION : IsWalletFull
//DESCRIPTION : This function checks if the stack is empty
//PARAMETERS : 	takes a struct pointer to the wallet.
//RETURNS : True if walletPtr->topIndex >= walletPtr->capacity - 1 else it returns false.
//
bool isWalletFull(wallet* walletPtr) {
	return walletPtr->topIndex >= walletPtr->capacity - 1;
}
//
//FUNCTION : printWallet
//DESCRIPTION : This function itterates through the wallet and prints each transaction.
//PARAMETERS : 	takes a struct pointer to the wallet.
//RETURNS : Does not have a return value
//
void printWallet(wallet* walletPtr) {
	//checks if wallet is empty or NULL
	if (walletPtr == NULL || isWalletEmpty(walletPtr)) {
		printf("Wallet is empty.\n");
		return;
	}
	printf("Transactions\n");
	for (int i = 0; i <= walletPtr->topIndex; i++) {
		//ternary operator used to determine whether processed or refunded are true or false
		const char* processed = walletPtr->transactions[i].processed ? "Yes" : "No";
		const char* refunded = walletPtr->transactions[i].refunded ? "Yes" : "No";
		printf("Transaction %c: $%.2lf, Processed: %s, Refunded: %s\n", (i + 1), walletPtr->transactions[i].transactionAmount, processed, refunded);
	}
}
//
//FUNCTION : freeWallet
//DESCRIPTION : This frees all allocated memory in the program
//PARAMETERS : 	takes a struct pointer to the wallet.
//RETURNS : Does not return any value.
//
void freeWallet(wallet* walletPtr) {
    if (walletPtr) {
		//frees the transactions first
        free(walletPtr->transactions);
		//frees the wallet second
        free(walletPtr);
    }
}