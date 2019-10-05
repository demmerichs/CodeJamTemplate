//#region printerTools
/*  <<-operator for deque and pair class
 */
namespace printerTools{

template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> iteratable);

template <typename T>
std::ostream& operator<<(std::ostream& os, std::deque<T> iteratable);

template <typename T>
std::ostream& operator<<(std::ostream& os, std::set<T> iteratable);

template <typename T>
std::ostream& operator<<(std::ostream& os, std::unordered_set<T> iteratable);

template <typename S, typename T>
std::ostream& operator<<(std::ostream& os, std::map<S, T> iteratable);

template <typename S, typename T>
std::ostream& operator<<(std::ostream& os, std::unordered_map<S, T> iteratable);

template <typename S, typename T>
std::ostream& operator<<(std::ostream& os, std::pair<S,T> pa);

template <typename T>
std::ostream& _outstream_iteratables(std::ostream& os, T iteratable){
    if(iteratable.begin() == iteratable.end())
        return os;
    os << *iteratable.begin();
    for(auto it = (++iteratable.begin()); it != iteratable.end(); ++it)
        os << ' ' << *it;
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> iteratable){
    return _outstream_iteratables(os, iteratable);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, std::deque<T> iteratable){
    return _outstream_iteratables(os, iteratable);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, std::set<T> iteratable){
    return _outstream_iteratables(os, iteratable);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, std::unordered_set<T> iteratable){
    return _outstream_iteratables(os, iteratable);
}

template <typename S, typename T>
std::ostream& operator<<(std::ostream& os, std::map<S, T> iteratable){
    return _outstream_iteratables(os, iteratable);
}

template <typename S, typename T>
std::ostream& operator<<(std::ostream& os, std::unordered_map<S, T> iteratable){
    return _outstream_iteratables(os, iteratable);
}

template <typename S, typename T>
std::ostream& operator<<(std::ostream& os, std::pair<S,T> pa){
    os << pa.first << ' ' << pa.second;
    return os;
}

} // namespace printerTools
using namespace printerTools;
//#endregion printerTools
