// project test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <string>
#include "Trie.h"
#include <time.h>

using namespace std;
int main()
{
	Dictionary obj;
	obj.addFromTextFile("wifeys.txt");
	string word, name1, name2;
	int n, freq1 = 0, freq2 = 0, score1 = 0, score2 = 0, numberOfRounds = 0;
	char c = 'y';
	srand(time(NULL));
	int random = rand() % 26 + 65;
	char randomL = static_cast<char>(random);
	
	cout << "\n\tPLAYER 1, ENTER YOUR NAME: ";
	cin >> name1;
	cout << "\n\tPLAYER 2, ENTER YOUR NAME: ";
	cin >> name2;

	do
	{
		system("cls");
		freq1 = 0, freq2 = 0;
		numberOfRounds++;
		cout << "\n\tROUND " << numberOfRounds;
		cout << "\n\tPLAYER 1, ENTER A WORD: ";
		cin >> word;
		obj.search(word);
		if (obj.found)
		{
			freq1 = obj.freq;
		}
		cout << "\n\tPLAYER 2, ENTER A WORD: ";
		cin >> word;
		obj.search(word);
		if (obj.found)
		{
			freq2 = obj.freq;
		}
		if (freq1 > freq2)
		{
			score1++;
			cout << "\n\t" << name1 << " ENTERED A WORD WITH HIGHER FREQUENCY";
			cout << "\n\tSCORES: ";
			cout << "\n\PLAYER 1: " << score1;
			cout << "\n\PLAYER 2: " << score2;
		}
		if (freq2 > freq1)
		{
			score2++;
			cout << "\n\t" << name2 << " ENTERED A WORD WITH HIGHER FREQUENCY";
			cout << "\n\tSCORES: ";
			cout << "\n\tPLAYER 1: " << score1;
			cout << "\n\tPLAYER 2: " << score2;
		}
		if (freq2 == freq1)
		{
			cout << "\n\tIT IS A TIE";
		}
		cout << "\n\n\twant to continue (enter 'y' or 'Y') ";
		cin >> c;
	} while (c == 'y' || c == 'Y');
	exit(0);
}
	//Dictionary obj;
	//string word;
	//char c = 'y';
	//int freqUser, freqComp, userScore = 0, compScore = 0;
	//obj.addFromTextFile("wifeys.txt");
	//obj.addToComp("Trial.txt");
	//obj.randomLetter();
	//do
	//{
	//	system("cls");
	//	cout << "\n\tENTER A WORD THAT STARTS WITH "<<obj.getRandomL()<< ": ";
	//	cin >> word;
	//	if (word[0] != obj.getRandomL() || word[0] != toupper(obj.getRandomL()))
	//	{
	//		cout << "\n\tDISQUALIFIED\n";
	//		exit(0);
	//	}
	//	obj.search(word);
	//	if (obj.found)
	//	{
	//		freqUser = obj.freq;
	//		obj.randomWord(obj.getRandomL());
	//		obj.search(obj.wordbycomp);
	//		freqComp = obj.freq;
	//		if (freqComp > freqUser)
	//		{
	//			cout << "\n\tTHE COMPUTER HAS WON\n";
	//			compScore++;
	//		}
	//		else if (freqComp == freqUser)
	//		{
	//			cout << "\n\tIT IS A TIE\n";
	//		}
	//		else
	//		{
	//			cout << "\n\tCONGRATS YOU HAVE WON\n";
	//			userScore++;
	//		}
	//	}
	//	cout << "\n\n\twant to continue (enter 'y' or 'Y') ";
	//	cin >> c;
	//} while (c == 'y' || c == 'Y');
	//
	//exit(0);



