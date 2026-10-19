#include <iostream>
using namespace std;
#include <list>

void printList(const list<int> & List){
    for (list<int>::const_iterator it = List.begin(); it != List.end() ; it++ ) {
        cout << *it << "  ";
    }
    cout << endl;

}

void InsertElement(){
    list<int> L1 ;
    L1.push_back(10);
    L1.push_back(200);
    L1.push_back(300);
    L1.push_back(20);
    L1.push_back(50);

    //insert from front
    L1.push_front(1);
    L1.push_front(2);
    L1.push_front(90);
    
    //print L1
    printList(L1);

    //delete front
    L1.pop_front();
    printList(L1);

    //delete back
    L1.pop_back();
    printList(L1);


    //insert elements
    list<int>::const_iterator it = L1.begin();
    L1.insert(++it,1000);
    printList(L1);

    //delete element
    it = L1.begin();
    L1.erase(++it);
    printList(L1);

    //remove
    L1.push_back(10000);
    L1.push_back(10000);
    L1.push_back(10000);
    L1.push_back(10000);
    printList(L1);
    L1.remove(10000);
    printList(L1);


    //empty elements
    L1.clear();
    printList(L1);

}

int main(){
    InsertElement();
    return 0;
}