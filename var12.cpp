#include <iostream>
#include <ctime>
#define srnd srand
#include <cstdlib>

// matrix A m x n
// matrix B n x 1
// matrix C m x 1
using namespace std;
int main()
{

    int m = rand() % 4 + 2;
    int n = rand() % 4 + 2;
    long long limit_offset_A = 8*m*n;
    long long limit_offset_B = 8*n;
    
    long long *matrix_a = new long long[m*n];
    long long *matrix_b = new long long[n];
    long long *matrix_c = new long long[m];

    for (int i=0; i<n*m; i++)
        matrix_a[i]=rand() % 9 + 1;

    for (int i=0; i<n; i++)
        matrix_b[i]=rand() % 9 + 1;

    for (int i=0; i<m; i++)
        matrix_c[i]=0;

    asm(
        "mov $0, %%rcx\n\t"        
        "push %%rcx\n\t"                    // Положили 0 в стек (смещение C)
        "mov $0, %%rcx\n\t"         
        "push %%rcx\n\t"                    // Положили 0 в стек (смещение B)
        "mov $0, %%rcx\n\t"                  
        "push %%rcx\n\t"                    // Положили 0 в стек (смещение A)
    
    "start_loop:\n\t"
        
        "mov %[ptr_a], %%rbx\n\t"           // Указатель на А в rbx
        "pop %%rcx\n\t"                     // Достали из стека смещение A
        "add %%rcx, %%rbx\n\t"              // Добавили смещение к указателю на А
        "push %%rcx\n\t"                    // Вернули смещение в стек
        "mov (%%rbx), %%rax\n\t"            // Закинули значение из А в rax

        "add $8, %%rsp\n\t"                 // Передвинули вершину стека на смещение B
        
        "mov %[ptr_b], %%rbx\n\t"           // Указатель на В в rbx 
        "pop %%rcx\n\t"                     // Достали из стека смещение B
        "add %%rcx, %%rbx\n\t"              // Добавили смещение к указателю на В
        "push %%rcx\n\t"                    // Вернули смещение в стек

        "sub $8, %%rsp\n\t"                 // Вернули вершину стека на смещение A

        "mulq (%%rbx)\n\t"                  // Умножили элементы матриц
       
        "add $16, %%rsp\n\t"                // Передвинули вершину стека на смещение C

        "mov %[ptr_c], %%rbx\n\t"           // Указатель на С в rbx 
        "pop %%rcx\n\t"                     // Достали из стека смещение C
        "add %%rcx, %%rbx\n\t"              // Добавили смещение к указателю на С
        "push %%rcx\n\t"                    // Вернули смещение в стек

        "sub $16, %%rsp\n\t"                // Вернули вершину стека на смещение A

        "add %%rax, (%%rbx)\n\t"            // Суммируем результат произведения и элемент матрицы С

        "pop %%rax\n\t"                     // Достали из стека смещение A
        "pop %%rbx\n\t"                     // Достали из стека смещение B
        "pop %%rcx\n\t"                     // Достали из стека смещение C

        "add $8, %%rax\n\t"                 // Увеличили смещение A на размер элемента
        "cmp %%rax, %[limit_offset_A]\n\t"  // Проверили границу матрицы А
        "je end_asm\n\t"                    // Если граница достигнута -> завершение вставки, иначе проверям В
                                            
        "add $8, %%rbx\n\t"                 // Увеличили смещение B на размер элемента
        
        "cmp %%rbx, %[limit_offset_B]\n\t"  // Проверили границу матрицы В
        "jne continue_loop\n\t"             // Если граница не достигнута -> считаем дальше, иначе меняем В и С


        "mov $0, %%rbx\n\t"                 // Обнулили В
        "add $8, %%rcx\n\t"                 // Увеличили смещение С на размер элемента

    "continue_loop:\n\t"

        "push %%rcx\n\t"                    // Вернули в стек смещение C
        "push %%rbx\n\t"                    // Вернули в стек смещение B
        "push %%rax\n\t"                    // Вернули в стек смещение A
        "jmp start_loop\n\t"                // Следующая итерация

    "end_asm:\n\t"
        
        :
        :[ptr_a]"m"(matrix_a), [ptr_b]"m"(matrix_b), [ptr_c]"m"(matrix_c), 
        [limit_offset_A]"m"(limit_offset_A), [limit_offset_B]"m"(limit_offset_B)
        :"%rax", "%rbx", "%rcx"
    );
    
    cout<<endl<<"--------------------------------"<<endl;

    cout<< "Matrix A"<<endl;

    for (int i=0; i<m; i++)
    {
        for (int j=0; j<n; j++)
            cout<<matrix_a[n*i+j]<<"\t";     
        cout << endl;
    }

    cout<<endl<< "Matrix B"<<endl;

    for (int i=0; i<n; i++)
        cout<<matrix_b[i] << endl;     

    cout<<endl<< "Matrix C"<<endl;

    for (int i=0;i<m;i++)
        cout<< matrix_c[i]<<endl;

    cout<<endl;
    delete [] matrix_a;
    delete [] matrix_b;
    delete [] matrix_c;

    return 0;
}