#include <stdio.h>
#include <stdlib.h>
#include <mach/mach.h>
#include <pthread.h>

mach_port_t exception_port; // 异常端口

// 异常处理线程，监听和处理异常
void* exception_handler_thread(void* arg) {
    while (1) {
        mach_msg_header_t msg;
        kern_return_t kr = mach_msg(&msg, MACH_RCV_MSG, 0, sizeof(msg), exception_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);

        if (kr != KERN_SUCCESS) {
            printf("mach_msg failed: %d\n", kr);
            exit(EXIT_FAILURE);
        }

        printf("Caught EXC_BAD_ACCESS exception!\n");
        // 输出异常相关的详细信息
        printf("Exception message received.\n");
        exit(EXIT_FAILURE);
    }
    return NULL;
}

// 设置异常端口，监听 EXC_BAD_ACCESS 异常
void setup_exception_port() {
    kern_return_t kr;

    // 分配 Mach 端口
    kr = mach_port_allocate(mach_task_self(), MACH_PORT_RIGHT_RECEIVE, &exception_port);
    if (kr != KERN_SUCCESS) {
        printf("Failed to allocate mach port: %d\n", kr);
        exit(EXIT_FAILURE);
    }

    // 插入端口权限
    kr = mach_port_insert_right(mach_task_self(), exception_port, exception_port, MACH_MSG_TYPE_MAKE_SEND);
    if (kr != KERN_SUCCESS) {
        printf("Failed to insert mach port right: %d\n", kr);
        exit(EXIT_FAILURE);
    }

    // 设置异常端口，捕获 EXC_BAD_ACCESS
    kr = task_set_exception_ports(
        mach_task_self(),
        EXC_MASK_BAD_ACCESS,  // 捕获 EXC_BAD_ACCESS 异常
        exception_port,       // 异常端口
        EXCEPTION_DEFAULT,    // 默认异常行为
        x86_THREAD_STATE     // 线程状态类型
    );
    if (kr != KERN_SUCCESS) {
        printf("Failed to set exception ports: %d\n", kr);
        exit(EXIT_FAILURE);
    }

    printf("Exception port set successfully.\n");
}

// 引发 EXC_BAD_ACCESS 异常
void cause_bad_access() {
    int *ptr = NULL;
    *ptr = 42;  // 触发 EXC_BAD_ACCESS
}

int main() {
    // 设置异常端口，监听 EXC_BAD_ACCESS
    setup_exception_port();

    // 创建一个线程来处理异常消息
    pthread_t thread;
    pthread_create(&thread, NULL, exception_handler_thread, NULL);

    // 引发 EXC_BAD_ACCESS 异常
    printf("Causing EXC_BAD_ACCESS...\n");
    cause_bad_access();

    // 等待异常处理线程
    pthread_join(thread, NULL);

    return 0;
}
