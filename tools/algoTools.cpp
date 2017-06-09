//#region algoTools
/* TODO write doc
 */
namespace algoTools{

// returns the average of 2 values without generating overflow and always rounding down
template <typename T>
T middle(T l, T u){
    T mid = (l/2)+(u/2);
    T r = l%2 + u%2 + 2;
    return mid + r/2 - 1;
}

// returns the number of elements which are strict smaller/larger than val if start = 0
// otherwise returns the smallest index for which f(idx) >/<= val and start+length if this index does not exist
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
