#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;

int n; // Number of philosophers (and forks)
mutex* forks; // Array of mutexes, each representing a fork
mutex cout_mutex; // mutex for console output

// Simulates a philosopher thinking
void think(int id)
{
    {
        // Locking console to safely print the message
        lock_guard<mutex> lock(cout_mutex);
        cout << "Philosopher " << id << " thinks...\n";
    }
    this_thread::sleep_for(chrono::milliseconds(500)); // Thinking time
}

// Simulates a philosopher eating
void eat(int id)
{
    {
        // Locking console to safely print the message
        lock_guard<mutex> lock(cout_mutex);
        cout << "Philosopher " << id << " eats...\n";
    }
    this_thread::sleep_for(chrono::milliseconds(500)); // Eating time
}

// Main job that each philosopher thread executes
void philosopher_job(int id)
{
    int left_fork = id; // Each philosopher's left fork
    int right_fork = (id+1)%n; // Each philosopher's right fork

    while(true)
    {
        // Step 1. Philosopher thinks
        think(id);

        // Step 2: Philospher tries to pick up forks
        // To avoid deadlock, forks are always picked in a consistent order:
        // Always lock the lower-numbered fork first
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

// Function that runs the algorithm
void run()
{
    // Creating mutex for every fork
    forks = new mutex[n];

    // Creating the vector of threads
    vector<thread> philosophers;
    for (int i=0; i<n; i++) 
    {
        philosophers.emplace_back(philosopher_job, i);
    }

    // Wait for all philosopher threads to finish
    for (auto &p : philosophers)
    {
        p.join();
    }

    // Clean up allocated memory
    delete[] forks;
}

int main(int argc, char* argv[])
{
    // Parse the number of philosophers from command-line arguments
    try 
    {
        n = stoi(argv[1]);
    } 
    catch(const invalid_argument& e)
    {
        cerr << "Error: Invalid argument. Please provide a valid integer.\n";
        return 1;
    }
    catch(...) 
    {
        cerr << "Unknown error occurred.\n";
        return 1;
    }

    run();

    return 0;
}
