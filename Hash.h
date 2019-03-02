//
// Created by Osaid K on 11/24/18.
//

#ifndef PLAGIARISMCATCHER_HASH_H
#define PLAGIARISMCATCHER_HASH_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

class HashTable{
private:
    static const int TableSize=14557 ;

    struct words{
        int filenumber;
        words* next;
    };

    words* HashT[TableSize];

public:
    HashTable();
    unsigned int Hash (string word);
    void AddWord(string &word, int filenumber);
    int NumberofWordsInIndex(int index);
    void PrintTable ();
    void PrintInedxWords(int index);
    vector<string> CounttableFiles(vector<string> &files, int limit);
    vector<int> CollisionsInIndex(int index);
    ~HashTable();

};

#endif //PLAGIARISMCATCHER_HASH_H
