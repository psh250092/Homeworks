// OS과제.cpp : 애플리케이션의 진입점을 정의합니다.
//

#include "OS과제.h"

#include <pthread.h>
#include <iostream>
#include <queue>
#include <semaphore.h>
#include <unistd.h>

const int REPEAT = 30;
const int MAX = 100;

using namespace std;

queue<int> q;

pthread_mutex_t m;
pthread_cond_t c;

void* product(void* arg);
void* consume(void* arg);

int main() {
	pthread_t productor, consumer;

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
		pthread_mutex_lock(&m);
		if (q.size() >= MAX)
		{
			pthread_cond_wait(&c, &m);
			cout << "productor " << pthread_self() <<  " wait..." << endl;
		}
		q.push(q.size());
		cout << pthread_self() << " producted " << q.size() << endl;
		pthread_cond_signal(&c);
		pthread_mutex_unlock(&m);
	}
	return NULL;
}
void* consume(void* arg) {
	int r = REPEAT;
	while (r--)
	{
		cout << pthread_self() << " consumed " << q.front() << endl;
		if (q.empty())
		{
			pthread_cond_wait(&c, &m);
			cout << "consumer " << pthread_self() << "consumer wait..." << endl;
		}
		q.pop();
		pthread_cond_signal(&c);
		pthread_mutex_unlock(&m);
	}
	return NULL;
}

