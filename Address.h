#pragma once
#include "HashTable.h"

class Address {
public:
	Address(int _p, int _q) : p(_p), q(_q) {}
	int getAddress(int key, int address, int attempt, int size) {
		return ((address + attempt * (q + (key % p))) % size);
	}
private:
	int p;
	int q;
};