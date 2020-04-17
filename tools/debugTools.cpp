//#region debugTools
namespace debugTools{

#ifdef LOCAL
    #include <chrono>

    auto start=std::chrono::high_resolution_clock::now(), stop=std::chrono::high_resolution_clock::now();

    inline void start_timer(){start=std::chrono::high_resolution_clock::now();}
    inline void stop_timer(){stop=std::chrono::high_resolution_clock::now();}
    inline double get_time(){return std::chrono::duration<double>(stop - start).count();}
#else
    #define start_timer()
    #define stop_timer()
    #define get_time()
#endif /*LOCAL*/

inline void local_log(){
    std::cerr << std::endl;
}

template<typename T>
inline void local_log(T t){
    std::cerr << t << std::endl;
}

template<typename T, typename... Args>
inline void local_log(T t, Args... args){
    std::cerr << t << "\t";
    local_log(args...);
}

#ifdef LOCAL
    #define llog(args...) local_log(args)
#else
    #define llog(args...)
#endif /*LOCAL*/

template<typename T>
void local_assert(T t, std::string message){
    if(!t)
        llog(message);
    assert(t);
}

#ifdef LOCAL
    #define lassert(args...) local_assert(args)
#else
    #define lassert(args...)
#endif /*LOCAL*/

} // namespace debugTools
using namespace debugTools;
//#endregion debugTools
