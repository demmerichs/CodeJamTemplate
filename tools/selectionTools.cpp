//#region selectionTools
/*  SelectionIterator class (abbr. seliter)
 *          iterates over every possible selection of k elements out of the vector
 *      use as following:
 *          for(seliter<T> si(vector,k); !si.final(); ++si) { something with *si }
 *          si.getNotSelected() returns a vector of the n-k not selected elements
 *  getSelection-Function (abbr. gsel)
 *          select from elements, indicated by the ones "1" in the binary representation
 *      use as following:
 *          gsel(vector,binaryRepresentationOfSelection) returns vector
 */
namespace selectionTools{

template <typename T>
class SelectionIterator{
private:
    unsigned long long k;
    unsigned long long n;
    v(T) vector;
    v(T) selection;
    v(unsigned long long) selectionNumbers;
    bool finalState;
public:
    SelectionIterator<T>(v(T) vector, unsigned long long k):k(k), n(vector.size()), vector(vector), finalState(false){
        if(k>n){
            finalState = true;
            return;
        }
        for(unsigned long long i=0;i<k;++i){
            selection.push_back(vector[i]);
            selectionNumbers.push_back(i);
        }
    }

    void operator++(){
        for(unsigned long long i=k-1;i<k;--i){
            if(selectionNumbers[i]==n+i-k)
                continue;
            else{
                ++selectionNumbers[i];
                selection[i]=vector[selectionNumbers[i]];
                for(unsigned long long j=i+1;j<k;++j){
                    selectionNumbers[j]=selectionNumbers[i]+j-i;
                    selection[j]=vector[selectionNumbers[j]];
                }
                return;
            }
        }
        finalState=true;
    }

    v(T) operator*(){
        return selection;
    }

    v(T) getNotSelected(){
        v(T) notSelected;
        unsigned long long cur = 0;
        for(unsigned long long i=0; i<k; ++i){
            for(unsigned long long j=cur; j<selectionNumbers[i]; ++j)
                notSelected.push_back(vector[j]);
            cur = selectionNumbers[i] + 1;
        }
        for(unsigned long long j=cur; j<n; ++j)
            notSelected.push_back(vector[j]);
        return notSelected;
    }

    bool final(){
        return finalState;
    }
};
#define seliter SelectionIterator

template <typename T>
v(T) getSelection(v(T) elements, unsigned long long binaryRepresentationOfSelection){
    v(T) result;
    for(unsigned long long i=0;i<elements.size();++i)
        if( (binaryRepresentationOfSelection>>i)%2 )
            result.push_back(elements[i]);
    return result;
}
#define gsel getSelection

} // namespace selectionTools
using namespace selectionTools;
//#endregion selectionTools
