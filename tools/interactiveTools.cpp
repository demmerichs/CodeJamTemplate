//#region interactiveTools

namespace interactiveTools{

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

} // namespace interactiveTools
using namespace interactiveTools;
//#endregion interactiveTools
