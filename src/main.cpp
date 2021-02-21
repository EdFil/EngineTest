#include <Engine.hpp>

//#include <logger/Logger.hpp>
//struct TestStruct {
//    int number;
//
//    TestStruct() : number(0) { LOG("Constructor1"); }
//    TestStruct(int _number) : number(_number) { LOG("Constructor2"); }
//    TestStruct(const TestStruct& other) noexcept : number(other.number) { LOG("Copy Constructor"); }
//    TestStruct(TestStruct&& other) noexcept : number(std::move(other.number)) { LOG("Move Constructor"); }
//    ~TestStruct() { LOG("Destructor"); }
//    bool operator==(const TestStruct& rhs) const {
//        LOG("Equals Operator");
//        return number == rhs.number;
//    }
//    TestStruct& operator=(const TestStruct& rhs) {
//        LOG("Copy Operator");
//        number = rhs.number;
//        return *this;
//    }
//    TestStruct& operator=(TestStruct&& rhs) noexcept {
//        LOG("Move Operator");
//        number = rhs.number;
//        return *this;
//    }
//};

int main(int argc, char* argv[]) {
    Engine engine(argc, argv);
    engine.initialize();
    engine.run();
    return 0;
}