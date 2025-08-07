# Detect_cycle_in_Undirected_Graphs_using_bfs

### Problem [Link](https://www.interviewbit.com/problems/cycle-in-undirected-graph/)

---

#### Code (C++)
```cpp
#include <bits/stdc++.h>
using namespace std;

int Solution::solve(int A, vector<vector<int>> &B) { // here A is the number of vertices and B is the list of edges
    
    if(A == 2 || B.size() == 0) {
        return 0;
    } // Handling edge cases: if there are only 2 vertices or no edges, no cycle can exist

    vector<vector<int>> adj(A); // Adjacency list representation of the graph
    // Constructing the adjacency list from the edge list
    // Note: B contains edges in 1-based indexing, so we need to convert them
    // to 0-based indexing for our adjacency list
    // Example: if B = [[1, 2], [2, 3]],
    // we will create adj[0] = [1] and adj[1] = [0, 2], etc.
    // This is done to ensure that we can use 0-based indexing in our implementation
    // Each edge in B is of the form [u, v], where u and v are 1-based indices
    // We will convert them to 0-based indices by subtracting 1 from each vertex
    // This is necessary because C++ uses 0-based indexing for arrays and vectors
    // After conversion, we will have adj[0] = [1], adj[1] = [0, 2], etc.
    // This allows us to easily access the neighbors of each vertex in the graph    

    for (auto &edge : B) {
        int u = edge[0] - 1;
        int v = edge[1] - 1;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> vis(A, 0);

    for (int i = 0; i < B.size(); i++) { 
        if (vis[i] == 0) {
            queue<pair<int, int>> q;
            q.push({i, -1});
            vis[i] = 1;

            while (!q.empty()) {
                int node = q.front().first;
                int parent = q.front().second;
                q.pop();

                for (int neigh : adj[node]) {
                    if (vis[neigh] == 0) {
                        vis[neigh] = 1;
                        q.push({neigh, node});
                    }
                    else if (vis[neigh] == 1 && neigh != parent) {
                        return 1;
                    }
                }
            }
        }
    }

    return 0; 
}

```
#### TC and SC
- **Time Complexity:** O(V + E), where V is the number of vertices and E is the number of edges.
- **Space Complexity:** O(V + E), for the adjacency list and visited array.
---



## 📝 Notes
How to handle 1-based indexing in the input graph:
- When reading edges, subtract 1 from each vertex to convert it to 0-based indexing
- When pushing to the adjacency list, ensure that the vertices are adjusted accordingly
```cpp
int u = edge[0] - 1; // Convert to 0-based index
int v = edge[1] - 1; // Convert to 0-based index
adj[u].push_back(v);
adj[v].push_back(u);
```