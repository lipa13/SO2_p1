#include <iostream>
#include <vector>
#include <thread>

using namespace std;

void think(int id)
{
    cout << "Philospher " << id << " thinks\n";
    this_thread::sleep_for(chrono::milliseconds(500));
}

void eat(int id)
{
    cout << "Philosopher " << id << " eats...\n";
    this_thread::sleep_for(chrono::milliseconds(500));
}

void philosopher_job(int id, int n)
{
    int left_fork = id;
    int right_fork = (id+1)%n;

    while(true)
    {
        // filzof myśli
        // filozof próbuje pobrać 1. widelec (o niższym numerze)
        // 2. widelec
        // filozof je
        // filozof odkłada widelce w tej samej kolejności w jakiej je wziął
        // itd 
    }  
}

// function that runs the algorithm
void run(int n)
{
    // creating the vector of threads
    vector<thread> philosophers;
    for (int i=0; i <n; i++) 
    {
        philosophers.emplace_back(philosopher_job, i, n);
    }

    for (auto &p : philosophers)
    {
        p.join();
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
