// math.ixx - Primary Module Interface Unit (PMIU)
export module math; // 声明模块名，并导出此单元的内容

// export 关键字使 add 函数对导入 math 模块的客户端可见
export int add(int a, int b) {
    return a + b;
}