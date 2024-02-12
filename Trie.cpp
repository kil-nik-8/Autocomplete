#include "Trie.h"
#include <iostream>

using namespace std;

// Возвращет новый узел с пустыми детьми
TrieNode* getNewNode(void)
{
    // Выделяем память по новый узел
    struct TrieNode* pNode = new TrieNode;

    // устанавливаем флаг конца слова в false
    pNode->isEndOfWord = false;
    pNode->freq = 0;
    // инициализируем детей нулевым уазателем
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;

    return pNode;
}

// Вставляет ключ в дерево, если его нет, 
// иначе если ключ явлется префксом узла дерева 
// помечает вкачестве литового т.е. конец слова
void insert(TrieNode* root, string key)
{
    TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        // вычисляем индекс в алфите через смещение отнситьельно первой буквы
        int index = key[i] - 'a';

        // если указатель пустрой, т.е. детей с таким префиксом нет
        // создаем новый узел
        if (!node->children[index])
            node->children[index] = getNewNode();


        node = node->children[index];
        node->freq++;
    }

    // помечаем последний узлел как лист, т.е. конец слова
    node->isEndOfWord = true;
}

// Возврашает true если ключ есть в дереве, иначе false 
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

// Вохвращает true если root имеет лист, иначе false 
bool isEmpty(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

// Рекурсивная функция удаления ключа из дерева 
TrieNode* remove(TrieNode* root, string key, int depth)
{
    // Если дерево пустое 
    if (!root)
        return nullptr;

    // если дошли до конца ключа 
    if (depth == key.size()) {

        // Этот узел больше не конец слова 
        if (root->isEndOfWord)
            root->isEndOfWord = false;

        // Если ключ не евляется префиксом, удаляем его
        if (isEmpty(root)) {
            delete (root);
            root = nullptr;
        }

        return root;
    }

    // Если не дошли до конца ключа, рекурсивно вызываем для ребенка 
    // соответствующего символа 
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);

    // Если у корня нет дочернего слова 
    // (удален только один его дочерний элемент), 
    // и он не заканчивается другим словом. 
    if (isEmpty(root) && root->isEndOfWord == false) {
        delete (root);
        root = nullptr;
    }

    // возвращаем новый корень
    return root;
}

// не изменияйте сигнатуру функции
void findMinPrefixes(TrieNode* root, char buf[], int ind, string& res)
{
    // ваш код
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