#include <iostream>
#include <string>
#include <cstring>
#include <map>

using namespace std;




int main(int argc, char *argv[], char *enpv[])
{
    bool first_word_ok = false;
    int temp_i=0;
    string bigram = "";
    map <string, int> dict;
    map <string, int> :: iterator it;
    dict.value_comp();
    
    if (argc!=2)
        return -1;

    for (int i=0; i<strlen(argv[1]); i++)
    {
        
        if (argv[1][i] == ' ')
            {
                if (first_word_ok == false) 
                {
                    first_word_ok = true;
                    temp_i = i;
                }
                else
                {
                    first_word_ok = false;
                    if (dict.find(bigram) != dict.end()) dict.find(bigram)->second++;
                    else
                    {
                        dict[bigram] = 1;
                    }
                    
                    bigram="";
                    i = temp_i;
                    continue;
                }
                

            }

        bigram += tolower(argv[1][i]);


    }

    if (dict.find(bigram) != dict.end()) dict.find(bigram)->second++;
    else dict[bigram] = 1;
    
    
    it = dict.end();
    it--;
    for (;;)
    {
        if (it != dict.begin())
        {
            cout<<it->second<<" : "<<it->first<<endl;
            it--;
            continue;
        }
        cout<<it->second<<" : "<<it->first<<endl;
        break;
    }
    
    
    return 0;
}