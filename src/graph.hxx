
#include "node.hxx"
#include "service.hxx"
#include<vector>
#include<queue>
// #include<unordered_set>
#include<unordered_map>
#include<map>
#include "runerror.hxx"
#include<utility>
#include <algorithm> // for std::fill
#include <climits> // fir int_max
#include<set>
#ifndef GRAPH_H
#define GRAPH_H


// node의 포인터와 그 가중치를 저장합니다.
// typedef std::pair<Node*, int> nodevalue;
struct nodevalue{
    Node* node;
    unsigned int cost; // A*는 cost가 양의 값이여야
    unsigned int time; // 이 시간보다 커야.
};
auto nodevalueCompare = [](const nodevalue* p1, const nodevalue* p2) { return p1->cost < p2->cost; };
// struct nodevalueCompare{
//     bool operator()(const nodevalue &p1, const nodevalue &p2 ){
//         return p1.cost < p2.cost;
//     }
// };

/*
class serviceValue{
    private:
        Service* service;
        
        int idx_start;
        // std::vector<int> timelast; // 가장 빨리 이용할 수 있는 열차 찾기.
    public:
        /\**
         * int starttime: 순환 시작시, 이 시간보다는 뒤의 열차를 이용햐야 할 것. -> 이걸 바탕으로 판단
        *\/
        serviceValue(Service* sv, int nodeId, int starttime);// service(sv), idx_start(nodeId) {};
        // next
        /\*
        class Iterator {
            private:
                int idx; // 이터레이터를 따라하기. -> 동시에, 한 서비스를 다른 노드에서 접근하면 망한다. MT주의!
                serviceValue* sv; // this*를 넣는다.
                
            public:
                Iterator(serviceValue* sv, int idx): sv(sv), idx(idx) {};
                std::pair<int, int> operator*() const; // 각각 nodeID와 새 시간 값을 반환,
                Iterator& operator++();
                bool operator!=(const Iterator& other) const;
        };

        Iterator begin(std::pair<int, int> nv);
        Iterator end (std::pair<int, int>);
        *\/
        
};
*/


// struct routeFindResault{
//     int cost;
//     int dest;
// };
// 다른 옵션은 상속을 통해 결정.

enum Routeoption{
    TimeFirst, // 시간 최적화.
    FeeFirst, // TODO: 요금최적화
    MinTrans // 최소환승
    
};


class Graph{
   

    private:
        std::vector<Service*> serviceList;
        // std::set<Node*> nodeList;
        std::unordered_map<int, Node*> nodeList;

        /**
         * reset all nodes to run dijc
        */
        void init_node();
    public:
        void insert_node(int id, Coordinate cord);
        // Node* find_node(int nodeId);
        void insert_service(Service* service);
        int find_route(int start, int dest, Routeoption routeoption, unsigned int startTime);
};

#endif
