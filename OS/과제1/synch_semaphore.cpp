// OS과제.cpp : 애플리케이션의 진입점을 정의합니다.
//

#include "OS과제.h"

#include <pthread.h>
#include <iostream>
#include <queue>
#include <semaphore.h>
#include <unistd.h>

const int REPEAT = 30000;
const int MAX = 30;

using namespace std;

queue<int> q;

sem_t m, f, e;

void* product(void* arg);
void* consume(void* arg);

int main() {
	pthread_t productor, consumer;
	sem_init(&m, 0, 1);
	sem_init(&e, 0, MAX);
	sem_init(&f, 0, 0);

	pthread_create(&productor, NULL, product, NULL);
	pthread_create(&consumer, NULL, consume, NULL);

	pthread_join(productor, NULL);
	pthread_join(consumer, NULL);

	cin.get();
	return 0;
}

void* product(void* arg) {
	int r = REPEAT;
	while (r--)
	{
		sem_wait(&m);
		sem_wait(&e);

		q.push(q.size());
		cout << pthread_self() << " producted " << q.size() << endl;
		
		sem_post(&f);
		sem_post(&m);
	}
	return NULL;
}
void* consume(void* arg) {
	int r = REPEAT;
	while (r--)
	{
		sem_wait(&m);
		sem_wait(&f);

		cout << pthread_self() << " consumed " << q.front() << endl;
		q.pop();

		sem_post(&e);
		sem_post(&m);
	}
	return NULL;
}

