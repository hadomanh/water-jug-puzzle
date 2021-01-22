#include <iostream>
#include <sstream>
#include <string>
#include <regex>
#include <queue>
#include <map>
#include <new>

using namespace std;

// Struct to represent state of water in the jugs.
struct State
{
    int a, b, c;
    int toPour;
    char from;
    char to;
    shared_ptr<State> parent;

    State() {}
    State(int _a, int _b, int _c) : a(_a), b(_b), c(_c), toPour(0), parent(nullptr) {}
    State(int _a, int _b, int _c, int _toPour, char _from, char _to, shared_ptr<State> _parent) : a(_a), b(_b), c(_c), toPour(_toPour), from(_from), to(_to), parent(_parent) {}

    // String representation of state in tuple form.
    void to_string()
    {
        if (toPour > 0)
        {
            cout << "Pour " << toPour;
            if (toPour == 1)
            {
                cout << " gallon";
            } else
            {
                cout << " gallons";
            }
            cout << " from " << from << " to " << to;
        }
        else
        {
            cout << "Initial state";
        }
        
        cout << ". (" << a << ", " << b << ", " << c << ")" << endl;
        
        
    }
};

void demonstrate(shared_ptr<State> state) {
    if (state.get()->parent != nullptr)
    {
        demonstrate(state.get()->parent);
    }
    state.get()->to_string();
    return;
    
}

bool BFS(int a, int b, int c, int capacity[], int goal[])
{
    map<pair<pair<int, int>, int>, int> m;
    queue<shared_ptr<State> > q;
    
    q.push(make_shared<State>(a,b,c));

    int toPour;

    while (!q.empty())
    {
        // Current state == goal state
        if (q.front().get()->a == goal[0] && q.front().get()->b == goal[1] && q.front().get()->c == goal[2])
        {
            demonstrate(q.front());
            return true;
        }

        // Current state has already been seen
        if (m[make_pair(make_pair(q.front().get()->a, q.front().get()->b), q.front().get()->c)] == 1)
        {
            q.pop();
            continue;
        }

        // Mark as visited
        m[make_pair(make_pair(q.front().get()->a, q.front().get()->b), q.front().get()->c)] = 1;

        // Try 6 ways to pour water and push new state to queue
        // a -> b
        if (q.front().get()->a > 0 && q.front().get()->b < capacity[1])
        {
            toPour = q.front().get()->a > (capacity[1] - q.front().get()->b) ? (capacity[1] - q.front().get()->b) : q.front().get()->a;

            q.push(make_shared<State>(q.front().get()->a - toPour, q.front().get()->b + toPour, q.front().get()->c, toPour, 'A', 'B', q.front()));
        }
        // a -> c
        if (q.front().get()->a > 0 && q.front().get()->c < capacity[2])
        {
            toPour = q.front().get()->a > (capacity[2] - q.front().get()->c) ? (capacity[2] - q.front().get()->c) : q.front().get()->a;

            q.push(make_shared<State>(q.front().get()->a - toPour, q.front().get()->b, q.front().get()->c + toPour, toPour, 'A', 'C', q.front()));
        }
        // b -> c
        if (q.front().get()->b > 0 && q.front().get()->c < capacity[2])
        {
            toPour = q.front().get()->b > (capacity[2] - q.front().get()->c) ? (capacity[2] - q.front().get()->c) : q.front().get()->b;

            q.push(make_shared<State>(q.front().get()->a, q.front().get()->b - toPour, q.front().get()->c + toPour, toPour, 'B', 'C', q.front()));
        }
        // b -> a
        if (q.front().get()->b > 0 && q.front().get()->a < capacity[0])
        {
            toPour = q.front().get()->b > (capacity[0] - q.front().get()->a) ? (capacity[0] - q.front().get()->a) : q.front().get()->b;

            q.push(make_shared<State>(q.front().get()->a + toPour, q.front().get()->b - toPour, q.front().get()->c, toPour, 'B', 'A', q.front()));
        }
        // c -> a
        if (q.front().get()->c > 0 && q.front().get()->a < capacity[0])
        {
            toPour = q.front().get()->c > (capacity[0] - q.front().get()->a) ? (capacity[0] - q.front().get()->a) : q.front().get()->c;

            q.push(make_shared<State>(q.front().get()->a + toPour, q.front().get()->b, q.front().get()->c - toPour, toPour, 'C', 'A', q.front()));
        }
        // c -> b
        if (q.front().get()->c > 0 && q.front().get()->b < capacity[1])
        {
            toPour = q.front().get()->c > (capacity[1] - q.front().get()->b) ? (capacity[1] - q.front().get()->b) : q.front().get()->c;

            q.push(make_shared<State>(q.front().get()->a, q.front().get()->b + toPour, q.front().get()->c - toPour, toPour, 'C', 'B', q.front()));
        }
        q.pop();
    }

    return false;
}

int main(int argc, char **argv)
{

    if (argc != 7)
    {
        cout << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
        exit(0);
    }

    regex digits("\\d+");
    int *capacity = new int[3];

    for (int i = 1; i < 4; i++)
    {
        if (!regex_match(argv[i], digits) || stoi(argv[i]) == 0)
        {
            cout << "Error: Invalid capacity '" << argv[i] << "' for jug " << (char)('A' + i - 1) << "." << endl;
            exit(1);
        }
        capacity[i - 1] = stoi(argv[i]);
    }

    int *goal = new int[3];
    int totalGoal = 0;

    for (int i = 4; i < 7; i++)
    {
        if (!regex_match(argv[i], digits))
        {
            cout << "Error: Invalid goal '" << argv[i] << "' for jug " << (char)('A' + i - 4) << "." << endl;
            exit(1);
        }
        goal[i - 4] = stoi(argv[i]);

        totalGoal += stoi(argv[i]);
    }

    for (int i = 0; i < 3; i++)
    {
        if (goal[i] > capacity[i])
        {
            cout << "Error: Goal cannot exceed capacity of jug " << (char)('A' + i) << "." << endl;
            exit(2);
        }
    }

    if (totalGoal != capacity[2])
    {
        cout << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
        exit(3);
    }

    if (!BFS(0, 0, capacity[2], capacity, goal))
    {
        cout << "No solution." << endl;
    }

    return 0;
}
