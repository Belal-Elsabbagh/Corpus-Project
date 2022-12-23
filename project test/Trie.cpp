#include"Trie.h"
#include <Windows.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>
using namespace std;
Dictionary::Dictionary()
{
	root = new TrieNode();
	
}
void Dictionary::addFromTextFile()
{
	int repitions;
	int count;
	string word;
	ifstream fin;
	fin.open("Trial.txt");
	string line;
	while (getline(fin, line))
	{
		istringstream iss(line);
		vector<string> values;
		string val;
		while (getline(iss, val, '\t'))
		{
			values.push_back(val);
		}
		count = stoi(values[0]);
		word = values[1];
		repitions = stoi(values[2]);
		insert(word, repitions);
		cout << count << ", " << word << ", " << repitions << endl;
	}
	cout << "imported from file...\n";

	fin.close();
}
TrieNode::TrieNode() :count(0)
{
	for (int i = 0; i < ALPHABETS; i++)
		children[i] = NULL;

}
void Dictionary::insert(string word, int count)
{
	int i, index;
	TrieNode* nodePtr = this->root;
	for (i = 0; i < word.length(); i++)
	{
		index = word[i] - 'a';
		if (nodePtr->children[index] == NULL) {
			nodePtr->children[index] = new TrieNode();
			nodePtr = nodePtr->children[index];
			continue;
		}
		nodePtr = nodePtr->children[index];
	}
	nodePtr->count = count;

}
void Dictionary::autoComplete(TrieNode* root, string word, vector< string>& similarWords)
{
	/*
	objective: autosuggest words which are close to the entered word which isn't found in the dictionary

	input parameters: none

	output value: none

	approach: a susbtring of the unfound word is received as a parameter to the function by the search
			  function and that substring is successively permuted with the 26 alphabets to check whether
			  any word exists corresponding to that alphabet and appended to the word and printed as a
			  suggestion to the user
	*/
	TrieNode* temp = root;
	if (root->count > 0)
	{
		similarWords.push_back(word);
	}
	for (int i = 0; i < ALPHABETS; i++)
	{
		if (temp->children[i])
			autoComplete(temp->children[i], word + (char)(i + 'a'), similarWords);
	}
}
void Dictionary::search(string word)
{
	/*
	objective: gives the meaning of the word entered, and if the entered word is not present in the
			   dictionary the application will say that the word is not found

	input parameters: word to be searched

	output value: none

	approach: the input word is send as a parameter to the search function which displays the word with its
			  meaning (when found)
	*/
	int i, index;
	TrieNode* temp = root;
	vector <string> similarWords;
	for (i = 0; i < word.length(); i++)
	{
		index = word[i] - 'a';
		if (temp->children[index] == NULL)
		{
			autoComplete(temp, word.substr(0, i), similarWords);
			break;
		}
		temp = temp->children[index];
	}
	if (temp->count == 0)
		autoComplete(temp, word, similarWords);

	if (temp->count > 0)
		cout << "\n\tThe word \"" << word << "\" was found with the count of \"" << temp->count << "\"";
	else
	{
		cout << "\n\tThe word \"" << word << "\" was not found";
		if (similarWords.size() == 0)
			return;
		cout << "\n\tDid you mean? ";
		for (i = 0; i < similarWords.size() && i < 10; i++)
		{
			cout << similarWords[i];
			if (i == similarWords.size() - 1 || i == 9) cout << " or ";
		}
	}

}
bool Dictionary::isEmpty(TrieNode* temp)
{
	int i;
	for (i = 0; i < ALPHABETS; i++)
		if (temp->children[i])
			return 0;
	return 1;
}
TrieNode* Dictionary::removeUtil(TrieNode* temp, string word, int depth = 0)
{
	if (depth == word.size())
	{
		temp->count = 0;
		if (isEmpty(temp))
		{
			delete(temp);
			temp = NULL;
		}
		return temp;

	}
	int index = word[depth] - 'a';
	temp->children[index] = removeUtil(temp->children[index], word, depth + 1);
	if (isEmpty(temp) && temp->count == 0)
	{
		delete temp;
		temp = NULL;
	}
	return temp;
}

void Dictionary::remove(string word)
{
	removeUtil(root, word);
	cout << "\n\tThe word \"" << word << " has been successfully removed. ";

}

TrieNode* Dictionary::clearDictionary(TrieNode* temp)
{
	for (int i = 0; i < ALPHABETS; i++)
	{
		if (temp->children[i])
			temp->children[i] = clearDictionary(temp->children[i]);
	}
	delete temp;
	temp = NULL;
	return temp;
}
Dictionary ::~Dictionary()
{
	clearDictionary(root);
}

