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
        //read input
        task::readInput();
        //calc result
        task::calcFunction();
#ifndef IA_MODE
        //write output
        std::cout << "Case #" << test << ": ";
#ifndef DEFAULT_VAL
        std::cout << result << std::endl;
#endif /*DEFAULT_VAL*/
#ifdef DEFAULT_VAL
        if(result>=0){
            std::cout << result << std::endl;
        }
        else{
            std::string errorWord = ERROR_WORD;
            std::cout << errorWord << std::endl;
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
