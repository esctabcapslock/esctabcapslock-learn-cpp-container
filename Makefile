CC = clang++
CFLAGS = --std=c++2b -Wall -g -O0
# TARGET = my_program
SRC_DIR = src
TEST_DIR = test
BUILD_DIR = build
LIBDIRS = vcpkg/installed/arm64-osx/debug/lib
LIBS = xlsxio_read xlsxio_write expat minizip bz2 z
INCLUDES = 	-Ivcpkg/installed/arm64-osx/include


# 현재 빌드 디렉토리의 절대 경로를 가져오는 명령어
BUILD_DIR_ABSOLUTE_PATH := $(abspath $(CURDIR))
# C++ 컴파일러에 절대 경로를 전달하기 위해 변수를 정의
CFLAGS += -DBUILD_DIR_PATH=\"$(BUILD_DIR_ABSOLUTE_PATH)\"


# 소스 파일과 객체 파일 목록
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))



# 빌드 폴더 생성 규칙
$(BUILD_DIR):
	mkdir -p $@


# 객체 파일 빌드 규칙
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<



test01: $(TEST_DIR)/test01.cpp $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $(BUILD_DIR)/$@

testxlsx: data/ROK/metro/toTest1Format.cpp
	$(CC) $(CFLAGS) $(INCLUDES)  $(foreach LIBDIR,$(LIBDIRS),-L$(LIBDIR)) $(foreach LIB,$(LIBS),-l$(LIB)) $^ -o $(BUILD_DIR)/$@ 
	



debug: test01
	lldb $(BUILD_DIR)/$<


# clean 규칙: 빌드된 파일 삭제
clean:
	rm -f $(BUILD_DIR)/*.o $(TARGET)
