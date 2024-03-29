#include "graph.hxx"


/*
serviceValue::serviceValue(Service* sv, int nodeId, int starttime){
    service = sv;
    idx_start = -1;
    // todo: 최적화
    for(int i=0; i<sv->tableLen; i++){
        if (nodeId == sv->stopTable[i])
            idx_start = i;
    }
    if (idx_start == -1){
        throw InitException("존재하지 않은 nodeID를 넘긴 오류 발생");
    }
    // idx_start = nodeId;
    timelast.resize(sv->tableLen);
    // std::fill(timelast.begin(), timelast.end(), starttime); 


    


    // if (sv->serviceinfo->serviceType == ServiceType::Timetable){

    //     // 현재 service가 담당하는 모든 node에 대해 갈 수 있는 시간 미리 구하?기 
    // // TODO: lazy로 고쳐야함. 버스 같은거 300개 정거장 미리 구할샘인가? 어라 흠
    // // 오히려 이러면 table로 펼친게 독인가.
    // // 갱 시간표라 의외로 괜찮을수도?
    // // 그니까  안락 -> 충렬사 계산하는데, 모든 ㄷ, 1, 4 역을 계산해버렷.... (10개역 -> 수백개역)
    // // 무시해버려?
    // // 뜯어고치자.


    //     for(int i=0; i<idx_start; i++) timelast[i] = INT_MAX; // 못가는것이다.
    //     int start_service = 0;
    //     for (; start_service<sv->timeTableLen; start_service++){
    //         if (sv->timeTable[start_service][idx_start] > starttime) break;
    //     }

    //     if (start_service < sv->timeTableLen){
    //         for (int i=idx_start; i < sv->tableLen; i++){
    //             if ((sv->timeTable[start_service][i]) > 0){
    //                 timelast[i] = sv->timeTable[start_service][i];
    //             }
    //         }
            
    //     }else{
    //         for (int i=idx_start; i < sv->tableLen; i++){
    //             timelast[i] = INT_MAX;
    //         }
    //     }
    // }
    
}

// serviceValue::Iterator::
std::pair<int,int> serviceValue::Iterator::operator*() const{
    switch (sv->service->serviceinfo->serviceType) {
        case ServiceType::Immediate:
             return std::make_pair(**(sv->service->timeTable), 1);
        case ServiceType::Periodically:
            return std::make_pair(**(sv->service->timeTable), 1);
        case ServiceType::Timetable:

            /\*
                - 여기에 설정하기.
                - ptr마다 순환
            *\/
    };
};

// Iterator& operator++();
serviceValue::Iterator& serviceValue::Iterator::operator++(){
    switch (sv->service->serviceinfo->serviceType) {
        case ServiceType::Timetable:
                idx = (idx + 1) % sv->service->tableLen;
           break;
    };

    return *this;
};

// Iterator begin(std::pair<int, int> nv);

serviceValue::Iterator serviceValue::begin(std::pair<int, int> nv){

}



// bool operator!=(const Iterator& other) const;

bool serviceValue::Iterator::operator!=(const Iterator& other) const{
    return other.idx != idx;
};

*/

void Graph::init_node(){
    // 큐 초기화. - 큐 관리 변경 - 필요x
    // std::priority_queue<nodevalue, std::vector<nodevalue>, nodevalueCompare> newQueue;
    // visitQueue = newQueue;
};

void Graph::insert_node(int id, Coordinate cord)
{
    Node *stop = new Node(id, cord);
    nodeList[id] = stop; // insert
};

void Graph::insert_service(Service *svc)
{

    // 입력된 서비스의 유효성 확인
    for (int i = 0; i < svc->tableLen; i++)
    {
        int nodeID = svc->stopTable[i];
        // std::map<int, Node*, std::less> abcde;
        if (!nodeList.contains(nodeID))
        {
            throw InitException("정의되지 않는 node를 포함하는 service");
        }
    }

    serviceList.push_back(svc);
};

int Graph::find_route(int start, int dest, Routeoption *routeoption)
{

    // 우선 초기화
    init_node();
    Node *st = nodeList[start];
    Node *fn = nodeList[dest];
    nodevalue p = {st, 0};
    nodevalue *pp = &p;

    std::unordered_map<Node *, nodevalue *> visitList; // 검색
    // std::unordered_set<Node*> visitSet; // 검색
    // std::set<nodevalue *, std::vector<nodevalue *>, nodevalueCompare> priorityQueue; // 삭제.
    std::set<nodevalue *,  decltype(nodevalueCompare)> priorityQueue; // 삭제.

    while (true)
    {
        for (auto sv = pp->node->serviceBegin(); sv != pp->node->serviceEnd(); sv++){
            // startNodeId, int startTime
            std::optional<nextNodeInfo> opt_nodeinfo = sv[0]->nextStop(pp->node->get_nodeId(), pp->cost);
            if(!opt_nodeinfo.has_value()) continue;

            nextNodeInfo nodeinfo = opt_nodeinfo.value();
            Node* nextNode = nodeList[nodeinfo.nodeId];
            
            // item- > node 연결된 노드
            // item -> vertexvalue 간선가중치
            // nodevalue*
            // unsigned int newweight = item->vertexvalue + p.cost + dist(fn->get_cord(), item->node->get_cord()) - dist(fn->get_cord(), pp->node->get_cord());
            unsigned int newweight = p.cost + dist(fn->get_cord(), nextNode->get_cord()) - dist(fn->get_cord(), pp->node->get_cord());

            nodevalue* item = visitList[nextNode];
            if (item == nullptr){
                item = new nodevalue();
                visitList[nextNode] = item;
                item->node = nextNode;
                item->cost = newweight;
            }

            if (priorityQueue.contains(item)){ // 우선순위 큐 OK
                if (item->cost > newweight) { // 그리고 더 짧은 경우
                    item->cost = newweight; // 갱신
                }
            }
            else if (!visitList.contains(item->node)){ // 큐에 없고 방문한적 없음
                // 할당
                nodevalue *p = new nodevalue();
                p->node = item->node;
                p->cost = newweight;

                // priorityQueue[item->node].cost = p; // 역시 큐에 삽빕
                priorityQueue.insert(p);
            }
        }

        // 가장 작은 값 가져오기
        auto minv = priorityQueue.begin();
        if (minv == priorityQueue.end()){ // 빔
            return -1;

        }else{
            pp = (*minv);
        }
    }

    // TODO: 할당 삭제 코드.
    for (auto it : visitList){
        if (it.second != pp){
            delete it.second;
        }
    }
    visitList.clear();
    priorityQueue.clear();
}