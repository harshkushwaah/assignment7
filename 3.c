#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#define MAX 16
#define MAX_THREAD 4
// place arr, key and other variables as global to access from different thread
int arr[] = {1, 6, 8, 11, 13, 14, 15, 19, 21, 23, 26, 28, 31, 65, 108, 220};
int key = 31;
bool found = false;
int part = 0;
void *binary_search(void *arg)
{ // There are four threads, each will take 1/4th part of the list
    int thread_part = part++;
    int mid;
    int start = thread_part * (MAX / 4); // set start and end using the thread part    
    int end = (thread_part + 1) * (MAX / 4);
    // search for the key until low < high    // or key is found in any portion of array    
    while (start < end && !found)
    {
        // if some other thread has got the element, it will stop      
        mid = (end - start) / 2 + start;
        if (arr[mid] == key)
        {
            found = true;
            break;
        }
        else if (arr[mid] > key)
            end = mid - 1;
        else
            start = mid + 1;
    }
}
void main()
{
    pthread_t threads[MAX_THREAD];
    for (int i = 0; i < MAX_THREAD; i++)
        pthread_create(&threads[i], NULL, binary_search, (void *)NULL);
    for (int i = 0; i < MAX_THREAD; i++)
        pthread_join(threads[i], NULL); // wait, to join with the main thread    
    if (found)
        printf("found in array\n");
    else
        printf("not found in array");
    printf("\n\n");
}