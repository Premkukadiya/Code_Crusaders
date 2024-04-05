#include <iostream>
#include <random>
#include <time.h>
#include <vector>
#include <queue>

using namespace std;

class Stadium {
private:
    vector<queue<int>> gate;
    vector<int> waiting_time;
    int N;
    int M;
    int P;

public:
    Stadium(int numGates, int capacity, int entryTime) : N(numGates), M(capacity), P(entryTime) {
        gate.resize(N);
        waiting_time.resize(N);
    }
};

void Calculate_waiting_time() {
        for (int i = 0; i < N; ++i) {
            waiting_time[i] = gate[i].size() * P;
            cout << "Waiting time for new attendee at gate " << i + 1 << ": " << waiting_time[i] << " minutes" << endl;
        }
        cout << endl;
    }

int main() 
{
    int N, M, P;
    cout << "Enter gate number: ";
    cin >> N;

    cout << "Enter capacity: ";
    cin >> M;

    cout << "Enter time (in minutes) for a single attendee to enter any gate: ";
    cin >> P;

    Stadium stadium(N, M, P);
    stadium.Random_Assignment();
    stadium.Calculate_waiting_time();
    stadium.add_in_suggested_queue();

    return 0;
}