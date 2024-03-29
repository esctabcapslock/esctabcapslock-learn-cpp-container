#include<algorithm> // for std::find
#include<vector>
#include "runerror.hxx"
#include<optional>
#ifndef SERVICE_H  // 헤더 파일 중복 포함 방지를 위한 전처리 지시문
#define SERVICE_H

// first: 다음역 node, second: 다음역 시간
struct nextNodeInfo{
    int nodeId;
    int time;
};

enum ServiceType{
    Timetable, // 정해신 시간표가 있음
    Periodically, // n시 ~ n시 사이에 5분 간격으로 운행함.
    Immediate, // 즉시 출발
    // VariousTimetable, // 기차같이 최적화 필요한 경우? -> 걍 따른 서버
};


struct ServiceInfo
{
    /* data */
    int serviceId;
    enum ServiceType serviceType;

    // 기타 정보.
};



class Service
{
private:
    /* data */
   
    
public:

    int tableLen;
    int* stopTable; // node id들로 구현되어 있을 것이다.
    int* distTable; 
    int timeTableLen;
    int** timeTable; 
    struct ServiceInfo* serviceinfo;

    // int[] _timeTable;
    Service(int tableLen, int* stopTable, int* distTable,  int timeTableLen, int** timeTable,  ServiceInfo* serviceinfo):
        tableLen(tableLen), stopTable(stopTable), distTable(distTable), timeTableLen(timeTableLen), timeTable(timeTable), serviceinfo(serviceinfo)
        {}

    std::optional<nextNodeInfo>  nextStop(int startNodeId, int startTime);
    // ~Service();
    // void setupTable();
};

#endif