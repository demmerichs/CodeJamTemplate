//#region interactiveTools

namespace interactiveTools{

#ifdef IA_MODE

COMM_TYPE in(){
    COMM_TYPE in_value;
    std::cin >> in_value;
    llog("reading value:", in_value);
    if(in_value == IA_ERROR_CODE){
        exit(0);
    }
    return in_value;
}

template<typename T>
void out(T t){
    llog("sending output:", t);
    std::cout << t << std::endl;
}

template<typename T, typename... Args>
void out(T t, Args... args){
    llog("sending output:", t);
    std::cout << t << std::endl;
    out(args...);
}

#endif /*IA_MODE*/

} // namespace interactiveTools
using namespace interactiveTools;
//#endregion interactiveTools
