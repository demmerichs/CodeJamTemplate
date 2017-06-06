/* parallelTools
 *
 *  declares partition_work(items, rank, nodes, start, end)
 *      input: items, rank, nodes
 *      output: if the rank node gets work (true or false)
 *          values: if it gets work, nodes is the total number of nodes that get work, and start inclusive, end exclusive is the range the current node needs to work on
 */
//#region parallelTools
namespace parallelTools{
template<typename T>
bool partition_work(long long items, int rank, int &nodes, T &start, T &end)
{
    if (nodes > items)
        nodes = items;
    start = items * rank / nodes;
    end = items * (rank + 1) / nodes;
    return rank < nodes;
}
} // namespace parallelTools
using namespace parallelTools;
//#endregion parallelTools
