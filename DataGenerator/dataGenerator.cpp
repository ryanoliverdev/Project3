#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <chrono>
#include <stdlib.h>
#include <time.h>
using namespace std;
using namespace std::chrono;

//  generates the set of IP addresses
void makeIP(map<int, string>& IPs);
//  writes the IP addresses to a text file
void writeIPFile(map<int, string>& IPs, ofstream& IPFile);
//  creates the connections between IP addresses
void createConnection(map<int, string>& IPs, map<int, vector<pair<int, int>>>& connections, int numHighCap,
                      int highCap, int numMedCap, int medCap, int numLowCap, int lowCap);
//  writes the connections between IP addresses to a text file
void writeConnections(map<int, string>& IPs, map<int, vector<pair<int, int>>>& connections, ofstream& connectionFile);

int main() {
    //  stores the IP addresses of the network
    map<int, string> IPs;
    //  creates the IP addresses of the network
    makeIP(IPs);
    //  stores the number of high capacity routers
    int numHighCap = 5000;
    //  stores how many connections a high capacity router has
    int highCap = 64;
    //  stores the number of medium capacity routers
    int numMedCap = 15000;
    //  stores how many connections a medium capacity router has
    int medCap = 32;
    //  stores the number of low capacity routers
    int numLowCap = 80000;
    //  stores how many connections a low capacity router has
    int lowCap = 16;
    //  stores and opens the IP file
    ofstream IPFile;
    IPFile.open("Project3CSV.txt");
    //  writes all the IP addresses to the IP file
    writeIPFile(IPs, IPFile);
    IPFile.close();
    //  stores the connections between IPs
    map<int, vector<pair<int, int>>> connections;
    createConnection(IPs, connections, numHighCap, highCap, numMedCap, medCap, numLowCap, lowCap);
    //  stores and opens the connection file
    ofstream connectionFile;
    connectionFile.open("Connections.txt");
    //  writes all the connections to the connection file
    writeConnections(IPs, connections, connectionFile);
    connectionFile.close();
    return 0;
}

void makeIP(map<int, string>& IPs){
    srand(time(NULL));
    //  stores the IP address being generated
    string IP;
    //  stores a portion of the IP being generated
    int IPnum = rand() % 255 + 1;
    //  generates 100,000 IP addresses
    for(int i = 1; i <= 100000; i++){
        IP = "";
        for(int j = 0; j < 3; j++){
            IPnum = rand() % 255 + 1;
            IP += to_string(IPnum);
            IP += ".";
        }
        IPnum = rand() % 255 + 1;
        IP += to_string(IPnum);
        //  inserts the IP into the map with an associated index
        IPs[i] = IP;
    }
}

void writeIPFile(map<int, string>& IPs, ofstream& IPFile){
    map<int, string>::iterator iter;
    for(iter = IPs.begin(); iter != IPs.end(); iter++){
        IPFile << iter->second << endl;
    }
}

void createConnection(map<int, string>& IPs, map<int, vector<pair<int, int>>>& connections, int numHighCap,
                      int highCap, int numMedCap, int medCap, int numLowCap, int lowCap){
    srand(time(NULL));
    //  stores the start of the range for the medium capacity
    int medStart = numHighCap + 1;
    //  stores the end of the range for the medium capacity
    int medEnd = numHighCap + numMedCap;
    //  stores the start of the range for the low capacity
    int lowStart = medEnd + 1;
    //  stores the end of the range for the low capacity
    int lowEnd = 100000;
    //  stores the to connection
    int to = rand() % numHighCap + 1;
    //  stores the connection edge weight
    int weight = rand() % 16 + 24;
    //  creates the connections for the high capacity routers
    for(int i = 1; i <= numHighCap; i++){
        for(int j = 0; j < highCap; j++){
            to = rand() % 100000 + 1;
            weight = rand() % 16000 + 24000;
            //  checks if the to connection is the same at the from
            if(i == to){
                //  generates a new to connection
                while(i == to){
                    to = rand() % 100000 + 1;
                }
            }
            //  adds the connection to the map of connections
            connections[i].push_back(make_pair(to, weight));
        }
    }
    //  creates the connections for the medium capacity routers
    for(int i = medStart; i <= medEnd; i++){
        for(int j = 0; j < medCap; j++){
            to = rand() % 100000 + 1;
            weight = rand() % 16000 + 24000;
            //  checks if the to connection is the same at the from
            if(i == to){
                //  generates a new to connection
                while(i == to){
                    to = rand() % 100000 + 1;
                }
            }
            //  adds the connection to the map of connections
            connections[i].push_back(make_pair(to, weight));
        }
    }
    //  creates the connections for the low capacity routers
    for(int i = lowStart; i <= lowEnd; i++){
        for(int j = 0; j < lowCap; j++){
            to = rand() % 100000 + 1;
            weight = rand() % 16000 + 24000;
            //  checks if the to connection is the same at the from
            if(i == to){
                //  generates a new to connection
                while(i == to){
                    to = rand() % 100000 + 1;
                }
            }
            //  adds the connection to the map of connections
            connections[i].push_back(make_pair(to, weight));
        }
    }
}

void writeConnections(map<int, string>& IPs, map<int, vector<pair<int, int>>>& connections, ofstream& connectionFile){
    map<int, vector<pair<int, int>>>::iterator iter;
    for(iter = connections.begin(); iter != connections.end(); iter++){
        connectionFile << iter->first << "|" << IPs[iter->first] << "|";
        //  writes the to connections to the file
        for(int i = 0; i < iter->second.size(); i++){
            connectionFile << iter->second[i].first << "," << iter->second[i].second << "|";
        }
        connectionFile << endl;
    }
}