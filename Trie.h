#pragma once
#include <string>
using namespace std;

const int ALPHABET_SIZE = 26;

// Структура узела дерева 
struct TrieNode
{
    struct TrieNode* children[ALPHABET_SIZE];
    // isEndOfWord - true, если ключ является концом слова
    bool isEndOfWord;
    int freq;
};

TrieNode* getNewNode(void);
void insert(TrieNode*, string);
bool search(TrieNode*, string);
string searchSequence(TrieNode*, string);
int getChildAmount(TrieNode*);
bool isEmpty(TrieNode*);
TrieNode* remove(TrieNode*, string, int depth = 0);
void findMinPrefixes(TrieNode*, char[], int, string&);
