#pragma once
#ifndef ASSIGNMENT3_H
#define ASSIGNMENT3_H

#include <stdio.h>
#include <stdbool.h>

#define WALLET_CAPACITY 30
#define PROCESSED_BIT (1 << 0)
#define REFUNDED_BIT (1 << 1)

typedef struct {
    double transactionAmount;
    //flags to hold status of processed and refunded
    unsigned char flags;
 
} walletSlot;

typedef struct {
    walletSlot* transactions;
    int topIndex;
    int capacity;
} wallet;

wallet* initializeWallet(void);
bool resizeWallet(wallet* walletPtr);
void freeWallet(wallet* walletPtr);
walletSlot newTransaction(double dollarAmount);
void addTransaction(wallet* walletPtr);
void pushToWallet(wallet* walletPtr, walletSlot transactionToAdd);
void printWallet(wallet* walletPtr);
void applyTransactionFees(wallet* walletPtr);
void findHighestTransaction(wallet* walletPtr);
void swapTransactions(wallet* walletPtr);
void manageFlags(wallet* walletPtr);
void setProcessed(walletSlot* slot);
void clearProcessed(walletSlot* slot);
void toggleRefunded(walletSlot* slot);
void totalAndAverage(wallet* walletPtr);
bool isWalletEmpty(wallet* walletPtr);
bool isWalletFull(wallet* walletPtr);

#endif
