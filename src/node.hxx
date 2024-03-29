#include "service.hxx"
#include <vector>
#include <cmath>

#ifndef NDOE_H
#define NODE_H




struct Coordinate
{
    int latitude; // 위도
    int longitude; // 경도
    /* data */
};

int dist(Coordinate a, Coordinate b);

class Node{
private:
    int nodeId;
    Coordinate cord;
    // struct Service* serviceList;
    /* data */
    std::vector<Service*> serviceList;
    
public:
    bool addService(Service* newService);
    std::vector<Service*>::iterator serviceBegin();
    std::vector<Service*>::iterator serviceEnd();

    Coordinate get_cord() const{
        return cord;
    };

    Node(int id, Coordinate nodeCord): nodeId(id), cord(nodeCord) {}
    ~Node();

    int get_nodeId();
    bool operator() (const Node* a, const Node* b) const{
        return (void*)a < (void *)b;
    }
};

#endif //NODE_H