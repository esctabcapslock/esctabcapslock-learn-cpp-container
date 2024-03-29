#include "node.hxx"

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
