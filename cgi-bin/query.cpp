//
//  main.cpp
//  query
//
//  Created by Dora on 4/27/16.
//  Copyright © 2016 Dora. All rights reserved.
//

#include <cstdio>
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

bool not_empty = 0;

struct Entry
{
    string univ, name;
    int rank;
    bool acm_fellow, ieee_fellow, funding;
};

vector<Entry> list;

inline void trans_lower(string& token)
{
    std::transform(token.begin(), token.end(), token.begin(), ::tolower);
}
void print(Entry& entry)
{
    if (not_empty)
        cout << ",";
    cout<<"{";
    cout<<"\"rank\":"<<"\""<<entry.rank<<"\",";
    cout<<"\"univ\":"<<"\""<<entry.univ<<"\",";
    cout<<"\"name\":"<<"\""<<entry.name<<"\",";
    cout<<"\"acm_fellow\":"<<"\""<<entry.acm_fellow<<"\",";
    cout<<"\"ieee_fellow\":"<<"\""<<entry.ieee_fellow<<"\",";
    cout<<"\"funding\":"<<"\""<<entry.funding<<"\"";

    cout<<"}";
    return;
}

int main(int argc, char *argv[]){
    if (argc !=2)
    {
        cout<<"Error Input"<<endl;
        return -1;
    }

    fstream input;
    input.open("./database/index.txt");
    string token;
    while (getline(input, token, '-'))
    {
        trans_lower(token);
        Entry entry;
        entry.rank = stoi(token);
        getline(input, token, '|');
        trans_lower(token);
        entry.univ = token;
        getline(input, token, '|');
        trans_lower(token);
        entry.name = token;
        getline(input, token, '|');
        trans_lower(token);
        entry.acm_fellow = (token =="yes" ? 1:0);
        getline(input, token, '|');
        trans_lower(token);
        entry.ieee_fellow = (token =="yes" ? 1:0);
        getline(input, token, '\n');
        trans_lower(token);
        entry.funding = (token =="yes" ? 1:0);
        //cout<<entry.rank<<" "<<entry.univ<< " "<<entry.name<<" "<<entry.acm_fellow<<endl;
        list.push_back(entry);
    }

    vector<string> keywords;
    string str(argv[1]);
    istringstream ss(str);
    while (getline(ss, token, ' '))
    {
        trans_lower(token);
        keywords.push_back(token);
    }
    cout << "[";
    for (int i=0 ; i<list.size(); ++i)
    {
        for (int j=0; j<keywords.size(); ++j)
            if ((list[i].name.find(keywords[j]))!= -1 ||
                (list[i].univ.find(keywords[j]))!= -1)
        {
            print(list[i]);
            not_empty = 1;
            //return 0;
        }
    }
    cout<<"]";
    //printf("{\"get\": \"%s\", \"put\": 2}\n", a);
    //fprintf(stderr, "log: %s\n", a);
    return 0;
}
