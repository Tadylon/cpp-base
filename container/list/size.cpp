#include <iostream>
using namespace std;
#include <list>

void printList(const list<int> & List ){
    for (list<int>::const_iterator it = List.begin(); it != List.end() ; it++ ) {
        cout << *it << "  ";
    }
    cout << endl;
}

void test01(){
    list<int>L1;
    L1.push_back(10);
    L1.push_back(500);
    L1.push_back(40);
    L1.push_back(80);
    L1.push_back(100);

    if (!L1.empty()) {
        cout << "L1 isn`t empty" << endl;
        cout << "the size of L1 is : " << L1.size() << endl;
        
    }
    else {
        cout << "L1 is empty " << endl;
    }

    L1.resize(10);
    cout << "the size of L1 is : " << L1.size() << endl;
    printList(L1);

    //重新指定大小
    L1.resize(2);
    cout << "the size of L1 is : " << L1.size() << endl;
    printList(L1);

}

int main(){
    test01();
    system("pause");
    return 0;

}