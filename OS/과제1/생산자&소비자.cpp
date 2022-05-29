#include <pthread.h>
#include <iostream>
#include <queue>

using namespace std;

queue<int> q;

void* product(void* arg);
void* consume(void* arg);

int x;
int main() {
	pthread_t productor, consumer;
	pthread_create(&productor, NULL, product, NULL);
	pthread_create(&consumer, NULL, consume, NULL);
	pthread_join(productor, NULL);
	pthread_join(consumer, NULL);
}

void* product(void* arg) {
	q.push(q.size());
	cout << pthread_self() << " producted " << q.size() << endl;
	return NULL;
}
void* consume(void* arg) {
	cout << pthread_self() << " consumed " << q.front() << endl;
	q.pop();
	return NULL;
}

