#include "Address.h"

int HashTable::HashFunction(Movie* key) {
	for (int i = 0; i < key->title.length(); i++)
	{
		if (i % 2 == 1)
			key->number += key->title.at(i) * 10;
		else
			key->number += key->title.at(i);
	}
	int numOfnum = 1;
	int toMod = 10;
	while (key->number > toMod)
	{
		numOfnum++;
		toMod *= 10;
	}

	int num = numOfnum % 4;
	int index = 0;
	toMod = 1;
	for (int i = 0; i < num; i++)
		toMod *= 10;
	index += key->number % toMod;
	int helpNum = key->number / toMod;

	while (helpNum > 0)
	{
		num = 4;
		for (int i = 0; i < num; i++)
			toMod *= 10;
		index += key->number % toMod;
		helpNum = key->number / toMod;
	}

	return index % size;
}

Movie* HashTable::FindKey(Movie key) {
	int attempt = 1;
	int index = HashTable::HashFunction(&key);
	Address address(3, 5);

	while (table[index].title != key.title && attempt <= size)
	{
		index = address.getAddress(key.number, index, attempt, size);
		attempt++;
	}

	if (table[index].title == key.title)
	{
		succesTry = succesTry + 1 + attempt;
		succes++;
		return &(table[index]);
	}
	else
	{
		unsuccesTry = unsuccesTry + 1 + attempt;
		unsucces++;
		return nullptr;
	}
}

bool HashTable::InsertKey(Movie key) {
	int attempt = 1;
	Movie* exists = FindKey(key);

	if (keyCount() < size)
	{
		if (exists == nullptr)
		{
			int index = HashTable::HashFunction(&key);
				if (table[index].title == "empty" || table[index].title == "deleted")
				{
					table[index] = key;
				}
				else
				{
					Address address(3, 5);
						while (table[index].title != "empty" && table[index].title != "deleted")
						{
							index = address.getAddress(key.number, index, attempt, size);
							attempt++;
						}
					table[index] = key;	
				}
				cout << "Movie succesfully added." << endl;
				return true;
		}
		else
		{
			cout << "Movie already exists." << endl;
			return false;
		}
	}
	else
	{
		cout << "Hash table is full." << endl;
		return false;
	}
}

bool HashTable::DeleteKey(Movie key) {
	Movie* deleteIt = FindKey(key);

	if (deleteIt != nullptr)
	{
		deleteIt->title = "deleted";
		cout << "Movie succesfully deleted." << endl;
		return true;
	}
	else
	{
		cout << "Movie doesn't exist." << endl;
		return false;
	}
}

int HashTable::keyCount() {
	int keyCount = 0;
	for (int i = 0; i < size; i++)
	{
		if (table[i].title != "empty" && table[i].title != "deleted")
		{
			keyCount++;
		}
	}
	return keyCount;
}

void HashTable::clear() {
	for (int i = 0; i < size; i++)
	{
		if (table[i].title != "empty" && table[i].title != "deleted")
		{
			table[i].title = "deleted";
		}
	}
	cout << "All movies are deleted." << endl;
}

float HashTable::avgAccessSuccess()
{
	if (succes > 0)
		return (succesTry / succes);
	else
	{
		cout << "Nije bilo pokusaja." << endl;
		return 0;
	}
}

float HashTable::avgAccessUnsuccess()
{
	if (unsucces > 0)
		return (unsuccesTry / unsucces);
	else
	{
		cout << "Nije bilo pokusaja." << endl;
		return 0;
	}
}

float HashTable::avgAccessUnsuccessEst() 
{
	int n = keyCount() + 1;
	float avg = 0;
	int i = 1;
	float freeElem = size - keyCount();

	while (i <= n)
	{
		//izracunaj verovatnocu
		float p = 1;
		int num = 1;
		float numOfElem = keyCount();
		float newSize = size;
		while (num < i)
		{
			p *= (numOfElem / newSize);

			numOfElem--;
			newSize--;
			num++;
		}
		p *= (freeElem / newSize);

		//povecaj broj
		avg += i * p;
		i++;
	}
	return avg;
}