#include "Assignment3.h"
#include <stdlib.h>



int main() {
	//intialize wallet
    wallet* walletPtr = initializeWallet();
    if (walletPtr) {
        printf("Wallet initialized successfully.\n");  
    }
	
	//addTransaction(walletPtr);
	//printWallet(walletPtr);
	//applyTransactionFees(walletPtr);
	//findHighestTransaction(walletPtr);
	//swapTransactions(walletPtr);
	//printWallet(walletPtr);
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
//FUNCTION : applyTransactionFees
//DESCRIPTION : This function takes user input for a percentage fee and applies it to the transactions in the wallet.
//				It then prints the new transaction amounts to the screen.
//PARAMETERS : 	takes a struct pointer to the wallet.
//RETURNS : Does not have a return value
//
void applyTransactionFees(wallet* walletPtr) {
	if (walletPtr == NULL || isWalletEmpty(walletPtr)) {
		printf("Wallet is empty.\n");
		return;
	}
	int convertToDecimal = 100;
	double percentageFee = 0;
	printf("Enter fee percentage: ");
	scanf_s("%lf", &percentageFee);
	while (getchar() != '\n');
	//converts to decimal
	percentageFee = percentageFee / convertToDecimal;
	for (int i = 0; i <= walletPtr->topIndex; i++) {
		//calculates the amount to be subtracted
		double feeAmount = walletPtr->transactions[i].transactionAmount * percentageFee;
		//subtracts the fee from the transactionAmount
		walletPtr->transactions[i].transactionAmount = walletPtr->transactions[i].transactionAmount - feeAmount;
	}
	printf("New Transaction amounts based on %.2lf%% rate\n", percentageFee);
	printWallet(walletPtr);
}
//
//FUNCTION : findHighestTransaction
//DESCRIPTION : This function stores the value of the first transaction in the wallet than iterates through the wallet comparing
//				if the value is less. If it is less it swaps the value into the temporary walletSlot. The highest value gets printed at
//				the end.
//PARAMETERS : 	takes a struct pointer to the wallet.
//RETURNS : Does not return any value.
//
void findHighestTransaction(wallet* walletPtr) {
	if (walletPtr == NULL || isWalletEmpty(walletPtr)) {
		printf("Wallet is empty.\n");
		return;
	}
	walletSlot highestAmount = walletPtr->transactions[0];
	for (int i = 0; i <= walletPtr->topIndex; i++) {
		
		if (walletPtr->transactions[i].transactionAmount > highestAmount.transactionAmount) {
			highestAmount = walletPtr->transactions[i];
		}
	}
	printf("Highest transaction amount: $%.2lf\n", highestAmount.transactionAmount);
}
//
//FUNCTION : swapTransactions
//DESCRIPTION : This function takes user input for two wallet indicies and performs a index swap using a basic swap technique
//				with a temporary variable.
//PARAMETERS : 	takes a struct pointer to the wallet.
//RETURNS : Does not return any value.
//
void swapTransactions(wallet* walletPtr) {
	if (walletPtr == NULL || isWalletEmpty(walletPtr)) {
		printf("Wallet is empty.\n");
		return;
	}
	int index1 = 0;
	int index2 = 0;

	printf("Enter two indices to swap (1 to %d): ", walletPtr->topIndex + 1);

	// Get first valid index
	while (scanf_s("%d", &index1) != 1 || index1 < 1 || index1 > walletPtr->topIndex + 1) {
		printf("Invalid index. Enter index between 1 and %d: ", walletPtr->topIndex + 1);
		//clear buffer if input is wrong
		while (getchar() != '\n');
	}
	// clear buffer when it exits loop
	while (getchar() != '\n'); 

	while (scanf_s("%d", &index2) != 1 || index2 < 1 || index2 > walletPtr->topIndex + 1) {
		printf("Invalid index. Enter index between 1 and %d: ", walletPtr->topIndex + 1);
		while (getchar() != '\n');
	}
	while (getchar() != '\n');
	//decrement to array index associated with input
	index1--;
	index2--;
	
	walletSlot temp = walletPtr->transactions[index1];
	walletPtr->transactions[index1] = walletPtr->transactions[index2];
	walletPtr->transactions[index2] = temp;

	printf("Transactions at indices %d and %d swapped successfully.\n", index1 + 1, index2 + 1);
}
//
//FUNCTION : manageFlags
//DESCRIPTION : This function takes prompts a sub menu to manage different flags in the wallet to set processed, 
//				clear processed and toggle refunded
//PARAMETERS : 	takes a struct pointer to the wallet.
//RETURNS : Does not return any value.
//
void manageFlags(wallet* walletPtr) {
	if (walletPtr == NULL || isWalletEmpty(walletPtr)) {
		printf("Wallet is empty.\n");
		return;
	}
	printf("Enter transaction index: ");
	int index = 0;
	while (scanf_s("%d", &index) != 1 || index < 1 || index > walletPtr->topIndex + 1) {
		printf("Invalid index. Enter index between 1 and %d: ", walletPtr->topIndex + 1);
		while (getchar() != '\n');
	}
	while (getchar() != '\n');
	printf("1. Set Processed\n");
	printf("1. Clear Processed\n");
	printf("1. Toggle Refund\n");
	int menu = 0;
	while (scanf_s("%d", &index) != 1) {
		printf("Invalid Input. Select a number.\n");
	}
	switch (menu)
	{
	case 1:
		//setprocessed
		break;
	case 2:
		//clear processed
		break;
	case 3:
		//toggle refund
		break;
	default:
		printf("invalid option.\n");
		break;
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