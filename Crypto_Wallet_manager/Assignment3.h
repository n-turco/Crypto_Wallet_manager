#pragma once
#ifndef ASSIGNMENT3_H
#define ASSIGNMENT3_H
#include <stdio.h>
#include <stdbool.h>
#define MAX_WALLET_SIZE 50
typedef struct {
	int dollarAmount;
	bool processed;
	bool refunded;
}transaction;
#endif 

