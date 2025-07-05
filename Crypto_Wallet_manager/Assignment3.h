#pragma once
#ifndef ASSIGNMENT3_H
#define ASSIGNMENT3_H
#include <stdio.h>
#include <stdbool.h>

#define MAX_WALLET_SIZE 100

typedef struct {
	double dollarAmount;
	bool processed;
	bool refunded;
	int topIndex;
}walletSlot;

bool isWalletEmpty(walletSlot* transaction);
bool isWalletFull(walletSlot* transaction);

#endif 

