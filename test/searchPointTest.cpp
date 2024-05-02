#include<iostream>
#include<format>
#include "../data/ROK/rail/point/searchPoint.hxx"

int main(){

    SearchPoint find;
    find.set_coord_custom_orig(37, 127 );
    // find 
    auto value =find.find_by_name("경강선", "신판교");

    // std::cout << std::format("({:.20f},{:.20f})", value.first, value.second) << std::endl;
    std::cout << std::format("({},{})", value.first, value.second) << std::endl;

    // 37.2825479128438,      127.628695040081, -> 37.282548, 127.628695, 37°16'57.2"N 127°37'43.3"E
    // 37.28254699707031250000,127.62869262695312500000 -> 37°16'57.2"N 127°37'43.3"E
    // 37.282547,127.62869 -> 37°16'57.2"N 127°37'43.3"E


}