#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <unistd.h>
#include <pthread.h>
#include <algorithm>
#include <fstream>

using namespace std;

vector <pair<int, string>> bigrams_v;

pthread_mutex_t mutex_of_result;
pthread_mutex_t mutex_of_params;

int sync_num_threads = 0;
string buff_share = "";

bool need_sort = false;

void *find_bigrams(void *arg)
{
    pthread_mutex_lock(&mutex_of_params);
        string local_buff=buff_share;
        ++sync_num_threads;
        int local_num_thread=sync_num_threads;
    pthread_mutex_unlock(&mutex_of_params);
    
    cout<<"Thread #"<<local_num_thread<<" start\n";
    bool first_word_ok = false;
    int temp_i=0;
    string bigram = "";
    map <string, int> dict;
    
    sleep(local_num_thread);

    for (int i=0; i<local_buff.size(); ++i)
    {
        if (local_buff[i] == ' ')
        {
            if (first_word_ok == false) 
            {
                first_word_ok = true;
                temp_i = i;
            }
            else
            {
                first_word_ok = false;
                if (dict.find(bigram) != dict.end())
                    dict.find(bigram)->second++;
                else
                    dict[bigram] = 1;
                
                bigram="";
                i = temp_i;
                continue;
            }
        }
        bigram += tolower(local_buff[i]);
    }

    if (dict.find(bigram) != dict.end())
        dict.find(bigram)->second++;
    else
        dict[bigram] = 1;
    
    first_word_ok=false;

    pthread_mutex_lock(&mutex_of_result);
    for (auto i : dict)
    {
        for (auto& j : bigrams_v)
        {
            if (i.first==j.second)
            {
                ++j.first;
                first_word_ok=true;
                break;
            }    
        }
        if (!first_word_ok)
        {
            bigrams_v.emplace_back(i.second,i.first);
        }
        first_word_ok=false;

    }
    pthread_mutex_unlock(&mutex_of_result);

    pthread_mutex_lock(&mutex_of_params);
        --sync_num_threads;
        cout<<"Thread #"<<local_num_thread<<" stop\n";
    pthread_mutex_unlock(&mutex_of_params);
    
    return 0; 
}




int main(int argc, char *argv[], char *enpv[])
{
    pthread_t tid;
    int local_sync=0;
    string buff_local=""; 
    
    if (argc!=3)
    {
        cout<<"Wrong number of arguments\n";
        return -1;
    }

    fstream fin(argv[1]);

    if (!fin.is_open())
    {
        cout << "Файл не может быть открыт!\n";
        return -1;
    }

    while (getline(fin,buff_local))
    {
        for (int i=0; i<buff_local.size(); ++i)
        {
            
            if (buff_local[i] == '.')
            {
                    
                for(;;)
                {
                    pthread_mutex_lock(&mutex_of_params);
                    if (sync_num_threads<atoi(argv[2]))
                    {   
                        pthread_mutex_unlock(&mutex_of_params);
                        break;
                    }
                    pthread_mutex_unlock(&mutex_of_params);
                }

                local_sync=sync_num_threads+1;
                
                pthread_create(&tid,NULL,find_bigrams,NULL);
                pthread_detach(tid);
                for(;;)
                {
                    pthread_mutex_lock(&mutex_of_params);
                    if (local_sync==sync_num_threads) 
                    {
                        pthread_mutex_unlock(&mutex_of_params);
                        break;
                    }
                    pthread_mutex_unlock(&mutex_of_params);
                }

                buff_share="";
                ++i;
                continue;
            }

            buff_share += tolower(buff_local[i]);

        }
    }

    fin.close();

    for(;;)
    {
        pthread_mutex_lock(&mutex_of_params);
        if (sync_num_threads==0) 
        {
            pthread_mutex_unlock(&mutex_of_params);
            break;
        }
        pthread_mutex_unlock(&mutex_of_params);
    }

    cout<<" Results: \n";
    
    sort(bigrams_v.rbegin(), bigrams_v.rend());
    for(auto i : bigrams_v)
        cout<<i.second<<" : "<<i.first<<"\n";
    
    return 0;
}