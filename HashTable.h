#pragma once
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

typedef struct movie {
	string language;
	string title;
	string releaseDate;
	string revenue;
	float runtime;
	int number;
} Movie;

class HashTable {
public:
	HashTable(const int _size) {
		size = _size;
		table = new Movie[size];
		for (int i = 0; i < size; i++)
		{
			table[i].title = "empty";
		}
	}
	Movie* FindKey(Movie key);
	int HashFunction(Movie* key);
	bool InsertKey(Movie key);
	bool DeleteKey(Movie key);
	int tableSize() const {
		return size;
	}
	int keyCount();
	void clear();

	float avgAccessSuccess();
	float avgAccessUnsuccess();
	float avgAccessUnsuccessEst();
	void resetStatistics() 
	{
		succesTry = 0;
		succes = 0;
		unsuccesTry = 0;
		unsucces = 0;
	}

	friend ostream& operator<<(ostream& os, const HashTable ht) {
		for (int i = 0; i < ht.size; i++)
		{
			os << i + 1 << ". " << ht.table[i].title << endl;
			//os << i + 1 << ". " << ht.table->language << ", " << ht.table->title << ", " << ht.table->releaseDate << ", " << ht.table->revenue << ", " << ht.table->runtime << endl;
		}
		return os;
	}

private:
	int size;
	Movie *table;
	int succesTry = 0;
	int succes = 0;
	int unsuccesTry = 0;
	int unsucces = 0;
};