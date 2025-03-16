#include <iostream>
#include <vector>
#include <thread>

using namespace std;

void think()
{

}

// 
void eat()
{

}

void philosopher_job()
{

}

// function that runs the algorithm
void run(int n)
{
    vector<thread> philosophers;

    // creating the vector of threads
    for (int i=0; i <n; i++) 
    {
        philosophers.emplace_back(philosopher_job, i);
    }
}

int main()
{
    int n;

    cout << "Number of philosophers: ";
    cin >> n;

    run(n);

    return 0;
}
