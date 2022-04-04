#pragma region main
namespace task{
long long unsigned T;
void init();
void readInput();
void calcFunction();
}

COMM_TYPE result;
int main() {
    std::ios::sync_with_stdio(false);  // don't use scanf when sync turned off -> https://www.geeksforgeeks.org/cincout-vs-scanfprintf/
    std::cerr << std::setprecision(4);
    std::cout << std::setprecision(10);
    task::init();
    for(long long unsigned test=1; test<=task::T; ++test){
        llog();
        llog();
        llog();
        llog();
        llog("################################################");
        llog("################################################");
        llog("################################################");
        llog("################", test, "################");
        llog("################################################");
        llog("################################################");
        llog("################################################");
        llog();
        llog("============      reading input     ============");
        start_timer();
        task::readInput();
        stop_timer();
        llog("-----------", get_time(), "secs -----------");
        llog();
        llog("============    doing computation   ============");
        start_timer();
        task::calcFunction();
        stop_timer();
        llog("-----------", get_time(), "secs -----------");
        llog();
#ifndef IA_MODE
        //write output
        std::cout << "Case #" << test << ": ";
#ifndef DEFAULT_VAL_MODE
        std::cout << result << std::endl;
#else
        if(DEFAULT_VAL_TRIGGER){
            llog("default val triggered");
            std::cout << DEFAULT_VAL << std::endl;
        }
        else{
            llog("default val NOT triggered");
            std::cout << result << std::endl;
        }
#endif /*DEFAULT_VAL_MODE*/
#endif /*IA_MODE*/
    }
    return 0;
}
#pragma endregion main

using namespace std;
#pragma endregion template code

namespace task {

void init(){
    cin >> T;
}

void readInput(){
}

// write to COMM_TYPE result
void calcFunction() {
}

} // namespace task
