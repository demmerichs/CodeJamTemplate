//#region algoTools
/* TODO write doc
 */
namespace algoTools{

// does an argsort (increasing values) over the provided vector
template <typename T>
std::deque<long long int> argsort(const std::deque<T> &v) {
    // initialize original index locations
    std::deque<long long int> idxs(v.size());
    std::iota(idxs.begin(), idxs.end(), 0);

    // sort indexes based on comparing values in v
    std::sort(idxs.begin(), idxs.end(),
              [&v](long long int i1, long long int i2) {return v[i1] < v[i2];});

    return idxs;
}

// returns the average of 2 values without generating overflow and always rounding down
template <typename T>
T middle(T l, T u){
    T mid = (l/2)+(u/2);
    T r = l%2 + u%2 + 2;
    return mid + r/2 - 1;
}

// for list structures use as function list.operator[] and start = 0
// returns the number of elements which are strict smaller/larger than val
// otherwise returns the smallest index for which f(idx) >=/<= val and start+length if this index does not exist
template <typename T>
long long binSearchDisc(const T &val, const std::function<T (long long)> &f, const unsigned long long &length, const long long &start = 0, bool increasing = true){
    long long l = start - 1;
    long long u = start + length;
    if(increasing){
        while(u>l+1){
            long long mid = middle(l,u);
            if(f(mid)<val)
                l=mid;
            else
                u=mid;
        }
    } else {
        while(u>l+1){
            long long mid = middle(l,u);
            if(f(mid)>val)
                l=mid;
            else
                u=mid;
        }
    }
    return u;
}

} // namespace algoTools
using namespace algoTools;
//#endregion algoTools
