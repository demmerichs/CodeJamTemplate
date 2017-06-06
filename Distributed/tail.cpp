//#region main
namespace task{
OUT_TYPE result;
bool init();
void run_node();
messageTools::range_comm w(NumberOfNodes());
int rank, nodes;

int main(){
    rank = MyNodeId();
    nodes = NumberOfNodes();
    if(!init())
        return 0;
    run_node();
    if (w.isMaster()){
#ifndef DEFAULT_VAL
        std::cout << result << std::endl;
#endif /*DEFAULT_VAL*/
#ifdef DEFAULT_VAL
        if(result>=0){
            std::cout << result << std::endl;
        } else{
            std::cout << ERROR_WORD << std::endl;
        }
#endif /*DEFAULT_VAL*/
    }
    return 0;
}
}

int main(){
    return task::main();
}
//#endregion main

using namespace std;

//#endregion template code

namespace task{

ll N, start, end;
bool init(){
    N = GetN();
    if (!partition_work(N, rank, nodes, start, end))
        return false;
    w.setRange(0, nodes);
    return true;
}

// write to OUT_TYPE result
void run_node(){
}

} // namespace task
