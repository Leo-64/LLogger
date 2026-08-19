#include <llogger/llogger.hpp>
#include <thread>
#include <vector>

void workerTask(int id)
{
    LOG_INFO("Thread " + std::to_string(id) + " started working.");
    LOG_WARNING("Thread " + std::to_string(id) + " throws a warning.");
    LOG_TRACE("Thread {0} logs a trace.", id);
    LOG_DEBUG("Thread {0} throws a warning{1}", id, "!");
    std::vector<float> logVec{0.1, -2.3, 5};
    LOG_ERROR("Thread {0} throws error! And logs vector {1}", id, logVec);
    LOG_INFO("Thread {0} logs enum {0}", id, static_cast<int>(LLogger::Level::INFO));
}

int main()
{
    LOG_INFO("LLogger framework started.");
    LOG_ERROR("Simulated error!");

    std::vector<std::thread> threads;
    for (int i = 0; i < 3; ++i)
    {
        threads.emplace_back(workerTask, i);
    }

    for (auto &t : threads)
    {
        t.join();
    }

    LOG_INFO("Program finished.");
    return 0;
}
