#include <iostream>
#include "Hash.h"
#include <string>
#include <cstdlib>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <fstream>
#include <queue>
#include <cstring>
#include "Sequencer.h"
#include <algorithm>

using namespace std;
/*function... might want it in some class?*/
int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}



int main(int argv, char** argc) {
    HashTable t;
    string dir = string(argc[1]);
    vector<string> files = vector<string>();

    getdir(dir, files);

    WordSequence c(stoi(argc[2]));
    c.open_outfile();

    files.erase(files.begin());
    files.erase(files.begin());

    for (int i = 0; i < files.size(); i++) {
        c.SequenceBuilder(argc[1], files[i], i);

    }
    int size= files.size();
    int limit=atoi(argc[3]);
     vector<string> vec= c.CountCollisions(files,limit);
    sort(vec.begin(), vec.end());
    reverse(vec.begin(), vec.end());
    for(int i = 0; i < vec.size(); i++){
        cout << vec[i] << endl;
    }
}






