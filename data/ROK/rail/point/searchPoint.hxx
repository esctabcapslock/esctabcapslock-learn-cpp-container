#include<iostream>
#include<sstream>
#include <fstream>
#include <string>
#include<vector>
#include<map>
#include <unordered_map>
#include <utility> // std::pair

#ifndef SEARCHPOINT_H
#define SEARCHPOINT_H

// struct stn_into{
//     std::string line;
//     float latitude; // 위도
//     float longitude; // 경도

// };

typedef std::pair<float, float> coord;
// proj 같은거 써야하냐
typedef  std::pair<int,int> coord_custom;

class SearchPoint{
    public:
        SearchPoint();
        const  coord_custom find_by_name(std::string line, std::string stn);
        void set_coord_custom_orig(float lat, float lon){lat_c_orig=lat, lon_c_orig=lon;};
        // coord find_by_id(int id); 이거 하는게 맞음?


    private:
        // std::unordered_map<std::pair<std::string, std::string>, std::pair<float, float>> coord_by_stn;
        float lat_c_orig, lon_c_orig;
        std::map<int, coord> id_to_coord;
        std::map<std::string, int> name_to_id;
        void readFile();
};


#endif