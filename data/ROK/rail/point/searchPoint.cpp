#include "searchPoint.hxx"
#include <stdexcept> // 에러를 위한 헤더
#include<cmath>

// #include <unistd.h>

// std::hash 특수화
// Only for pairs of std::hash-able types for simplicity.
// You can of course template this struct to allow other hash functions
// https://stackoverflow.com/questions/32685540/why-cant-i-compile-an-unordered-map-with-a-pair-as-key
// struct pair_hash {
//     template <class T1, class T2>
//     std::size_t operator () (const std::pair<T1,T2> &p) const {
//         auto h1 = std::hash<T1>{}(p.first);
//         auto h2 = std::hash<T2>{}(p.second);

//         // Mainly for demonstration purposes, i.e. works but is overly simple
//         // In the real world, use sth. like boost.hash_combine
//         return h1 ^ h2;  
//     }
// };


SearchPoint::SearchPoint()  { // : coord_by_stn()
    // coord_by_stn = {};
    // char buffer[FILENAME_MAX];
    // if (getcwd(buffer, FILENAME_MAX) != NULL) {
    //     std::cout << "Current directory: " << buffer << std::endl;
    // } else {
    //     std::cerr << "Error: Unable to get current directory!" << std::endl;
    // }
    lat_c_orig = 0;
    lon_c_orig = 0;



    std::cout << "SearchPoint!!" << std::endl;
    readFile();
}


void SearchPoint::readFile(){
    

    std::ifstream file("data/ROK/rail/point/data_edited.csv"); // 파일 열기

    if (!file.is_open()) {
        std::cerr << "파일을 열 수 없습니다." << std::endl;
        return;
    }

    std::string line;
    std::vector<std::vector<std::string> > data; // 데이터 저장을 위한 벡터
    int row = 0;

    // 한 줄씩 파일을 읽어오면서 처리합니다.
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<std::string> tokens;
        std::string token;

        // 쉼표를 기준으로 문자열을 분할합니다.
        while (std::getline(iss, token, ',')) {
            tokens.push_back(token);
        }

        // data.push_back(tokens); // 분할된 데이터를 벡터에 추가합니다.

        // for (const auto& cell : tokens) {
        //     std::cout << cell << "\t";
        // }
        // std::cout << std::endl;

        if(row){
            
            float latitude =  std::stof(tokens[4]);
            float longitude = std::stof(tokens[3]);
            // info.line = tokens[1];

            id_to_coord[row] = std::make_pair(latitude, longitude);
            name_to_id[tokens[1] + "-" + tokens[2]] = row;
            
            // coord_by_stn.insert(std::make_pair(
            //     std::make_pair(tokens[1], tokens[2]),
            //     std::make_pair(latitude, longitude)
            // ));
        }
        
        row++;

    }

    // 데이터 출력
    // for (const auto& row : data) {
    //     // for (const auto& cell : row) {
    //     //     std::cout << cell << "\t";
    //     // }
    //     std::cout << std::endl;
    // }

    file.close(); // 파일 닫기
}




const std::pair<int,int> SearchPoint::find_by_name(std::string line, std::string stn){
    std::string key = line+"-"+stn;
    auto id = name_to_id.find(key);
    if (id == name_to_id.end()){
        throw std::out_of_range("Key not found in the map (name_to_id)"); // 에러 발생
    }
    auto value = id_to_coord.find(id->second);
    if (value == id_to_coord.end()){
        throw std::out_of_range("Key not found in the map (id_to_coord)"); // 에러 발생
    }
;

    // TODO: PROJ 쓰기
    float lat = value->second.first;
    float lon = value->second.second;
    std::cout << lat << "/" << lat_c_orig << "|" << lon <<  "/" << lon_c_orig << std::endl; 
    int lat_c = (lat-lat_c_orig)*6400000.0*2.0*M_PI/360.0; // m 단위.
    int lon_c = (lon-lon_c_orig)*6400000.0*2.0*M_PI*sin(lat*M_PI/180.0)/360.0; // m 단위.
    


    return std::make_pair(lat_c, lon_c);
}