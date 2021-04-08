#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main(int argc, char *argv[], char *enpv[])
{
    int proc_num=0;
    pid_t num;
    string buff = "";
    
    if (argc!=2)
        return -1;

    for (int i=0; i<strlen(argv[1]); i++)
    {
        
        if (argv[1][i] == '.')
            {
                cout<<"child process #"<<proc_num++<<endl;

                num = fork();
                if (num == 0) execl("first", "first", buff.c_str(), NULL);

                int status=0;
                waitpid(num, &status,0);
                buff="";
                i++;
                continue;
            }

        buff += tolower(argv[1][i]);


    }

    
    
    return 0;
}