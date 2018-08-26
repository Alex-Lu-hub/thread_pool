#include <pthread.h>
#include <stdio.h>
#include <unistd.h>


pthread_key_t key;


void tls_cleanup(void *args)
{
    fprintf(stderr, "tls_cleanup()\n");
}


void *func(void *args)
{
    int i = 0;
    int j = 0;

    pthread_setspecific(key, &i);

    sleep(1);

    printf("func(): %p\n", pthread_getspecific(key));

    pthread_setspecific(key, &j);

    sleep(1);

    printf("func(): %p\n", pthread_getspecific(key));

    return NULL;
}


int main()
{
    pthread_t t;

    pthread_key_create(&key, tls_cleanup);
    pthread_create(&t, NULL, func, NULL);
    pthread_join(t, NULL);
}