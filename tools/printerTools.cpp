//#region printerTools
/*  <<-operator for deque and pair class
 */
namespace printerTools{

template <typename T>
std::ostream& operator<<(std::ostream& os, std::deque<T> vector);

template <typename S, typename T>
std::ostream& operator<<(std::ostream& os, std::pair<S,T> pa);

template <typename T>
std::ostream& operator<<(std::ostream& os, std::deque<T> vector){
    if(vector.size()==0)
        return os;
    os << vector[0];
    for(unsigned long long i=1;i<vector.size();++i)
        os << ' ' << vector[i];
    return os;
}

template <typename S, typename T>
std::ostream& operator<<(std::ostream& os, std::pair<S,T> pa){
    os << pa.first << ' ' << pa.second;
    return os;
}

} // namespace printerTools
using namespace printerTools;
//#endregion printerTools
