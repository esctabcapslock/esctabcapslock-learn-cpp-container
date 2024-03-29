#include "service.hxx"


// Service::Service(int tableLen, int* stopTable, int* timeTable,  ServiceInfo* dd){
//     _tableLen = tableLen;
//     _stopTable = stopTable;
//     _timeTable = timeTable;


// };


// todo: 다른시간대?
std::optional<nextNodeInfo> Service::nextStop(int startNodeId, int startTime){
    // stopTable;
    int* idx_start = std::find(stopTable, stopTable+tableLen, startNodeId);
    if ( idx_start == stopTable+tableLen) {
        throw InitException("존재하지 않은 nodeID를 넘긴 오류 발생");
    }else if(idx_start == stopTable + tableLen - 1){
        // 마지막 정차역입니다.
        return std::nullopt;
    }
    // int nextNodeIndex = ((ptrdiff_t)(idx_start - stopTable))/sizeof(int) + 1;
    int nextNodeIndex = idx_start - stopTable + 1;

    switch (serviceinfo->serviceType)
    {
    case ServiceType::Immediate:
        return std::optional<nextNodeInfo>({stopTable[nextNodeIndex], *(timeTable)[nextNodeIndex]});
    case ServiceType::Periodically:
        return std::optional<nextNodeInfo>({stopTable[nextNodeIndex], *(timeTable)[nextNodeIndex]});
    case ServiceType::Timetable:
            
            for (int i=0; i<timeTableLen; i++){
                if (timeTable[i][nextNodeIndex] >= startTime){
                    return std::optional<nextNodeInfo>({stopTable[nextNodeIndex], timeTable[i][nextNodeIndex]});
                }
            }
        // 만족하는 열차가 없습니다. 
        return std::nullopt;
    
    default:
        throw InitException("잘못된 ServiceType");;
    }

}