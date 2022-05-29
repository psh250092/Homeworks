#include <pthread.h>
#include <iostream>
#include <queue>

using namespace std;

void* production(void* arg);
void* consumption(void* arg);

queue<int> que;

int main() {
	pthread_t producter;
	pthread_t customer;

	pthread_create(&producter, NULL, production, NULL);
	pthread_create(&customer, NULL, consumption, NULL);
	
}

void* production(void* arg)
{
	while (1)
	{
		cout << "product : " << que.size() + 1 << endl;
		que.push(que.size() + 1);
	}
	return NULL;
}
void* consumption(void* arg)
{
	while (1)
	{
		cout << "consume : " << que.front() << endl;
		que.pop();
	}
	return NULL;
}