#include <stdio.h>

int array[3] = {3, 11, 15};

int main()
{
    int sum=0;
    int i=0;
    int j=3;
start_loop:
    if (i==j)
        goto exit;
    array[i]=array[i]&-33;
    sum=sum+array[i];
    i++;
    if (i==j)
        goto exit;
    array[i]=array[i]|16;
    sum=sum+array[i];
    i++;
    goto start_loop;
exit:
    printf ("%i", sum);
    return 0;
}