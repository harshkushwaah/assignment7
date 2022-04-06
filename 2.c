#include <stdio.h>
#include <pthread.h>
#include <tgmath.h>
void *factorial(void *p);
void *fibb(void *p);
int fact(int n);
int main()
{
    pthread_t tid1;
    pthread_t tid2;
    pthread_attr_t attr;      // set of thread attributes
    pthread_attr_init(&attr); // get the default attributes
    pthread_create(&tid1, &attr, factorial, NULL);
    pthread_join(tid1, NULL);
    pthread_create(&tid2, &attr, fibb, NULL);
    pthread_join(tid2, NULL);
}
int fact(int n)
{
    if (n == 0 || n == 1)
        return 1;
    else
        return n * fact(n - 1);
}
void *factorial(void *p)
{
    int i, num1;
    printf("Thread 1 (factorial) : ");
    printf("Enter Number: ");
    scanf("%d", &num1);
    printf("Factorial is: %d\n", fact(num1));
    pthread_exit(0);
}
void *fibb(void *p)
{
    int i, num1, fib[1000];
    printf("Thread 2 (fibonacci) : ");
    printf("Enter the Nth index of series: ");
    scanf("%d", &num1);
    fib[0] = 0;
    fib[1] = 1;
    for (i = 2; i < num1; i++)
        fib[i] = fib[i - 1] + fib[i - 2];
    printf("The %dth term of series is : %d", num1, fib[num1 - 1]);
    pthread_exit(0);
}