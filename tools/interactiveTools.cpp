#pragma region interactiveTools

namespace interactiveTools{

#ifdef IA_MODE

COMM_TYPE in(){
    COMM_TYPE in_value;
    std::cin >> in_value;
    #ifdef IA_COMM_LOG
    llog("reading value:", in_value);
    #endif /*IA_COMM_LOG*/
    if(in_value == IA_ERROR_CODE){
        exit(0);
    }
    return in_value;
}

template<typename T>
void out(T t){
    #ifdef IA_COMM_LOG
    llog("sending output:", t);
    #endif /*IA_COMM_LOG*/
    std::cout << t << std::endl;
}

template<typename T, typename... Args>
void out(T t, Args... args){
    #ifdef IA_COMM_LOG
    llog("sending output:", t);
    #endif /*IA_COMM_LOG*/
    std::cout << t << std::endl;
    out(args...);
}

#endif /*IA_MODE*/

} // namespace interactiveTools
using namespace interactiveTools;
#pragma endregion interactiveTools
