//#region main
namespace task{
void init();
void readInput();
void calcFunction();
}

COMM_TYPE result;
int main() {
    std::cerr << std::setprecision(4);
    std::cout << std::setprecision(10);
    long long unsigned tests = 0;
    std::cin >> tests;
    task::init();
    for(long long unsigned test=1; test<=tests; ++test){
        llog("################", test, "################");
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
            std::cout << DEFAULT_VAL << std::endl;
        }
        else{
            std::cout << result << std::endl;
        }
#endif /*DEFAULT_VAL_MODE*/
#endif /*IA_MODE*/
    }
    return 0;
}
//#endregion main

using namespace std;
//#endregion template code

namespace task {

void init(){
}

void readInput(){
}

// write to COMM_TYPE result
void calcFunction() {
}

} // namespace task
