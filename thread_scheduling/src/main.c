#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
//#include <zephyr/logging/log.h>

//LOG_MODULE_REGISTER(thread_scheduling, LOG_LEVEL_INF);  // Register module with INFO level

#define STACK_SIZE 1024
#define PRIORITY_THREAD1 3
#define PRIORITY_THREAD2 7

K_THREAD_STACK_DEFINE(thread1_stack, STACK_SIZE);
K_THREAD_STACK_DEFINE(thread2_stack, STACK_SIZE);

struct k_thread thread1_data;
struct k_thread thread2_data;

void thread1_fn(void *a, void *b, void *c)
{
    while (1) {
        printk(">>> Thread 1 is running\n");
        k_sleep(K_MSEC(2000));
    }
}

void thread2_fn(void *a, void *b, void *c)
{
    while (1) {
        printk(">>> Thread 2 is running\n");
        k_sleep(K_MSEC(2000));
    }
}

void main(void)
{
    printk("Main thread started on ESP32!\n");

    k_thread_create(&thread1_data,                          // Pointer to thread control block (TCB) memory
                    thread1_stack,                          // Pointer to thread's stack memory       
                    K_THREAD_STACK_SIZEOF(thread1_stack),   // Size of stack (bytes)       
                    thread1_fn,                             //Thread entry function (function pointer)                       
                    NULL, NULL, NULL,                       // Parameters to thread1_fn (up to 3)
                    PRIORITY_THREAD1,                       // Thread priority (lower is higher priority)
                    0,                                      // Thread options (flags), 0 = default
                    K_NO_WAIT);                             // Delay before starting thread (0 = start immediately)

    k_thread_create(&thread2_data, thread2_stack,
                    K_THREAD_STACK_SIZEOF(thread2_stack),
                    thread2_fn, 
                    NULL, NULL, NULL,
                    PRIORITY_THREAD2, 0, K_NO_WAIT);
}
