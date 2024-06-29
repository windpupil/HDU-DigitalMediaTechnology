#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include <cstring>
using namespace std;
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "Usage: " << argv[0] << " <corpus> <query>" << endl;
        return 1;
    }
    ifstream corpus(argv[1]);
    if (!corpus)
    {
        cout << "Failed to open " << argv[1] << endl;
        return 1;
    }
    string line;
    string text;
    while (getline(corpus, line))
    {
        text += line + '\n';
    }
    map<string, set<int>> index;
    istringstream iss(text);
    string word;
    int pos = 1;
    while (iss >> word)
    {
        index[word].insert(pos);
        pos += 1;
    }
    ifstream query(argv[2]);
    if (!query)
    {
        cout << "Failed to open " << argv[2] << endl;
        return 1;
    }
    while (getline(query, line))
    {
        if (index.find(line) != index.end())
        {
            cout << *index[line].begin() << " " << line << endl;
        }
        else if (line.find(' ') != string::npos)
        {
            string first_word = line.substr(0, line.find(' '));
            set<int> first_set = index[first_word];
            bool found = false ;
            int pos = text.find(line);
            if(pos != string::npos){
                int temp = text.find(first_word);
                for(int i: first_set)
                {
                    if(temp == pos){
                        cout << i << " " << line << endl;
                        found = true;
                        break;
                    }
                    temp = text.find(first_word, temp + 1);
                }
            }
            if(!found){
                cout << " -- " << line << endl;
            }
        }
        else
        {
            cout << " -- " << line << endl;
        }
    }
    return 0;
}