#pragma once
#include <set>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Node {
    private:
        std::set<int> adjacentNodeIDs;
        bool visited;
        int post_order;

    public:
        void addEdge(int adjacentNodeID) {
            adjacentNodeIDs.insert(adjacentNodeID);
        }

        string toString() {
            stringstream ss;
            for (auto& nodeID : adjacentNodeIDs) {
                ss << "R" << nodeID << ", ";
            }
            string reString = ss.str();
            
        
            if (reString.length() > 0) { 
                reString = reString.substr(0, reString.length() - 2);
            }
            return reString;
        }   
};