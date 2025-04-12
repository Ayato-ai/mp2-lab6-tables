#include <iostream>
#include "tables.h"
using namespace std;

maps::UnorderedTable<string> table_un;
maps::OrderedTable<string> table_or;
maps::HashTable<string> table_h;

int main() {

	setlocale(2, "rus");

	
	size_t k = 0;
	cout << "1) Создать неупорядоченную таблицу" << endl << "2) Создать упорядоченную таблицу" << endl << "3) Создать хэш-таблицу" << endl;
	cin >> k;
	
	cout << "Добавить элементы таблицы" << endl;
	bool index = true;
	while (index) {
		size_t key;
		string str;

		cin >> key;
		cin >> str;

		switch (k) {
		case 1:
			table_un.insert(key, str);
			break;
		case 2:
			table_or.insert(key, str);
			break;
		case 3:
			table_h.insert(key, str);
			break;
		}
		if (key == 0)
			index = false;

	}

	switch (k) {
	case 1:
		cout << table_un << endl;
	case 2:
		cout << table_or << endl;
	case 3:
		cout << table_h << endl;
	}
	cout << "Печать таблицы окончена" << endl;
	
}
