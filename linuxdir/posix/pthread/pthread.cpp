#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 线程函数：返回 void*，参数是 void*
void* thread_func(void* arg) {
    int* num = (int*)arg;
    printf("子线程：收到参数 %d\n", *num);
    sleep(1);
    printf("子线程：任务完成\n");
    return NULL;  // 或者 return (void*)某个值
}

int main() {
    pthread_t tid;
    int arg = 42;
    
    // 1. 创建线程
    // 参数：线程ID指针，线程属性（NULL=默认），入口函数，传给线程的参数
    int ret = pthread_create(&tid, NULL, thread_func, &arg);
    if (ret != 0) {
        perror("pthread_create 失败");
        exit(1);
    }
    
    printf("主线程：等待子线程结束...\n");
    
    // 2. 等待线程结束（阻塞）
    void* retval;
    pthread_join(tid, &retval);  // retval 接收线程返回值
    
    printf("主线程：子线程已结束，返回值：%p\n", retval);
    return 0;
}