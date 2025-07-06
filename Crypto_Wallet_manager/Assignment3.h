#pragma once
#ifndef ASSIGNMENT3_H
#define ASSIGNMENT3_H

#include <stdio.h>
#include <stdbool.h>

#define WALLET_CAPACITY 30

typedef struct {
    double transactionAmount;
    bool processed;
    bool refunded;
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
bool isWalletEmpty(wallet* walletPtr);
bool isWalletFull(wallet* walletPtr);

#endif
