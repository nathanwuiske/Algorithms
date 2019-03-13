#include <iostream>
#include <queue>
#include <map>
#include <fstream>
#include <unordered_set>
#include <string>
#include <unordered_map>

using namespace std;

class LadderGram
{
public:
int findLen(unordered_set<string> &d, string begin, string end)
    {
        queue<string> fifo; // BFS
        fifo.push(begin);
        unordered_map<string,int> mapped; //distance from start to the current word
        mapped[begin] = 0;
        while (fifo.size() != 0)
        {
            string currentWord = fifo.front();
            fifo.pop();
            int len = mapped[currentWord];
            for (int i = 0; i<currentWord.length(); i++)
            {
            string storedTemp = currentWord;
                for (char character = 'a'; character<'z'; character++)
                {
                    storedTemp[i] = character;
                    if (d.erase(storedTemp) > 0)
                    {
                        if (storedTemp == end)
                        {
                            int display = len+2;
                            cout<<storedTemp<<" = "<<display<<"\n";
                            return display;
                        }
                        mapped[storedTemp] = len+1;
                        cout<<storedTemp<<" = "<<mapped[storedTemp]<<"\n";
                        fifo.push(storedTemp);
                    }
                }
            }
        }
    }
};

int main()
{
    string firstWord;
    string secondWord;
    cout<<"Enter first word: ";
    cin>>firstWord;
    cout<<"Enter second word: ";
    cin>>secondWord;
    vector<string> stored;
    string words;
    ifstream load("dictionary.txt");
        if (load.is_open())
        {
            while(!load.eof())
            {
                load>>words;
                stored.push_back(words);
            }
                load.close();
        }

    LadderGram instance;
    unordered_set<string> dictionary;
    for (int i=0; i<127142; i++)
    {
        dictionary.insert(stored[i]);
    }
    cout<<"Number of steps made: "<<instance.findLen(dictionary, firstWord, secondWord)<<"\n";
}



