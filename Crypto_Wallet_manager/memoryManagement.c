#include "Assignment3.h"

int* intializeWallet() {
	//creates a pointer to the allocated memory
	transaction* wallet = (int*)malloc(sizeof(transaction));
	if (wallet == NULL) {
		fprintf(stderr, "Memory allocation failed.\n");
		return 1;
	}
	wallet = (int*)malloc(MAX_WALLET_SIZE * (sizeof(transaction)));
	if (wallet == NULL) {
		fprintf(stderr, "Memory allocation failed.\n");
		return 1;
	}
	return wallet;
}