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
	freq = 0;
    found = false; 
}
void Dictionary::addFromTextFile(string file_path)
{
	ifstream fin;
	fin.open(file_path);
	string line;
	cout << "importing from file...\n";
	while (getline(fin, line))
	{
		int repititions, count;
		string word;
		if (line == "") continue;
		vector<string> values = this->parseCorpusLine(line);
		count = stoi(values[0]);
		word = values[1];
		repititions = stoi(values[2]);
		insert(word, repititions);
		/*cout << count << ", " << word << ", " << repititions << endl;*/
	}
	cout << "imported from file...\n";
	fin.close();
}
TrieNode::TrieNode() :count(0)
{
	for (int i = 0; i < 128; i++)
		children[i] = NULL;
}
void Dictionary::insert(string word, int count)
{
	int i, index;
	TrieNode* nodePtr = this->root;
	for (char i : word)
	{
		index = getCharIndex(i);
		if (nodePtr->children[index] == NULL) {
			nodePtr->children[index] = new TrieNode();
		}
		nodePtr = nodePtr->children[index];
	}
	nodePtr->count = count;
}
int Dictionary::getCharIndex(char i)
{
	return static_cast<int>(i);
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
	for (auto& i : temp->children)
	{
		int code = i.first;
		TrieNode* child = i.second;
		if (child != NULL) autoComplete(child, word + (char)(code), similarWords);
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
	int i = 0;
	TrieNode* temp = root;
	vector <string> similarWords;
	for (int i = 0; i < word.length(); i++)
	{
		int index = static_cast<int>(word[i]);
		if (temp->children[index] == NULL)
		{
			autoComplete(temp, word.substr(0, i), similarWords);
			break;
		}
		temp = temp->children[index];
	}
	if (temp->count == 0) autoComplete(temp, word, similarWords);

	if (temp->count > 0)
	{
		freq = temp->count;
		found = true;
		cout << this->foundMsg(word, temp->count);
		return;
	}
	cout << this->notFoundMsg(word);
	if (similarWords.size() == 0)
		return;
	cout << this->similarWordsMsg(similarWords);
}
bool Dictionary::isEmpty(TrieNode* temp)
{
	for (auto& i : temp->children)
		if (i.second) return 0;
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
	int index = static_cast<int>(word[depth]);
	temp->children[index] = removeUtil(temp->children[index], word, depth + 1);
	if (isEmpty(temp) && temp->count == 0)
	{
		delete temp;
		temp = NULL;
	}
	return temp;
}

vector<string> Dictionary::parseCorpusLine(string line)
{
	istringstream iss(line);
	vector<string> values;
	string val;
	while (getline(iss, val, '\t'))
	{
		values.push_back(val);
	}
	return values;
}

void Dictionary::remove(string word)
{
	removeUtil(root, word);
	cout << "\n\tThe word \"" << word << " has been successfully removed. ";

}

TrieNode* Dictionary::clearDictionary(TrieNode* temp)
{
	for (auto& i : temp->children)
	{
		if (i.second) i.second = clearDictionary(i.second);
	}
	delete temp;
	temp = NULL;
	return temp;
}
Dictionary ::~Dictionary()
{
	clearDictionary(root);
}