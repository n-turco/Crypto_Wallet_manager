#include "Assignment3.h"
#include "memoryManagement.h"



int main() {
	walletSlot* transaction = intializeWallet();
	freeAllocatedMemory(transaction);
	return 0;
}

//
//FUNCTION : IsWalletEmpty
//DESCRIPTION : This function checks if the wallet is empty.
//PARAMETERS : 	takes a struct pointer to the wallet.
//RETURNS : True if transaction == -1 else it returns false.
//
bool isWalletEmpty(walletSlot* transaction) {
	return transaction == -1;
}
//
//FUNCTION : IsWalletFull
//DESCRIPTION : This function checks if the stack is empty
//PARAMETERS : 	takes a struct pointer to the wallet.
//RETURNS : True if wallet == MAX_WALLET_SIZE - 1 else it returns false.
//
bool isWalletFull(walletSlot* transaction) {
	return transaction == MAX_WALLET_SIZE - 1;
}