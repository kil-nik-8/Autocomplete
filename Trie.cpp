#include "Trie.h"
#include <iostream>

using namespace std;

// ��������� ����� ���� � ������� ������
TrieNode* getNewNode(void)
{
    // �������� ������ �� ����� ����
    struct TrieNode* pNode = new TrieNode;

    // ������������� ���� ����� ����� � false
    pNode->isEndOfWord = false;
    pNode->freq = 0;
    // �������������� ����� ������� ���������
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;

    return pNode;
}

// ��������� ���� � ������, ���� ��� ���, 
// ����� ���� ���� ������� �������� ���� ������ 
// �������� ��������� �������� �.�. ����� �����
void insert(TrieNode* root, string key)
{
    TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        // ��������� ������ � ������ ����� �������� ������������ ������ �����
        int index = key[i] - 'a';

        // ���� ��������� �������, �.�. ����� � ����� ��������� ���
        // ������� ����� ����
        if (!node->children[index])
            node->children[index] = getNewNode();


        node = node->children[index];
        node->freq++;
    }

    // �������� ��������� ����� ��� ����, �.�. ����� �����
    node->isEndOfWord = true;
}

// ���������� true ���� ���� ���� � ������, ����� false 
bool search(struct TrieNode* root, string key)
{
    struct TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!node->children[index])
            return false;

        node = node->children[index];
    }

    return (node != nullptr && node->isEndOfWord);
}

string searchSequence(struct TrieNode* root, string key)
{
    if (search(root, key))
        return "";

    struct TrieNode* node = root;
    int k = 0, i = 0;
    srand(time(NULL));
    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!node->children[index])
            return "";

        node = node->children[index];
    }

    do
    {
        k = (rand() + 1) % getChildAmount(node);
        i = -1;
        while (k >= 0)
        {
            i++;
            if (node->children[i])
                k--;
        }
        node = node->children[i];
        key += i + 'a';
    } while (!node->isEndOfWord);

    return key;
}

int getChildAmount(TrieNode* root)
{
    int k = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            k++;
    return k;
}

// ���������� true ���� root ����� ����, ����� false 
bool isEmpty(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

// ����������� ������� �������� ����� �� ������ 
TrieNode* remove(TrieNode* root, string key, int depth)
{
    // ���� ������ ������ 
    if (!root)
        return nullptr;

    // ���� ����� �� ����� ����� 
    if (depth == key.size()) {

        // ���� ���� ������ �� ����� ����� 
        if (root->isEndOfWord)
            root->isEndOfWord = false;

        // ���� ���� �� �������� ���������, ������� ���
        if (isEmpty(root)) {
            delete (root);
            root = nullptr;
        }

        return root;
    }

    // ���� �� ����� �� ����� �����, ���������� �������� ��� ������� 
    // ���������������� ������� 
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);

    // ���� � ����� ��� ��������� ����� 
    // (������ ������ ���� ��� �������� �������), 
    // � �� �� ������������� ������ ������. 
    if (isEmpty(root) && root->isEndOfWord == false) {
        delete (root);
        root = nullptr;
    }

    // ���������� ����� ������
    return root;
}

// �� ���������� ��������� �������
void findMinPrefixes(TrieNode* root, char buf[], int ind, string& res)
{
    // ��� ���
    if (!root)
        return;

    if (root->freq == 1)
    {
        buf[ind] = '\0';
        if (res.length() == 0)
            res += (string)buf;
        else
            res += ' ' + (string)buf;
        return;
    }

    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        if (root->children[i])
        {
            buf[ind] = i + 'a';
            findMinPrefixes(root->children[i], buf, ind + 1, res);
        }
    }
}