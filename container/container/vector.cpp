#include <iostream>
// Include the vector library
#include <vector>

// Include the list library
#include <list>
using namespace std;

int main(){
    vector<int> firstVector = {
        1,2,3,4,5,6,7,8
    };
    vector<int> myVector(5, 10); 

        firstVector.push_back(2);
        int size = firstVector.size();
    
    vector<string> cars = {"Volvo", "BMW", "Ford", "Mazda"};

    // Print vector elements
    for (string car : cars) {
    cout << car << "\n";
    };


    list<string> testdata={"volvo","bwm","ford"};
    for (string data : testdata) {
        cout << data << endl;
    }

    return 0;
}
