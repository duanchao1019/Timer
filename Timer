#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <unordered_map>
#include <functional>
using namespace std;


class Timer
{
public:
    Timer(int _id, int _expire, std::function<void()>& _cb)
        : id(_id)
        , expire(_expire)
        , deleted(false)
        , cb(_cb)
    {

    }

    ~Timer()
    {

    }

    bool operator < (const Timer& other)
    {
        return expire < other.expire;
    }

    int id;
    int expire;
    bool deleted;
    std::function<void()> cb;
};


class TimeHeap
{
public:

    int AddTimer(int delay, std::function<void()>& cb)
    {
        int expire = (int)time(nullptr) + delay;
        Timer* timer = new Timer(++timer_id, expire, cb);
        time_heap.push(timer);
        mp[timer_id] = timer;
        return timer_id;
    }

    void Remove(int id)
    {
        mp[id]->deleted = true;
    }

    void Update(int time)
    {
        while (true)
        {
            if (time_heap.empty())
            {
                break;
            }

            Timer* timer = time_heap.top();
            if (timer->expire > time)
            {
                break;
            }
            time_heap.pop();
            if (!timer->deleted)
            {
                timer->cb();
            }
            delete timer;
        }
    }

private:
    static int timer_id;
    priority_queue<Timer*, vector<Timer*>, greater<Timer*>> time_heap;
    unordered_map<int, Timer*> mp;
};

int TimeHeap::timer_id = 0;

void work1()
{
    cout << "I'm work1" << endl;
    return;
}

void work2()
{
    cout << "I'm work2" << endl;
    return;
}

void work3()
{
    cout << "I'm work3" << endl;
    return;
}

int main()
{
    TimeHeap time_heap;

    std::function<void()> cb1 = work1;
    std::function<void()> cb2 = work2;
    std::function<void()> cb3 = work3;

    int id1 = time_heap.AddTimer(5, cb1);
    int id2 = time_heap.AddTimer(10, cb2);
    int id3 = time_heap.AddTimer(15, cb3);

    time_heap.Remove(id2);

    while (true)
    {
        time_heap.Update((int)time(nullptr));
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}
