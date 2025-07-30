# Connected Components

### Problem [Link](https://www.interviewbit.com/problems/connected-components/)

## 🧩 Problem: Connected Components

**Category:** Programming / Graph Data Structure & Algorithms  
**Difficulty:** Easy  
**Success Rate:** 47.2%  

---

### 📘 Problem Description

Given a graph with `A` nodes.  
The edges in the graph are given in a 2D array `B`.  
There is an **undirected** edge between `B[i][0]` and `B[i][1]`.  
Find the number of **connected components** in the given graph.

---

### 🔒 Constraints

- `1 <= A <= 10^5`
- `1 <= |B| <= 10^5`
- `1 <= B[i][0], B[i][1] <= A`

---

### 📥 Input Format

- First argument is an integer `A`.
- Second argument is a 2D integer array `B`.

---

### 📤 Output Format

- Return an integer representing the number of connected components in the graph.

---

### 🧪 Example Input

#### Input 1:
```plaintext
A = 4
B = [[1, 2],
    [2, 3]]
```

#### Input 2:
```plaintext
A = 3
B = [[1, 2],
    [2, 1]]
```

---

### ✅ Example Output

#### Output 1:
```plaintext
2
```

#### Output 2:
```plaintext
2
```

---

### 🧠 Example Explanation

**Explanation 1:**  
The two connected components are `[1, 2, 3]` and `[4]`.

**Explanation 2:**  
The two connected components are `[1, 2]` and `[3]`.


---
## 💡 Approaches

### 📌 Best Approach 
We will use a for loop for traversing all the vertices if that vertices is not visited and call traversing algorithm.

#### Code (C++)
```cpp
int Solution::solve(int A, vector<vector<int> > &B) {
    // forst making it adjacency list
    int n = B.size();
    vector<vector<int>> adj(A);
    for (auto &edge : B) {
        int u = edge[0] - 1;  // convert to 0-indexed
        int v = edge[1] - 1;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    //making vis array
    int vis[A] = {0};
    
    int count = 0;
    
    for(int i = 0 ; i<A ; i++){
        if(vis[i] == 0){
            count++;
            // writing the logic of bfs
            
            queue<int>q;
            q.push(i);
            
            vis[i] = 1;
            
            while(!q.empty()){
                int node = q.front();
                q.pop();
                
                for(auto & neigh : adj[node]){
                    if(vis[neigh] == 0){
                        vis[neigh] = 1;
                        q.push(neigh);
                    }
                }
            }
        }
    }
    
    return count;
    
}

```
#### TC and SC
- **Time Complexity:** O(E) + O(A) + O(A + 2E)  where E = edges, A = no. of vertices , in big O notation we discard the constant 2  
the expression became O(E) + O(A) + O(A + E) and we know that accoring to the bigO notation we will take the highest dominating value which is O(A + E).
- **Space Complexity:** O(A + 2E) + O(A) + O(A) + O(1)



---

## 📝 Notes

In this problem the graph given is of one based indexing  
So keep in mind that you need to make adj list   

```cpp
    vector<vector<int>> adj(A);
    for (auto &edge : B) {
        int u = edge[0] - 1;  // convert to 0-indexed
        int v = edge[1] - 1;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
```

