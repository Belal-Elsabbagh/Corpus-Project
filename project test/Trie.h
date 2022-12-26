#include<iostream>
#include<string>
#include<stdlib.h>
#include<vector>
#include<fstream>
#include<conio.h>
#include <Windows.h>
#include <array>
#include <map>
#define ALPHABETS 26
using namespace std;
class TrieNode
{
	int count;
	std::map<int, TrieNode*> children;
	friend class Dictionary;
public:
	TrieNode();
};

class Dictionary
{
	TrieNode* root;

public:
	Dictionary();
	void addFromTextFile(string file_path);
	bool isEmpty(TrieNode*);
	TrieNode* removeUtil(TrieNode*, string, int);
	TrieNode* clearDictionary(TrieNode*);
	void remove(string);
	void insert(string, int);
	void search(string);
	void autoComplete(TrieNode*, string, vector<string>&);
	~Dictionary();
};

//int main()
//{
//	/*
//	objective: to implement a dictionary which gives the meaning of the word entered, and if the entered word
//			   is not present in the dictionary the application will say that the word is not found, and then
//			   will autosuggest words which are close to the entered word
//
//	input parameters:
//			   word: the word whose meaning the user wants to find
//
//	output value: none
//
//	approach: the input word is send as a parameter to the search function which displays the word with its
//			  meaning (when found)
//	*/
//	Dictionary obj;
//	string word, meaning;
//	ifstream fin;
//	int n, ch;
//	char c;
//	cout << "\n\tDICTIONARY";
//	cout << "\n\t1.EXTRACTING DATA FROM FILE";
//	cout << "\n\t2.PREDEFINED DATA";
//	cout << "\n\tEnter your choice: ";
//	cin >> ch;
//	switch (ch)
//	{
//	case 1:	fin.open("F:\Dell\Documents\Data Structure\Projects\Text Files\Corpus\eng_newscrawl-public_2018_10K-words.txt");
//		while (!fin.eof())
//		{
//			fin >> word;
//			fin >> meaning;
//			obj.insert(word, meaning);
//		}
//		fin.close();
//		break;
//	case 2:	string words[] = { "prodigious","potent","sway","corrosive","propaganda","drag","cart","card","carrot","carrom","carton" };
//		  string meanings[] = { "very large in size","very strong in chemical or medicinal way","control","having the ability to wear down or destroy","information","pass slowly and tediously","a strong open vehicle with two or four wheels, typically used for carrying loads and pulled by a horse","a piece of thick, stiff paper or thin pasteboard, in particular one used for writing or printing on","a tapering orange-coloured root eaten as a vegetable","any strike and rebound, as a ball striking a wall and glancing off","a box" };
//		  n = sizeof(words) / sizeof(words[0]);
//		  for (int i = 0; i < n; i++)
//			  obj.insert(words[i], meanings[i]);
//		  break;
//	}
//	cout << "\n\tAdding words to the dictionary...";
//	Sleep(3);
//	cout << "\n\tAll the words have been suceesfully added to the dictionary.";
//	do
//	{
//		system("cls");
//		cout << "\n\t1.Search Word";
//		cout << "\n\t2.Remove Word";
//		cout << "\n\tEnter your choice: ";
//		cin >> ch;
//		cout << "\n\tENTER WORD: ";
//		cin >> word;
//
//		switch (ch)
//		{
//		case 1:obj.search(word);
//			break;
//		case 2:obj.remove(word);
//			break;
//
//		}
//		cout << "\n\n\twant to continue (enter 'y' or 'Y') ";
//		cin >> c;
//	} while (c == 'y' || c == 'Y');
//	return 0;
//
//}