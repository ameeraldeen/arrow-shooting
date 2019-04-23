#include <iostream>
#include <string>
#include <locale>
#include "Point.h"

using namespace std;

class Trie
{

public:
    const static int ALPHA_SIZE = 26;

    struct Node
    {
        struct Point *pos;
        struct Node *children[ALPHA_SIZE];
        char value;
        bool isEndOfWord;
    };

    struct Node *getNode()
    {
        struct Node *pNode = new Node;

        pNode->isEndOfWord = false;

        for (int i = 0; i < ALPHA_SIZE; i++)
            pNode->children[i] = nullptr;

        return pNode;
    };

    void insert(struct Node *root, string key)
    {
        struct Node *walker = root;

        this->normalizeToLower(key);

        for (int i = 0; i < key.length(); i++)
        {
            int index = key[i] - 'a';
            if (!walker->children[index])
                walker->children[index] = getNode();
            walker = walker->children[index];
        }
        walker->isEndOfWord = true;
    }

    bool search(struct Node *root, string key)
    {
        struct Node *walker = root;

        this->normalizeToLower(key);

        for (int i = 0; i < key.length(); i++)
        {
            int index = key[i] - 'a';
            if (!walker->children[index])
                return false;

            walker = walker->children[index];
        }

        return (walker != NULL && walker->isEndOfWord);
    }

    int computeDistance(struct Node a, struct Node b)
    {
        return (int)sqrt(pow(abs(a.pos->x - b.pos->x), 2) + pow(abs(a.pos->y - b.pos->y), 2));
    }

private:
    void normalizeToLower(string &key)
    {
        for (char &c : key)
        {
            if (!isalpha(c))
            {
                cerr << "Alphabetic characters allowed only!";
                exit(0);
            }
            c = tolower(c);
        }
    }
};