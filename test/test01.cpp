// #include "../src/node.h"
// #include "../src/service.h"
#include <iostream>
#include "../src/graph.hxx"
#include "../src/service.hxx"
using namespace std;

int main(){
    cout << "hello world!!, too" << endl;
    FILE* inputFile = fopen("../data/list1.in", "rb");
    Graph* mapweb = new Graph();
    Coordinate cord = {-1, -1};
    int n, id, tableLen;
    fscanf(inputFile, "%d", &n);
    for(int i=0; i<n; i++){
        fscanf(inputFile, "%d%d%d", &id, &(cord.latitude), &(cord.longitude));
        mapweb->insert_node(id, cord);
    }
    fscanf(inputFile, "%d", &n);
    for(int i=0; i<n; i++){
        fscanf(inputFile, "%d%d",&id, &tableLen);
        int* stop_arr = new int(tableLen);
        int* time_arr = new int(tableLen);
        ServiceInfo info;
        info.serviceId = id;
        info.serviceType = ServiceType::Timetable;
        for(int j=0; j<tableLen; j++){
            scanf("%d",stop_arr+j);
        }

        for(int j=0; j<tableLen; j++){
            scanf("%d",time_arr+j);
        }
        Service* input_service = new Service(tableLen, stop_arr, nullptr, 1, &time_arr, &info);
        mapweb->insert_service(input_service);
    }

    
}