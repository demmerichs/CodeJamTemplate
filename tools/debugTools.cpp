//#region debugTools
namespace debugTools{

template<typename T>
void log(T t){
#ifdef LOCAL
    std::cerr << t << std::endl;
#endif /*LOCAL*/
    return;
}

template<typename T, typename... Args>
void log(T t, Args... args){
#ifdef LOCAL
    std::cerr << t;
    log(args...);
#endif /*LOCAL*/
    return;
}

template<typename T>
void lassert(T t){
#ifdef LOCAL
    assert(t);
#endif /*LOCAL*/
    return;
}

} // namespace debugTools
using namespace debugTools;
//#endregion debugTools
