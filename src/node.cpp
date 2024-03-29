#include "node.hxx"


int dist(Coordinate a, Coordinate b)
{
    return sqrt(
        (a.latitude - b.latitude) * (a.latitude - b.latitude) + (a.longitude - b.longitude) * (a.longitude - b.longitude));
}


// bool addService(Service* newService);
bool Node::addService(Service* newService){
    serviceList.push_back(newService);
    return true;
};


std::vector<Service*>::iterator Node::serviceBegin(){
    return serviceList.begin();
};

std::vector<Service*>::iterator Node::serviceEnd(){
    return serviceList.end();
    
};


int Node::get_nodeId(){
    return nodeId;
}