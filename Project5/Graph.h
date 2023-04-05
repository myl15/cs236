#pragma once
#include <map>
#include <string>
#include <sstream>
#include "Node.h"

using namespace std;
class Graph {
    private:

    map<int, Node> nodes;

    public:

        Graph (int size) {
            for (int nodeID = 0; nodeID < size; nodeID++) {
                nodes[nodeID] = Node();
            }
        }
        void addEdge (int fromNodeID, int toNodeID) {
            nodes[fromNodeID].addEdge(toNodeID);
        }

        string toString() {
            stringstream ss;
            for (auto& pair: nodes) {
                int nodeID = pair.first;
                Node node = pair.second;
                ss << "R" << nodeID << ":" << node.toString() << endl;
            }
            return ss.str();

        }
};