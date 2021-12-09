#ifndef MENUMAKER_GRAPH_H
#define MENUMAKER_GRAPH_H

#include <map>
#include <stack>
#include <set>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

struct DisjointSets
{
    int* parent;
    int numSets;

    DisjointSets(int numVertices)
    {
        numSets = numVertices;
        parent = new int[numSets];

        for (int i = 0; i <= numSets; i++)
        {
            parent[i] = -1;
        }
    }

    int find(int value)
    {
        //  find the root of the set
        if (parent[value] == -1)
        {
            return value;
        }
        return find(parent[value]);
    }

    void merge(int a, int b)
    {
        //  make b the root of a to combine them into the same set
        a = find(a);
        b = find(b);

        parent[a] = b;
    }
};

class Graph{
private:
    //  stores the graph as an adjacency list
    map<int, vector<pair<int, double>>> adjListGraph;
    //  stores the graph as an edge list
    vector<pair<double, pair<int, int>>> edgeListGraph;
    vector<pair<double, pair<int, int>>> kruskal;
    map<int, pair<int, int>> prim;
public:
    //  adds an edge in the adjacency list
    void addEdge(int from, int to, double weight);
    //  builds the edge list implementation from the adjacency list
    void buildEdgeList();
    //  prints the connections for a specified IP address
    void printConnection(int index);
    vector<double> createKruskal();
    vector<double> createPrim();
};

void Graph::addEdge(int from, int to, double weight) {
    //  checks if the from vertx already exists in the graph
    if (adjListGraph.find(from) == adjListGraph.end()) {
        //  inserts a new connection between from and to
        adjListGraph[from].push_back(make_pair(to, weight));
        adjListGraph[to].push_back(make_pair(from, weight));
    }
    else {
        //  checks if there is already a connection between from and to, prevents duplicates
        vector<pair<int, double>>::iterator iter;
        for (iter = adjListGraph[from].begin(); iter != adjListGraph[from].end(); iter++) {
            if (iter->first == to) {
                return;
            }
        }
        //  inserts a new connection between from and to
        adjListGraph[from].push_back(make_pair(to, weight));
        adjListGraph[to].push_back(make_pair(from, weight));
    }
}

void Graph::buildEdgeList() {
    //  iterates through the adjacency list
    map<int, vector<pair<int, double>>>::iterator iter;
    for (iter = adjListGraph.begin(); iter != adjListGraph.end(); iter++) {
        //  adds all the connected to the edge list
        for (int i = 0; i < iter->second.size(); i++) {
            //if the edge does not yet exist, add the pair of (weight, (from, to)) to the edge list
            if (iter->second[i].first > iter->first)
                edgeListGraph.push_back(make_pair(iter->second[i].second, make_pair(iter->first, iter->second[i].first)));
        }
    }
    //  sorts the edges in ascending order
    sort(edgeListGraph.begin(), edgeListGraph.end());
}

void Graph::printConnection(int index){
    cout << index << ": {";
    //  prints all the connection for the IP address associated with index
    for(int i = 0; i < adjListGraph[index].size(); i++){
        cout << adjListGraph[index][i].first << ", " << adjListGraph[index][i].second << " ";
    }
    cout << "}";
}

vector<double> Graph::createKruskal()
{
    //initialize a disjoint set for each vertex
    DisjointSets setOfSets(adjListGraph.size());
    vector<double> result;

    //traverse the edges by ascending weight
    for (int i = 0; i < edgeListGraph.size(); i++)
    {
        //if the two vertices are not in the same set, combine the sets
        if (setOfSets.find(edgeListGraph[i].second.first) != setOfSets.find(edgeListGraph[i].second.second))
        {
            setOfSets.merge(setOfSets.find(edgeListGraph[i].second.first), setOfSets.find(edgeListGraph[i].second.second));
            //add the edge to the kruskal vector container in order
            kruskal.push_back(edgeListGraph[i]);
        }
    }
    int end = kruskal[kruskal.size() - 1].second.second; //last index visited
    int start = kruskal[0].second.first; //first index accessed
    double sum = 0;
    for(int i = 0; i < kruskal.size(); i++){
        sum += kruskal[i].first;
    }
    result.push_back(start);
    result.push_back(end);
    result.push_back(sum);
    return result;
}

vector<double> Graph::createPrim()
{
    //  stores which vertices have been included in the MST
    vector<bool> visited;
    //  stores the minimum weight value for a vertex
    vector<double> value;
    //  stores the staring and ending vertices and the sum resulting from Prim's MST algorithm
    vector<double> result;
    //  stores the source vertex
    int source = 1;
    //  stores the vertices that are being put into the MST in a priority queue
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> priorityQ;
    //  initialize all vertices as not in the MST
    for(int i = 0; i <= adjListGraph.size(); i++){
        visited.push_back(false);
    }
    //  initialize the vertices that need to be visited with the max for an integer
    for(int i = 0; i <= adjListGraph.size(); i++){
        value.push_back(numeric_limits<int>::max());
    }
    //  add the source to the priority queue
    priorityQ.push(make_pair(0, source));
    value[source] = 0;

    //  goes through priority queue until it's empty and all vertices have been added to the MST
    while (!priorityQ.empty()){
        //  gets the vertex at the top of the priority queue
        int currVertex = priorityQ.top().second;
        priorityQ.pop();
        //  checks if the vertex is already in the MST
        if(visited[currVertex] == false){
            //  set the vertex to be in the MST
            visited[currVertex] = true;
            //  iterates through the adjacent vertices of the current vertex
            for(int i = 0; i < adjListGraph[currVertex].size(); i++){
                //  stores the current adjacent vertex
                int adjVertex = adjListGraph[currVertex][i].first;
                //  stores the weight of the current adjacent vertex
                double adjWeight = adjListGraph[currVertex][i].second;
                //  checks if the current adjacent vertex is already in the MST
                if(visited[adjVertex] == false && ((value[adjVertex] > adjWeight))){
                    //  updates the weight value
                    value[adjVertex] = adjWeight;
                    priorityQ.push(make_pair(value[adjVertex], adjVertex));
                    prim[adjVertex] = make_pair(currVertex, adjWeight);
                }
            }
        }
    }
    int start = source;
    int end;
    double sum = 0;
    map<int, pair<int, int>>::iterator iter;
    for(iter = prim.begin(); iter != prim.end(); iter++){
        sum += iter->second.second;
        end = iter->second.first;
    }
    result.push_back(start);
    result.push_back(end);
    result.push_back(sum);
    return result;
}

#endif //MENUMAKER_GRAPH_H
