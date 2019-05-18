//#region main
namespace task{
void init();
void readInput();
void calcFunction();
#ifdef IA_MODE
COMM_TYPE in(){
    COMM_TYPE in_value;
    std::cin >> in_value;
    log("reading value:\t", in_value);
    if(in_value == IA_ERROR_CODE){
        exit(-1);
    }
    return in_value;
}
template<typename T>
void out(T t){
    log("sending output:\t", t);
    std::cout << t << std::endl;
}
template<typename T, typename... Args>
void out(T t, Args... args){
    log("sending output:\t", t);
    std::cout << t << std::endl;
    out(args...);
}
#endif /*IA_MODE*/
}

COMM_TYPE result;
int main() {
    std::cerr << std::setprecision(4);
    std::cout << std::setprecision(10);
    long long unsigned tests = 0;
    std::cin >> tests;
    task::init();
    for(long long unsigned test=1; test<=tests; ++test){
        //read input
        task::readInput();
        //calc result
        task::calcFunction();
#ifndef IA_MODE
        //write output
        std::cout << "Case #" << test << ": ";
        std::cerr << "Case #" << test << ": ";
#ifndef DEFAULT_VAL
        std::cout << result << std::endl;
        std::cerr << result << std::endl;
#endif /*DEFAULT_VAL*/
#ifdef DEFAULT_VAL
        if(result>=0){
            std::cout << result << std::endl;
            std::cerr << result << std::endl;
        }
        else{
            std::string errorWord = ERROR_WORD;
            std::cout << errorWord << std::endl;
            std::cerr << errorWord << std::endl;
        }
#endif /*DEFAULT_VAL*/
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
