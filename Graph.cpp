#include <iostream>
using namespace std;

class Graph
{
    int adj[20][20];
    int n;
    bool visited[20] = {false};

public:
    void createGraph()
    {
        cout << "Enter number of vertices: ";
        cin >> n;

        // Initialize adjacency matrix
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                adj[i][j] = 0;
            }
        }

        int edges;
        cout << "Enter number of edges: ";
        cin >> edges;

        cout << "Enter edges (source destination):\n";

        for (int i = 0; i < edges; i++)
        {
            int u, v;
            cin >> u >> v;

            adj[u][v] = 1;
            adj[v][u] = 1;   
        }
    }

    void displayMatrix()
    {
        cout << "\nAdjacency Matrix:\n";

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << adj[i][j] << " ";
            }
            cout << endl;
        }
    }

    void resetVisited()
    {
        for (int i = 0; i < n; i++)
        {
            visited[i] = false;
        }
    }

    void DFS(int start)
    {
        visited[start] = true;
        cout << start << " ";

        for (int i = 0; i < n; i++)
        {
            if (adj[start][i] == 1 && !visited[i])
            {
                DFS(i);
            }
        }
    }

    // Breadth-First Search using a custom array-based queue
    void BFS(int start)
    {
        int q[20];           // Array to act as our queue
        int front = 0;       // Points to the front of the queue
        int rear = 0;        // Points to the next empty spot at the back

        // Mark start node as visited and add to queue
        visited[start] = true;
        q[rear] = start;
        rear++;              // Move rear forward

        // While there are elements in the queue (front hasn't caught up to rear)
        while (front < rear)
        {
            // Get the front element
            int current = q[front];
            cout << current << " ";
            front++;         // Move front forward (this "removes" it from the queue)

            // Check all adjacent vertices
            for (int i = 0; i < n; i++)
            {
                if (adj[current][i] == 1 && !visited[i])
                {
                    visited[i] = true;
                    q[rear] = i;  // Add to the back of the queue
                    rear++;       // Move rear forward
                }
            }
        }
    }
};

int main()
{
    Graph g;
    int choice, start;
    do
    {
        cout << "\n===== Graph Menu =====";
        cout << "\n1. Create a Graph";
        cout << "\n2. Display Graph (Adjacency matrix)";
        cout << "\n3. DFS traversal";
        cout << "\n4. BFS traversal";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            g.createGraph();
            break;

        case 2:
            g.displayMatrix();
            break;
            
        case 3:
            cout << "\nEnter starting vertex for DFS: ";
            cin >> start;
            g.resetVisited(); 
            cout << "DFS: ";
            g.DFS(start);
            cout << endl;
            break;

        case 4:
            cout << "\nEnter starting vertex for BFS: ";
            cin >> start;
            g.resetVisited(); 
            cout << "BFS: ";
            g.BFS(start);
            cout << endl;
            break;
            
        case 5:
            cout << "Program Exited.\n";
            break;
            
        default:
            cout << "Invalid Choice!\n";
        }

    } while (choice != 5);

    return 0;
}
