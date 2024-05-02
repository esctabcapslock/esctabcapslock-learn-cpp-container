//  이거 바꾸가
// data/ROK/metro/전체_도시철도운행정보_20240331.xlsx
#include<stdio.h>

#include <xlsxio_read.h>
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <format> // 출력용

std::string timeToStr(int time){
    int hour = time/3600;
    int min = (time%3600)/60;
    int sec= time%60;

    return std::format("{:02}:{:02}:{:02}",hour, min, sec);
}




enum colidx{
    열차번호= 0,
    노선번호= 1,
    노선명=2,
    운행구간기점명=3,
    운행구간종점명=4,
    운행유형=5,
    요일구분=6,
    운행구간정거장=7,
    정거장도착시각=8,
    정가장출발시각=9,
    운행속도=10,
    운영기관전화번호=11,
    데이터기준일자=12 
};

// using namespace를 안 쓰겠다는 의지..
typedef std::string string;
typedef int stn_id;

struct serviceInfo{
    std::vector<stn_id> stn_list;
    std::vector<int> start_time;
    std::vector<int> arib_time;

    void printInfo() const {
        std::cout << "Station List:" ;//<< std::endl;
        for (const auto& stn : stn_list)  std::cout << stn << " ";
        std::cout << std::endl;

        std::cout << "Start Time:" ;//<< std::endl;
        for (const auto& time : start_time)  std::cout << timeToStr(time) << " ";
        std::cout << std::endl;

        std::cout << "Arrival Time:" ;//<< std::endl;
        for (const auto& time : arib_time) std::cout << timeToStr(time) << " ";
        
        std::cout << std::endl << std::endl;
    }
};

int main(){
    //open .xlsx file for reading
    // int rowcount = 0;
    int stn_ind_count = 0;
    std::unordered_map<string, int> stnmap; // 역 이름을 저장. 번호로써.
    std::unordered_map<string, serviceInfo> serviceList;
    static const char filename[] = "data/ROK/metro/전체_도시철도운행정보_20240331.xlsx";

    xlsxioreader xlsxioread;
    if ((xlsxioread = xlsxioread_open(filename)) == NULL) {
    fprintf(stderr, "Error opening .xlsx file\n");
    return 1;
    }

    //read values from first sheet
    char* value;
    xlsxioreadersheet sheet;
    const char* sheetname = NULL;
    printf("Contents of first sheet:\n");
    if ((sheet = xlsxioread_sheet_open(xlsxioread, sheetname, XLSXIOREAD_SKIP_EMPTY_ROWS)) != NULL) {
    //read all rows

        
        while (xlsxioread_sheet_next_row(sheet)) {
            //read all columns
            // int colcont = 0;
            std::vector<string> colList;


            

            while ((value = xlsxioread_sheet_next_cell(sheet)) != NULL) {
                // printf("%s\t", value);
                colList.push_back(string(value));
                xlsxioread_free(value);
                // colcont++;
            }
            // printf("\n");
            // std::cout << "노선변호: " << colList[노선번호]  << std::endl;

            if (colList[노선명] == "경강선" && colList[요일구분] == "평일"){
                
                // std::cout << "노선변호: " << colList[노선명]  << std::endl;
                // 그 시간표 형태의 표를 만드는게 중요함.
                

                if (!stnmap.contains(colList[운행구간정거장])){
                    stnmap[colList[운행구간정거장]] = stn_ind_count++;
                }
                // TODO
                // 이부분 잘 만들기. 타노선 동일 역 -> 이거 다른 역으로 구분하되, 맨 마지막에 환승가능 언급해야함.

                int stopId = stnmap[colList[운행구간정거장]];

                if(!serviceList.contains(colList[열차번호])){
                    serviceList[colList[열차번호]] = serviceInfo();
                }
                serviceInfo& sv = serviceList[colList[열차번호]];

                sv.stn_list.push_back(stopId);
                sv.arib_time.push_back((int)(std::stod(colList[정거장도착시각])*24*60*60));
                sv.start_time.push_back((int)(std::stod(colList[정가장출발시각])*24*60*60));

                // std::cout << "colList[열차번호]" << colList[열차번호] << ", 정거장도착시각:" <<  (int)(std::stod(colList[정거장도착시각])*24*60*60) << "시각, 크기:" << sv.arib_time.size() << std::endl;

                // serviceInfo* sv = new serviceInfo();
            }


            // rowcount++;
        }
        xlsxioread_sheet_close(sheet);
    }

    //clean up
    xlsxioread_close(xlsxioread);

    std::cout << "end" << std::endl;
    for (const auto& pair: serviceList){
        std::cout << "Key: " << pair.first << ", Value: " ;
        pair.second.printInfo();
        // /* 여기에 pair.second 출력 */ << std::endl;
    }

    // TODO
    // 이제 이걸 묶자.
    // 서비스단위로 묶은뒤 내보내기 해야함.
    // 노선 상관없이 겹치는거 찾기.
    // 엄 순환선이 문제네. '직통' 설정이 필요한건가.    

    // 생각해보니까 시간표 그거 어차피 일정간격아냐? 걍 간격을 몇 개 저장해 놓고 출발시간만 한뒤 복붙때리면 될 것같은디 그럼 저장형식 읽기코드 또 만들어야하니 미뤄야겠구나.

    // 그리고, 전국 역사 위도/경도 데이터 수집해야함. 어케하지. 그 구글어스 파일 읽기 해야겠노
}