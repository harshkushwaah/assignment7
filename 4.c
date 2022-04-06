#include <stdio.h>
#include <pthread.h>
int sum[4];
int i[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

void *function(void* arg)
{
    int id = *(int *)arg;
    int start = id * 3;
    int in = 0;
    while(in < 3) {
        sum[id] += i[in + start];
        in++;
    }
}
int main()
{
    pthread_t t[4];
    int i, add;
    for (i = 0; i < 4; i++)
    {
        pthread_create(&t[i], NULL, function, (void *)&i);
    }
    for (i = 0; i < 4; i++)
    {
        pthread_join(t[i], NULL);
    }
    add = sum[0] + sum[1] + sum[2] + sum[3];
    printf("Addition is: % d", add);

    return 0;
}