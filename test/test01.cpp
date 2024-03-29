// #include "../src/node.h"
// #include "../src/service.h"
#include <iostream>
#include "../src/graph.hxx"
#include "../src/service.hxx"
#include <filesystem>

namespace fs = std::filesystem;

using namespace std;
#ifndef BUILD_DIR_PATH
#define BUILD_DIR_PATH "./"
#endif

int main(){
    cout << "hello world!!, too" << endl;
    // __FILE__
    // fs::path currentPath = fs::current_path();
    fs::path currentPath = BUILD_DIR_PATH;
    // constexpr fs::path currentPath = getCurrentPath();

    // fs::path datapath = currentPath.parent_path() / "data/list1.in";
    fs::path datapath = currentPath / "data/list1.in";


    FILE* inputFile = fopen(datapath.c_str(), "rb");
    if (inputFile == nullptr){
        throw InitException("파일을 읽을 수 없음" + std::string(datapath.c_str()));
    }
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
        int* stop_arr = new int[tableLen];
        int* time_arr = new int[tableLen];
        ServiceInfo* info = new ServiceInfo;
        info->serviceId = id;
        info->serviceType = ServiceType::Timetable;
        for(int j=0; j<tableLen; j++){
            fscanf(inputFile, "%d",stop_arr+j);
        }

        for(int j=0; j<tableLen; j++){
            fscanf(inputFile, "%d",time_arr+j);
        }

        Service* input_service = new Service(tableLen, stop_arr, nullptr, 1, &time_arr, info);
        mapweb->insert_service(input_service);
    }

    mapweb->find_route(1,10,Routeoption::TimeFirst, 0);

    fclose(inputFile);
    delete mapweb;
}