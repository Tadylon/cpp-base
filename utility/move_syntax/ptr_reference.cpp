#include <iostream>
#include <string>
#include <memory>

void allocateMemory(int*& ptr) { // 传入指针的引用
    ptr = new int[100];          // 修改外部的指针本身
}

void allocateMemory(std::unique_ptr<int[]>& ptr) { // 传入指针的引用
    ptr = std::make_unique<int[]>(100);          // 修改外部的指针本身
}

int main()
{

    int* p = nullptr;
    allocateMemory(p); // p 现在指向有效的堆内存
    
    //必须手动释放内存
    delete[] p;

    //the second way to fix the ptr
    std::unique_ptr<int[]> arr;
    allocateMemory(arr);
    arr[1] = 4323;

    auto arr1 = std::make_unique<int[]>(232);
    allocateMemory(arr1);
    std::cout << "the size of arr1 is : " << arr1.get() << std::endl;

}