#ifndef MENUMAKER_ALGORITHM_H
#define MENUMAKER_ALGORITHM_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "Graph.h"

using namespace std::chrono;

typedef high_resolution_clock Clock;


class Algorithm {

private:
    Graph graph;
    map<int, string> IPs;
public:
    //  reads in the connections and builds the graph as an adjacency list
    void buildAdjList(ifstream& connections, Graph& graph, map<int, string>& IPs);

    void runKruskal();
    void runPrim();

    int start;
    int end;
    string startIP;
    string endIP;
    int sum;
    int time;

};

void Algorithm::runPrim()
{
    std::ifstream connections("smallConnections.txt");
    buildAdjList(connections, graph, IPs);
    graph.buildEdgeList();

    auto t1 = Clock::now();
    vector<double> primResult = graph.createPrim();
    auto t2 = Clock::now();

    start = primResult[0];
    end = primResult[1];
    startIP = IPs[primResult[0]];
    endIP = IPs[primResult[1]];
    sum = primResult[2];
    time = duration_cast<milliseconds>(t2 - t1).count();
}

void Algorithm::runKruskal()
{
    std::ifstream connections("smallConnections.txt");
    buildAdjList(connections, graph, IPs);
    graph.buildEdgeList();

    auto t1 = Clock::now();
    vector<double> kruskalResult = graph.createKruskal();
    auto t2 = Clock::now();

    start = kruskalResult[0];
    end = kruskalResult[1];
    sum = kruskalResult[2];
    startIP = IPs[kruskalResult[0]];
    endIP = IPs[kruskalResult[1]];
    time = duration_cast<milliseconds>(t2 - t1).count();
}


void Algorithm::buildAdjList(ifstream& connections, Graph& graph, map<int, string>& IPs){
    //  stores the from vertex as a string
    string tempFrom;
    //  stores the from vertex as an int
    int from;
    //  stores the to vertex as a string
    string tempTo;
    //  stores the to vertex as an int
    int to;
    //  stores the edge weight as a string
    string tempWeight;
    //  stores the edge weight as an int
    int weight;
    //  stores the IP address
    string IP;
    //  stores the current index
    int index = 1;
    //  stores a line from the connections file
    string fileLine;
    while(getline(connections, fileLine)) {
        istringstream infoStream(fileLine);
        //  gets the from vertex
        getline(infoStream, tempFrom, '|');
        //  converts the from vertex to an int
        from = stoi(tempFrom);
        //  gets the IP address
        getline(infoStream, IP, '|');
        //  adds the IP address to the map of them
        IPs[index] = IP;
        //  checks if this is a high capacity router
        if(index <= 500){
            for(int i = 1; i <= 16; i++){
                //  gets the to vertex
                getline(infoStream, tempTo, ',');
                //  converts the to vertex to an int
                to = stoi(tempTo);
                //  gets the edge weight
                getline(infoStream, tempWeight, '|');
                //  converts the edge weight to an int
                weight = stoi(tempWeight);
                //  adds the connection to the graph
                graph.addEdge(from, to, weight);
            }
            //  checks if this is a medium capacity router
        } else if((index >= 501) && (index <= 5000)){
            for(int i = 1; i <= 8; i++){
                //  gets the to vertex
                getline(infoStream, tempTo, ',');
                //  converts the to vertex to an int
                to = stoi(tempTo);
                //  gets the edge weight
                getline(infoStream, tempWeight, '|');
                //  converts the edge weight to an int
                weight = stoi(tempWeight);
                //  adds the connection to the graph
                graph.addEdge(from, to, weight);
            }
            //  the router must be low capacity
        } else{
            for(int i = 1; i <= 4; i++){
                //  gets the to vertex
                getline(infoStream, tempTo, ',');
                //  converts the to vertex to an int
                to = stoi(tempTo);
                //  gets the edge weight
                getline(infoStream, tempWeight, '|');
                //  converts the edge weight to an int
                weight = stoi(tempWeight);
                //  adds the connection to the graph
                graph.addEdge(from, to, weight);
            }
        }
        index++;
    }
    return;
}

#endif //MENUMAKER_ALGORITHM_H
