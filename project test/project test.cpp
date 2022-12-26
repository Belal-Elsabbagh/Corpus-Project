// project test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include "Trie.h"
using namespace std;
int main()
{
	Dictionary obj;
	string word;
	int ch;
	char c = 'y';
	obj.addFromTextFile("wifeys.txt");
	do
	{
		system("cls");
		cout << "\n\t1.Search Word";
		cout << "\n\t2.Remove Word";
		cout << "\n\tEnter your choice: ";
		cin >> ch;
		cout << "\n\tENTER WORD: ";
		cin >> word;

		switch (ch)
		{
		case 1:obj.search(word);
			break;
		case 2:obj.remove(word);
			break;
		}
		cout << "\n\n\twant to continue (enter 'y' or 'Y') ";
		cin >> c;
	} while (c == 'y' || c == 'Y');
	return 0;

}

