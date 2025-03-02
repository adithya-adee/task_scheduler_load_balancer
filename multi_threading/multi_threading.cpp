#include <thread>
#include <iostream>
#include <mutex>
#include <unistd.h>

std::mutex loop_guard;
void loop(int, int);

int main()
{
    std::thread worker1(loop, 0, 1000);
    std::thread worker2(loop, 1000, 2000);
    std::thread worker3(loop, 2000, 3000);
    std::thread worker4(loop, 3000, 4000);

    worker1.join();
    worker2.join();
    worker3.join();
    worker4.join();

    return 0;
}

void loop(int start, int end)
{
    {
        const std::lock_guard<std::mutex> lock(loop_guard);
        pid_t pid = fork();
        std::cout << "thread #" << std::this_thread::get_id() << std::endl;
    }
}