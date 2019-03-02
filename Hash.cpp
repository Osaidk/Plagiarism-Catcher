//
// Created by Osaid K on 11/24/18.
//

#include <iostream>
#include "Hash.h"
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;


HashTable::HashTable() {

     for (int i=0; i<TableSize; i++){
         HashT[i]= new words;
         HashT[i]->filenumber=0;
         HashT[i]->next=NULL;
     }
}



unsigned int HashTable::Hash(string word) {
    unsigned long hash = 37;
   for  (int i= 0; i< word.length(); i++){
        hash = ((hash << 5) + hash) + word[i];
   }
  // hash*=word[0];
    return (unsigned int) hash%TableSize;
}






void HashTable::AddWord(string &word, int filenumber) {
    unsigned int index = Hash (word);
    if ( HashT[index]->filenumber == 0){
        HashT[index]->filenumber=filenumber;
    }
    else {
        words* ptr = HashT[index];
        words* newptr = new words;
        newptr->filenumber=filenumber;
        newptr->next=NULL;

        while (ptr->next !=NULL){
           ptr = ptr->next;
        }
        ptr->next=newptr;
    }
}



int HashTable::NumberofWordsInIndex(int index) {
    int count=0;

    if(HashT[index]->filenumber == 0){
        return count;
    }
    else{
        count++;
        words* ptr = HashT[index];
        while(ptr->next != NULL){
            ptr=ptr->next;
            count++;
        }
    }
    return count;
}



void HashTable::PrintTable() {
    int num;

    ofstream myfile;
    myfile.open("Hash.txt");

    for(int i=0; i<TableSize; i++){
        num = NumberofWordsInIndex(i);
        myfile << "--------------------\n";
        myfile << "index = "<< i << endl;
        myfile << HashT[i]->filenumber <<endl;
        myfile << "# of words = "<< num << endl;
        myfile << "--------------------\n";
        PrintInedxWords(i);
    }
}


void HashTable::PrintInedxWords(int index) {



    words* ptr = HashT[index];

    if (ptr->filenumber == 0){
       cout << " index = " << index << " is empty\n";
    }
    else
    {

        while ( ptr !=NULL){
            cout << ptr->filenumber<< endl;
            ptr = ptr->next;

        }
    }
}



vector<string> HashTable::CounttableFiles(vector <string> &files, int limit) {
    int size=files.size();
    int Arr[size][size];
    for (int n=0; n<size; n++){
        for(int y=0; y<size; y++){
            Arr[n][y]=0;
        }
    }

    vector<int> vec;
    for (int i = 0; i < TableSize; i++) {

        vec=CollisionsInIndex(i);

        if (!vec.empty()) {
            for (int k = 1; k < vec.size()-1 ; k++) {
                for (int j=k+1; j< vec.size() ; j++){
                    Arr[vec[k]][vec[j]]++;
                    Arr[vec[j]][vec[k]]++;
                }
            }
        }
    }

    vector<string> collisions;
    string filenames;
    for(int i = 1; i < files.size(); i++){
        for(int j = 0; j < i; j++){
            if(Arr[i][j] > limit){
                filenames = "";
               ostringstream toInt;
                toInt << Arr[i][j];
               filenames.append(toInt.str());
                filenames.append(": ");
                filenames.append(files[i].substr(files[i].find("/")+1, files[i].size()));
                filenames.append(", ");
                filenames.append(files[j].substr(files[j].find("/")+1, files[j].size()));
                collisions.push_back(filenames);
            }
        }
    }

    return collisions;
}






vector<int> HashTable::CollisionsInIndex(int index){
    vector<int> vec;
    if(HashT[index] == NULL || HashT[index]->next == NULL) {
        return vec;
    }
    else{
        words* i = HashT[index];

        while(i != NULL){
            vec.push_back(i->filenumber);
            i = i->next;
        }
    }
    return vec;
}



HashTable::~HashTable() {
    words *ptr;
    words *trail;
    for(int i = 0; i < TableSize; i++){
        if(HashT[i] != NULL){
            ptr = HashT[i];
            trail = ptr;
            while(ptr != NULL){
                ptr = trail->next;
                delete trail;
                trail = ptr;
            }
            delete trail;
            HashT[i] = NULL;
        }
    }
}
