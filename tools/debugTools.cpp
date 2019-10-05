//#region debugTools
namespace debugTools{

template<typename T>
void llog(T t){
#ifdef LOCAL
    std::cerr << t << std::endl;
#endif /*LOCAL*/
    return;
}

template<typename T, typename... Args>
void llog(T t, Args... args){
#ifdef LOCAL
    std::cerr << t << "\t";
    llog(args...);
#endif /*LOCAL*/
    return;
}

template<typename T>
void lassert(T t, std::string message){
#ifdef LOCAL
    if(!t)
        llog(message);
    assert(t);
#endif /*LOCAL*/
    return;
}

} // namespace debugTools
using namespace debugTools;
//#endregion debugTools
