#include<iostream>
#include<string>
#include<stdlib.h>
#include<vector>
#include<fstream>
#include<conio.h>
#include <Windows.h>
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
private:
	TrieNode* root;
	TrieNode* removeUtil(TrieNode*, string, int);
	vector<string> parseCorpusLine(string line);
	string foundMsg(string word, int count) {
		return "\n\tThe word \"" + word + "\" was found with the count of \"" + to_string(count) + "\"";
	}
	string notFoundMsg(string word) {
		return "\n\tThe word \"" + word + "\" was not found";
	}
	string similarWordsMsg(vector<string> similarWords) {
		string msg = "";
		msg += "\n\tDid you mean? ";
		for (int i = 0; i < similarWords.size() && i < 10; i++)
		{
			msg += (similarWords[i]+" ");
			if (i == similarWords.size() - 1 || i == 9) msg += " or ";
		}
		return msg;
	}

public:
	int freq;
	bool found;
	Dictionary();
	void addFromTextFile(string file_path);
	bool isEmpty(TrieNode*);
	TrieNode* clearDictionary(TrieNode*);
	void remove(string);
	void insert(string, int);
	int getCharIndex(char i);
	void search(string);
	void autoComplete(TrieNode*, string, vector<string>&);
	~Dictionary();
};
