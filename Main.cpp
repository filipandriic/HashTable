#include "HashTable.h"
#include <fstream>

Movie createMovie(ifstream* ulaz) {
	Movie key;

	string word = "";
	char c;
	*ulaz >> c;
	while (c != ',')
	{
		word += c;
		*ulaz >> c;
	}
	key.language = word;

	word = "";
	*ulaz >> c;
	if (c != '"')
	{
		while (c != ',')
		{
			word += c;
			*ulaz >> c;
		}
	}
	else
	{
		*ulaz >> c;
		while (c != '"')
		{
			word += c;
			*ulaz >> c;
		}
		*ulaz >> c;
	}
	key.title = word;

	word = "";
	*ulaz >> c;
	while (c != ',')
	{
		word += c;
		*ulaz >> c;
	}
	key.releaseDate = word;

	word = "";
	*ulaz >> c;
	while (c != ',')
	{
		word += c;
		*ulaz >> c;
	}
	key.revenue = word;

	*ulaz >> key.runtime;
	key.number = 0;

	return key;
}

int main()
{
	HashTable hashTable(5000);
	int choice;
	
	while (true)
	{
		cout << endl;
		cout << "\n-----MENU-----\n"
			"1. Insert elements.\n"
			"2. Find element.\n"
			"3. Write hash table.\n"
			"4. Hash table size.\n"
			"5. Number of keys.\n"
			"6. Delete key.\n"
			"7. Delete all keys.\n"
			"8. Search for a key.\n"
			"9. Access success.\n"
			"10. Access unsuccess.\n"
			"11. Access unsuccessEST.\n"
			"12. Reset statistics.\n"
			"0. Exit." << endl;

		cin >> choice;
		switch (choice)
		{
		case 0:
			{
				exit(0);
				break;
			}
		case 1:
			{
				ifstream ulaz;
				ulaz.open("tmdb_movies.txt");
				if (!ulaz.is_open())
					{
						cout << "File not opened." << endl;
						exit(0);
					}
				int i = 1;
				while (!ulaz.eof()) {
					Movie key = createMovie(&ulaz);
					cout << i << ". ";
					hashTable.InsertKey(key);
					i++;
				}
				break;
			}
		case 2:
			{
				ifstream ulaz;
				ulaz.open("movies_search_1.txt");
				if (!ulaz.is_open())
				{
					cout << "File not opened." << endl;
					exit(0);
				}
				int i = 1;
				while (!ulaz.eof())
				{
					Movie key;
					cout << i << ". ";
					getline(ulaz, key.title);
					key.number = 0;

					Movie* exists = hashTable.FindKey(key);
					if (exists == nullptr)
						cout << "Movie doesn't exist." << endl;
					else
						cout << "Movie exists." << endl;
					i++;
				}
				break;
			}
		case 3:
			{
			cout << hashTable;
			break;
			}
		case 4:
			{
				int size = hashTable.tableSize();
				cout << "Hash table size: " << size << endl;
				break;
			}
		case 5:
			{
				int keyCount = hashTable.keyCount();
				cout << "Number of keys: " << keyCount << endl;
				break;
			}
		case 6:
			{
				ifstream ulaz;
				ulaz.open("movies_delete.txt");
				if (!ulaz.is_open())
				{
					cout << "File not opened." << endl;
					exit(0);
				}
				int i = 1;
				while (!ulaz.eof())
				{
					Movie key;
					cout << i << ". ";
					getline(ulaz, key.title);
					key.number = 0;

					hashTable.DeleteKey(key);
					i++;
				}
				break;
			}
		case 7:
			{
				hashTable.clear();
				break;
			}
		case 8:
			{
				Movie key;
				cout << "Which one? ";
				cin >> key.title;
				key.number = 0;
				Movie* exists = hashTable.FindKey(key);
				if (exists == nullptr)
					cout << "Movie doesn't exist." << endl;
				else
					cout << "Movie exists." << endl;
				break;
			}
		case 9:
			{
				cout << "Access success: " << hashTable.avgAccessSuccess() << endl;
				break;
			}
		case 10:
			{
				cout << "Access unsuccess: " << hashTable.avgAccessUnsuccess() << endl;
				break;
			}
		case 11:
			{
				cout << "Access unsuccessEST: " << hashTable.avgAccessUnsuccessEst() << endl;
				break;
			}
		case 12:
			{
				hashTable.resetStatistics();
				cout << "Statistics reseted." << endl;
				break;
			}
		}
	}
}