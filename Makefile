CC = clang++
CFLAGS = --std=c++2b -Wall -g
# TARGET = my_program
SRC_DIR = src
TEST_DIR = test
BUILD_DIR = build

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



debug: test01
	lldb $(BUILD_DIR)/$<


# clean 규칙: 빌드된 파일 삭제
clean:
	rm -f $(BUILD_DIR)/*.o $(TARGET)
