#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;

int n;
mutex* forks;
mutex cout_mutex; // mutex for console output

void think(int id)
{
    {
        lock_guard<mutex> lock(cout_mutex);
        cout << "Philosopher " << id << " thinks...\n";
    }
    this_thread::sleep_for(chrono::milliseconds(500));
}

void eat(int id)
{
    {
        lock_guard<mutex> lock(cout_mutex);
        cout << "Philosopher " << id << " eats...\n";
    }
    this_thread::sleep_for(chrono::milliseconds(500));
}

void philosopher_job(int id)
{
    int left_fork = id;
    int right_fork = (id+1)%n;

    while(true)
    {
        // Step 1. Philosopher thinks
        think(id);

        // Step 2. Philosopher tries to get the forks starting with one, which has lower number
        if (left_fork<right_fork)
        {
            forks[left_fork].lock();
            forks[right_fork].lock();
        } 
        else
        {
            forks[right_fork].lock();
            forks[left_fork].lock();
        }

        // Step 3. Philosopher eats
        eat(id);

        // Step 4. Philosopher puts down the forks in the same order he took them
        forks[left_fork].unlock();
        forks[right_fork].unlock();
    }  
}

// function that runs the algorithm
void run()
{
    // creating mutex for every fork
    forks = new mutex[n];

    // creating the vector of threads
    vector<thread> philosophers;
    for (int i=0; i<n; i++) 
    {
        philosophers.emplace_back(philosopher_job, i);
    }

    for (auto &p : philosophers)
    {
        p.join();
    }

    delete[] forks;
}

int main()
{
    cout << "Number of philosophers: ";
    cin >> n;

    run();

    return 0;
}
