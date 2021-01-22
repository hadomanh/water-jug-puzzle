### Problem
Let’s say that we have 3 jugs, namely A, B, and C. Jug C will always start out completely full. Furthermore, we will define a goal state where jug A will contain a gallons, B will contain b gallons, and C will contain c gallons upon completion of the search. You need to use breadth-first search to find the minimum number of moves to go from the initial state to the goal state.

### Pseudo code
```
bool BFS(int a, int b, int c) 

    add new State(a, b, c) to Queue
    pop from the Queue
    
    while (queue is not empty)
        if current_state equals goal_state
            print the backtracked solution
            return true

        if current_state has already been seen
            continue

        mark current as having been visited
        try 6 ways to pour water, pushing new states to queue
    
    return false
```

### Run test
`bash test_waterjugpuzzle.sh`