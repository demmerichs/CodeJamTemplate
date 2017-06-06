/* messageTools
 *
 *  TODO format and edit documentation
     This class provides advanced communication tools
     using range_comm world(#Number of Nodes):
         T reduce(root, value, op = plus)
         T broadcast(root, value)
         T allreduce(value, op = plus)
         vector<T> gather(root, value)
         vector<T> join(root, vector<T> values)
         vector<T> alljoin(vector<T> values)
         T scatter(root, vector<T> values)
         T prefix_sum(&value, op = plus, identity = 0)
         T prefix_sum_arrays(vector<T> &values, op = plus, identity = 0)
         T suffix_sum(&value, op = plus, identity = 0)
         T suffix_sum_arrays(vector<T> &values, op = plus, identity = 0)

 */
//#region messageTools
namespace messageTools{

/*
    This template provides get(source) and put(target,value) for the types:
        char
        int
        long long
        bool
        vector<T>
        array<T,(int) N>
        pair<A,B>
        complex<T>
        tuple<Args...>
*/
template<typename T> class serialize;
//#region serialize
template<>
class serialize<char>
{
public:
    static char get(int source) { return GetChar(source); }
    static void put(int target, char value) { PutChar(target, value); }
};

template<>
class serialize<int>
{
public:
    static int get(int source) { return GetInt(source); }
    static void put(int target, int value) { PutInt(target, value); }
};

template<>
class serialize<long long>
{
public:
    static long long get(int source) { return GetLL(source); }
    static void put(int target, long long value) { PutLL(target, value); }
};

template<>
class serialize<bool>
{
public:
    static bool get(int source) { return GetChar(source); }
    static void put(int target, bool value) { PutChar(target, char(value)); }
};

template<typename T>
class serialize<std::deque<T> >
{
public:
    static std::deque<T> get(int source)
    {
        long long size = GetLL(source);
        std::deque<T> out;
        for (long long i = 0; i < size; i++)
            out.push_back(serialize<T>::get(source));
        return out;
    }

    static void put(int target, const std::deque<T> &value)
    {
        PutLL(target, value.size());
        for (std::size_t i = 0; i < value.size(); i++)
            serialize<T>::put(target, value[i]);
    }
};

template<typename T, std::size_t N>
class serialize<std::array<T, N> >
{
public:
    static std::array<T, N> get(int source)
    {
        std::array<T, N> out;
        for (std::size_t i = 0; i < N; i++)
            out[i] = serialize<T>::get(source);
        return out;
    }

    static void put(int target, const std::array<T, N> &value)
    {
        for (std::size_t i = 0; i < N; i++)
            serialize<T>::put(target, value[i]);
    }
};

template<typename A, typename B>
class serialize<std::pair<A, B> >
{
public:
    static std::pair<A, B> get(int source)
    {
        A a{serialize<A>::get(source)};
        B b{serialize<B>::get(source)};
        return std::make_pair(std::move(a), std::move(b));
    }

    static void put(int target, const std::pair<A, B> &value)
    {
        serialize<A>::put(target, value.first);
        serialize<B>::put(target, value.second);
    }
};

template<typename T>
class serialize<std::complex<T> >
{
public:
    static std::complex<T> get(int source)
    {
        T real = serialize<T>::get(source);
        T imag = serialize<T>::get(source);
        return std::complex<T>(real, imag);
    }

    static void put(int target, const std::complex<T> &value)
    {
        serialize<T>::put(target, value.real());
        serialize<T>::put(target, value.imag());
    }
};

namespace detail
{

template<int P, typename... Args>
class serialize_tuple
{
private:
    typedef typename std::tuple_element<P, std::tuple<Args...> >::type element_type;
public:
    static void get(int source, std::tuple<Args...> &out)
    {
        serialize_tuple<P - 1, Args...>::get(source, out);
        std::get<P>(out) = serialize<element_type>::get(source);
    }

    static void put(int target, const std::tuple<Args...> &value)
    {
        serialize_tuple<P - 1, Args...>::put(target, value);
        serialize<element_type>::put(target, std::get<P>(value));
    }
};

template<typename... Args>
class serialize_tuple<-1, Args...>
{
public:
    static void get(int, std::tuple<Args...> &) {}
    static void put(int, const std::tuple<Args...> &) {}
};

} // namespace detail

template<typename... Args>
class serialize<std::tuple<Args...> >
{
public:
    static std::tuple<Args...> get(int source)
    {
        std::tuple<Args...> out;
        detail::serialize_tuple<int(sizeof...(Args)) - 1, Args...>::get(source, out);
        return out;
    }

    static void put(int target, const std::tuple<Args...> &value)
    {
        detail::serialize_tuple<int(sizeof...(Args)) - 1, Args...>::put(target, value);
    }
};
//#endregion serialize

/*
    simple get and put functions:
        T get(source)
        get(source, Args&...)
        put(target, values...)
    simple send and receive functions:
        T receive(source)
        receive(source, Args&...)
        send(target, values...)
*/
//#region communication
template<typename T>
static T get(int source)
{
    return serialize<T>::get(source);
}

template<typename T>
static void get(int source, T &data)
{
    data = serialize<T>::get(source);
}

template<typename T, typename T2, typename... Rest>
static void get(int source, T &data, T2 &data2, Rest&... rest)
{
    data = serialize<T>::get(source);
    get(source, data2, rest...);
}

template<typename T>
static void put(int target, const T &value)
{
    serialize<T>::put(target, value);
}

template<typename T, typename T2, typename... Rest>
static void put(int target, const T &value, const T2 &value2, const Rest&... rest)
{
    serialize<T>::put(target, value);
    put(target, value2, rest...);
}

template<typename T>
static T receive(int source)
{
    source = Receive(source);
    return get<T>(source);
}

template<typename T, typename... Rest>
static int receive(int source, T &data, Rest&... rest)
{
    source = Receive(source);
    get(source, data, rest...);
    return source;
}

template<typename T, typename... Rest>
static void send(int target, const T &value, const Rest&... rest)
{
    put<T>(target, value, rest...);
    Send(target);
}
//#endregion communication

/*      TODO work on this
    This class provides advanced communication tools
    using range_comm world(#Number of Nodes):
        T reduce(root, value, op = plus)
        T broadcast(root, value)
        T allreduce(value, op = plus)
        vector<T> gather(root, value)
        vector<T> join(root, vector<T> values)
        vector<T> alljoin(vector<T> values)
        T scatter(root, vector<T> values)
        T prefix_sum(&value, op = plus, identity = 0)
        T prefix_sum_arrays(vector<T> &values, op = plus, identity = 0)
        T suffix_sum(&value, op = plus, identity = 0)
        T suffix_sum_arrays(vector<T> &values, op = plus, identity = 0)
*/
//#region range communication
class range_comm{
private:
    int first;
    int last;
    int master;

public:
    explicit range_comm(int last) : first(0), last(last), master(last-1) {}
    range_comm(int first, int last) : first(first), last(last), master(last-1) {}

    void setRange(int p_first, int p_last){
        first = p_first;
        last = p_last;
        master = last - 1;
    }

    void setMaster(int p_master){
        master = p_master;
    }

    bool isMaster() const{
        return MyNodeId() == master;
    }

    int getMaster() const{
        return master;
    }

    template<typename T>
    T reduce(int root, const T &value, const std::function<T (T, T)> &op = std::plus<T>()) const{
        if (MyNodeId() == root){
            T ans = value;
            for (int i = first; i < last; i++)
                if (i != root)
                    ans = op(ans, receive<T>(i));
            return ans;
        } else {
            send(root, value);
            return T();
        }
    }

    template<typename T>
    T reduce(const T &value, const std::function<T (T, T)> &op = std::plus<T>()) const{
        return reduce(master, value, op);
    }

    template<typename T>
    T broadcast(int root, const T &value) const{
        if (MyNodeId() == root){
            for (int i = first; i < last; i++){
                if (i != root)
                    send(i, value);
            }
            return value;
        } else
            return receive<T>(root);
    }

    template<typename T>
    T broadcast(const T &value) const{
        return broadcast(master, value);
    }

    template<typename T>
    T allreduce(const T &value, const std::function<T (T, T)> &op = std::plus<T>()) const{
        T mid = reduce(value, op);
        return broadcast(mid);
    }

    template<typename T>
    std::deque<T> gather(int root, const T &value){
        std::deque<T> ans;
        if (MyNodeId() == root){
            for (int i = first; i < last; i++)
                if (i == root)
                    ans.push_back(value);
                else
                    ans.push_back(receive<T>(i));
        } else
            send(root, value);
        return ans;
    }

    template<typename T>
    std::deque<T> gather(const T &value){
        return gather(master, value);
    }

    template<typename T>
    std::deque<T> allgather(const T &value){
        std::deque<T> ans;
        for (int i = first; i < last; i++){
            if (i != MyNodeId())
                send(i, value);
        }
        for (int i = first; i < last; i++){
            if (i != MyNodeId()){
                ans.push_back(receive<T>(i));
            } else
                ans.push_back(value);
        }
        return ans;
    }

    template<typename T>
    std::deque<T> join(int root, const std::deque<T> &value){
        std::deque<T> ans;
        if (MyNodeId() == root){
            for (int i = first; i < last; i++){
                if (i == root)
                    ans.insert(ans.end(), value.begin(), value.end());
                else {
                    std::deque<T> in;
                    receive(i, in);
                    ans.insert(ans.end(), in.begin(), in.end());
                }
            }
        } else
            send(root, value);
        return ans;
    }

    template<typename T>
    std::deque<T> join(const std::deque<T> &value){
        return join(master, value);
    }

    template<typename T>
    std::deque<T> alljoin(const std::deque<T> &value){
        std::deque<T> ans;
        for (int i = first; i < last; i++){
            if (i != MyNodeId())
                send(i, value);
        }
        for (int i = first; i < last; i++){
            if (i != MyNodeId()){
                std::deque<T> in;
                receive(i, in);
                ans.insert(ans.end(), in.begin(), in.end());
            } else
                ans.insert(ans.end(), value.begin(), value.end());
        }
        return ans;
    }

    template<typename T>
    T scatter(int root, const std::deque<T> &values){
        if (MyNodeId() == root){
            assert(values.size() == size_t(last - first));
            for (int i = first; i < last; i++)
                if (i != root)
                    send(i, values[i - first]);
            return values[root];
        } else {
            return receive<T>(root);
        }
    }

    template<typename T>
    T scatter(const std::deque<T> &values){
        return scatter(master, values);
    }

    // Exclusive in-place prefix sum, returning the overall total
    template<typename T>
    T prefix_reduce(T &value, const std::function<T (T, T)> &op = std::plus<T>(), const T &identity = T()){
        std::deque<T> all = gather(first, value);
        if (MyNodeId() == first){
            T sum = identity;
            for (T &t : all){
                T next = t;
                t = sum;
                sum = op(sum, next);
            }
            for (int i = first + 1; i < last; i++)
                send(i, all[i - first], sum);
            value = identity;
            return sum;
        } else {
            T sum;
            receive(first, value, sum);
            return sum;
        }
    }

    // Exclusive, in-place prefix sum, with each rank contributing a vector
    template<typename T>
    T prefix_reduce_arrays(std::deque<T> &values, const std::function<T (T, T)> &op = std::plus<T>(), const T &identity = T())
    {
        T my_total = accumulate(values.begin(), values.end(), identity, op);
        T total = prefix_sum(my_total, op, identity);
        for (T &t : values)
        {
            T next = t;
            t = my_total;
            my_total = op(my_total, next);
        }
        return total;
    }

    // Exclusive in-place suffix sum, returning the overall total
    template<typename T>
    T suffix_reduce(T &value, const std::function<T (T, T)> &op = std::plus<T>(), const T &identity = T())
    {
        std::deque<T> all = gather(first, value);
        if (MyNodeId() == first)
        {
            T sum = identity;
            for (auto it = all.rbegin(); it != all.rend(); it++)
            {
                T &t = *it;
                T next = t;
                t = sum;
                sum = op(sum, next);
            }
            for (int i = first + 1; i < last; i++)
                send(i, all[i - first], sum);
            value = all[0];
            return sum;
        }
        else
        {
            T sum;
            receive(first, value, sum);
            return sum;
        }
    }

    // Exclusive, in-place prefix sum, with each rank contributing a vector
    template<typename T>
    T suffix_reduce_arrays(std::deque<T> &values, const std::function<T (T, T)> &op = std::plus<T>(), const T &identity = T())
    {
        T my_total = accumulate(values.rbegin(), values.rend(), identity, op);
        T total = suffix_sum(my_total, op, identity);
        for (auto it = values.rbegin(); it != values.rend(); it++)
        {
            T &t = *it;
            T next = t;
            t = my_total;
            my_total = op(my_total, next);
        }
        return total;
    }
};
//#endregion range communication

} // namespace messageTools
using namespace messageTools;
//#endregion messageTools
