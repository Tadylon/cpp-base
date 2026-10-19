#include <vector>
#include <iostream>
#include <array>


// 声明一个 2行3列 的固定大小二维数组
std::array<std::array<int, 3>, 2> matrix;

// 传参非常自然，直接传引用即可
void print(const std::array<std::array<int, 3>, 2>& mat) {
    
};


// 传参极其优雅，不需要硬编码任何大小
void processVectorMatrix(const std::vector<std::vector<int>>& vec) {
    int rows = vec.size();
    if(rows > 0) {
        int cols = vec[0].size();
    }
}

int main() {
    // 创建一个 3行4列，初始值全为 0 的二维 vector
    std::vector<std::vector<int>> myMatrix(3, std::vector<int>(4, 0));
    
    myMatrix[2][3] = 99; // 正常访问
    processVectorMatrix(myMatrix);
    return 0;
}