//
// Created by Osaid K on 12/1/18.
//

#ifndef PLAGIARISMCATCHER_SEQUENCER_H
#define PLAGIARISMCATCHER_SEQUENCER_H

#include "Hash.h"
#include <string>
#include <queue>
#include <cstdlib>
#include <fstream>

class WordSequence{
private:

    int SequenceNumber;
    queue<string> words;
    string word;
    HashTable myHash;

public:
    ofstream myfileTest;
    WordSequence(){
        SequenceNumber = 0;
    }

    WordSequence(int numOfWords){
        SequenceNumber = numOfWords;
    }

    void open_outfile(){

        myfileTest.open("Test.txt");
        myfileTest << "open";
    }

    void close_file(){
        myfileTest.close();
    }



    void printHash(){
        myHash.PrintTable();
    }

    vector<string> CountCollisions(vector <string> &files, int limit){
        vector <string> vec=myHash.CounttableFiles(files, limit);
        return vec;
    }



    void SequenceBuilder(string const &dir, string const &filename, int i) {
        string file = dir + "/" + filename;

        ifstream myfile;
        myfile.open(file.c_str());

        if (myfile.is_open()) {

            while (!myfile.eof()) {
                myfile >> word;
                words.push(word);

                if (words.size() == SequenceNumber) {
                    queue<string> temp = words;
                    word.erase();
                    while (!temp.empty()) {
                        word += temp.front();
                        temp.pop();
                    }
                    words.pop();
                    myfileTest << word << endl;
                    myHash.AddWord(word, i);
                    word.erase();

                }
            }
        }
        myfile.close();
    }


};

#endif //PLAGIARISMCATCHER_SEQUENCER_H
