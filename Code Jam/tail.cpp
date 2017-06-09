//#region main
namespace task{
void init();
void readInput();
void calcFunction();
}

OUT_TYPE result;
int main() {
    task::init();
    std::ofstream outfile("output.txt");
    std::cout << std::setprecision(4);
    outfile << std::setprecision(10);
    long long unsigned tests = 0;
    std::cin >> tests;
    for(long long unsigned test=1; test<=tests; ++test){
        //read input
        task::readInput();
        //calc result
        task::calcFunction();
        //write output
        outfile << "Case #" << test << ": ";
        std::cout << "Case #" << test << ": ";
#ifndef DEFAULT_VAL
        outfile << result << std::endl;
        std::cout << result << std::endl;
#endif /*DEFAULT_VAL*/
#ifdef DEFAULT_VAL
        if(result>=0){
            outfile << result << std::endl;
            std::cout << result << std::endl;
        }
        else{
            std::string errorWord = ERROR_WORD;
            outfile << errorWord << std::endl;
            std::cout << errorWord << std::endl;
        }
#endif /*DEFAULT_VAL*/
    }
    outfile.close();
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

// write to OUT_TYPE result
void calcFunction() {
}

} // namespace task
