#include <iostream>
#include <cstdlib>
#include <cstring>
#include <zlib.h> // 成功链接后可直接包含
#include <zconf.h>

int main() {
    // 打印当前链接的 zlib 库版本
    std::cout << "ZLIB Version: " << zlibVersion() << std::endl;

    // 测试简单的 CRC32 计算函数
    const char* data = "Hello, CMake and ZLIB!";
    uLong crc = crc32(0L, Z_NULL, 0);
    crc = crc32(crc, reinterpret_cast<const Bytef*>(data), strlen(data));

    std::cout << "Data CRC32: " << std::hex << crc << std::endl;

    return 0;
}

