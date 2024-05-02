
#include<iostream>
#include<pugixml.hpp>
#include <string>
#include<format>

void print_node(int maxdeep, pugi::xml_node node, int deep=0){
    if (deep >= maxdeep) return;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        for(int _=0; _<deep; _++) std::cout << "\t";
        std::string value = child.child_value();
        if (value.length() > 40) {
            value = value.substr(0, 40) + "(생략됨...)";
        }

        std::cout << "[" << child.name() << "] = " << value  <<std::endl;
        print_node(maxdeep, child, deep+1);
    }

}

void print_by_line(pugi::xml_node 회사){
    auto 회사명 =  회사.child("name").child_value();
    auto 노선 = 회사.child("Folder");
    for (; 노선; 노선 = 노선.next_sibling()) {
        auto 노선명 =  노선.child("name").child_value();
        // std::cout << "\t 회사명:" << 노선명 << std::endl;


        auto 역 = 노선.child("Placemark");
        for (; 역; 역 = 역.next_sibling()) {
            // Placemark
            auto 역명 =  역.child("name").child_value();
            auto 좌표 = 역.child("Point").child("coordinates").child_value();
            // std::cout << "\t 역명:" << 역명  << "좌표" << 좌표 << std::endl;

            std::cout << std::format("{},{},{},{}",회사명,노선명,역명,좌표) << std::endl;

            
            // print_node(2,역);
        }
        
        // print_node(8,노선);
    }
}

int main(){
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("data/ROK/metro/KoreaRailroad_Ver2024.04.kml");
    if (!result){
        std::cout << "error to file open" << std::endl;
            return -1;
    }

    // std::cout << "hello" << std::endl;

    auto point = doc.child("kml").child("Document").child("Folder").next_sibling();
    auto 영업시설 = point.child("Folder").child("Folder");//next_sibling();
    // auto ㄱ = point.child("Folder");
    point = point.next_sibling();

    // print_node(8,영업시설);

    auto 기관 = 영업시설.child("Folder");
    for (; 기관; 기관 = 기관.next_sibling()) {
        std::string 기관명 = 기관.child("name").child_value();


        if (기관명 == "국유철도" || 기관명=="공영교통"){
            auto 회사 = 기관.child("Folder");
            for (; 회사; 회사 = 회사.next_sibling()) {
                // auto 회사명 =  회사.child("name").child_value();
                // std::cout << "\t 회사명:" << 회사명 << std::endl;


                print_by_line(회사);


                // print_node(8,회사);
            }
        }else{
            print_by_line(기관);
        }

        


        
    }




    // for (pugi::xml_node child = ROK.first_child(); child; child = child.next_sibling()) {
    //     std::cout << "[" << child.name() << "] = " << child.child_value() <<  "자식:" << child.first_child().child_value() <<std::endl;
    // }



// Document > Folder 
// .children("Tool")
    // for (pugi::xml_node tool: doc.child("Document").child("Folder"))
    // {
    //     int timeout = tool.attribute("Timeout").as_int();
        
    //     if (timeout > 0)
    //         std::cout << "Tool " << tool.attribute("Filename").value() << " has timeout " << timeout << "\n";
    // }



}