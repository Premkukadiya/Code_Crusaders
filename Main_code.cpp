#include <iostream>
#include <random>
#include <time.h>
#include <vector>
#include <queue>

using namespace std;

class Stadium 
{
private:
    vector<queue<int>> gate;
    vector<int> waiting_time;
    int N;
    int M;
    int P;

public:
    Stadium(int numGates, int capacity, int entryTime) : N(numGates), M(capacity), P(entryTime) 
    {
        gate.resize(N);
        waiting_time.resize(N);
}

    void Calculate_waiting_time() 
    {
        for (int i = 0; i < N; ++i) {
            waiting_time[i] = gate[i].size() * P;
            cout << "Waiting time for new attendee at gate " << i + 1 << ": " << waiting_time[i] << " minutes" << endl;
        }
        cout << endl;
 }

    void Waiting_time() 
    {
        for (int i = 0; i < N; ++i) {
            waiting_time[i] = gate[i].size() * P;
        }
    }

    void Random_Assignment(){
            srand(time(NULL));
        for (int i = 0; i < M / 2; i++) {
            int a = rand() % N;
            gate[a].push(i);
        }
        for (int i = 0; i < N; i++) {
            cout << "Number of attendee in " << i + 1 << " gate " << gate[i].size() << endl;
        }
        cout << endl;
    }

    int suggest_queue() {
        int min = waiting_time[0];
        cout << "Suggested gates are: ";
        for (int i = 0; i < N; ++i) {
            if (min >= waiting_time[i]) {
                min = waiting_time[i];
            }
        }
        int j;
        for (int i = 0; i < N; ++i) {
            if (waiting_time[i] == min) {
                cout << i + 1 << " ";
                j = i;
            }
        }
        cout << "and for this gate waiting time is " << min << " minutes" << endl;
        return j;
    }
    // Function to arrange people in gates for minimum waiting time
    void Internal_Arrangement(int k)
    {
        cout << "After arranging people for minimum time :" << endl;
        for (int i = 0; i < N - 1; i++)
        {
            while (gate[i].size() != k / (N))
            {
                gate[i + 1].push(gate[i].front());
                gate[i].pop();
            }
        }

        for (int j = 0; j < N - 2; j++)
        {
            int a = gate[N - 1].size(), b = gate[j].size();
            if (a - b > 1)
            {
                gate[j].push(gate[N - 1].front());
                gate[N - 1].pop();
            }
        }
    }


    void add_in_suggested_queue() {
        int People;
        if (M % 2 == 0)
            People = M / 2;
        else
            People = M / 2 + 1;

        for (int i = 0; i < People; i++) {
            int Index_gate = suggest_queue();
            gate[Index_gate].push(i);
            for (int j = 0; j < N; j++) {
                if (!gate[j].empty()) {
                    gate[j].pop();
                }
                Waiting_time();
            }
        }
    }
};



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

 return 0;
}