#ifndef SERVER_H
#define SERVER_H

#include<iostream>
#include <queue>
#include <thread>
#include <chrono>
#include <mutex>
#include <future>
#include <unordered_set>
#include <atomic>
#include <vector>
#include <cstdio> 
#include <cstring> 
#include <string> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netdb.h> 
#include <netinet/in.h>	   
#include <netinet/tcp.h> 
#include <unistd.h>
namespace MyServer
{


class thread_pool {
    
private: 
    std::queue<std::pair<std::future<void>, int64_t> > q; // очередь задач - хранит функцию(задачу), которую нужно исполнить и номер данной задачи
    std::mutex q_mtx;
    std::condition_variable q_cv;

    std::unordered_set<int64_t> completed_task_ids;      // помещаем в данный контейнер исполненные задачи
    std::condition_variable completed_task_ids_cv;
    std::mutex completed_task_ids_mtx;

    std::vector<std::thread> threads;


    std::atomic<bool> quite{ false };                    // флаг завершения работы thread_pool
    std::atomic<int64_t> last_idx = 0;                   // переменная хранящая id который будет выдан следующей задаче
public:
    thread_pool(uint32_t num_threads) {
        threads.reserve(num_threads);
        for (uint32_t i = 0; i < num_threads; ++i) {
            threads.emplace_back(&thread_pool::run, this);
        }
    }

    template <typename Func, typename ...Args>
    int64_t add_task(const Func& task_func, Args&&... args) {
        int64_t task_idx = last_idx++;

        std::lock_guard<std::mutex> q_lock(q_mtx);
        q.emplace(std::async(std::launch::deferred, task_func, args...), task_idx);
        q_cv.notify_one();
        return task_idx;
    }

    void wait(int64_t task_id) {
        std::unique_lock<std::mutex> lock(completed_task_ids_mtx);
        completed_task_ids_cv.wait(lock, [this, task_id]()->bool {
            return completed_task_ids.find(task_id) != completed_task_ids.end();
            });
    }

    void wait_all() {
        std::unique_lock<std::mutex> lock(q_mtx);
        completed_task_ids_cv.wait(lock, [this]()->bool {
            std::lock_guard<std::mutex> task_lock(completed_task_ids_mtx);
            return q.empty() && last_idx == completed_task_ids.size();
            });
    }

    bool calculated(int64_t task_id) {
        std::lock_guard<std::mutex> lock(completed_task_ids_mtx);
        if (completed_task_ids.find(task_id) != completed_task_ids.end()) {
            return true;
        }
        return false;
    }

    ~thread_pool() {
        quite = true;
        for (uint32_t i = 0; i < threads.size(); ++i) {
            q_cv.notify_all();
            threads[i].join();
        }
    }

private:

    void run() {
        while (!quite) {
            std::unique_lock<std::mutex> lock(q_mtx);
            q_cv.wait(lock, [this]()->bool { return !q.empty() || quite; });

            if (!q.empty()) {
                auto elem = std::move(q.front());
                q.pop();
                lock.unlock();

                elem.first.get();

                std::lock_guard<std::mutex> lock(completed_task_ids_mtx);
                completed_task_ids.insert(elem.second);

                completed_task_ids_cv.notify_all();
            }
        }
    }
};


struct keepaliveOpt
        {
            int idle;
            int cnt;
            int intvl;
        };


class TcpServer
{
    struct ClientClass
    {
        int newClient;
        struct sockaddr_in new_client_addr;
    };

    private:
        
        int m_serverSocket;
        int m_newClient;
        int m_port;
        int m_buffesSize;
        int m_maxClients;
        int number;
        char m_msg[1024];
        std::string m_ipAddress;
        struct sockaddr_in serv_addr;
        struct sockaddr_in client_addr;
        struct keepaliveOpt m_keepaliveOpt;
            

    public:

        TcpServer();
        TcpServer(int);                 // Constructor
        TcpServer(std::string,int);     // Constructor with param
        ~TcpServer();                   // Destructor
        void init();                    // Initializer
        void fillServAddr();             
        void createSocket();            // Create new socket
        void bindPort();                // Bind to port
        void listenToClients();         // Listen clients
        void acceptClient();            // Set connection with client
        void sendMsg();                 // Send message to client
        std::string receiveMsg();       // Receive message from client
        void messageExchange();         // Regulates the order in which messages are exchanged between the client and the server
        void newThreadForClient();
};
    
}
#endif
