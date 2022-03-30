#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <thread>
#include <functional>
using namespace std;

typedef std::function<void()> Func;

class Timer
{
public:
    Timer(int id, int rotation, int slot, Func& cb)
        : _id(id)
        , _rotation(rotation)
        , _slot(slot)
        , _cb(cb)
    {

    }

    ~Timer()
    {

    }

    int _id;
    int _rotation;
    int _slot;
    Func _cb;
};


class TimeWheel
{
public:
    TimeWheel(int slots, int slot_interval)
        : _slots(slots)
        , _slot_interval(slot_interval)
    {
        _time_wheel.resize(_slots);
    }

    ~TimeWheel()
    {
        for (int i = 0; i < _slots; i++)
        {
            while (!_time_wheel[i].empty())
            {
                Timer* timer = *_time_wheel[i].begin();
                _time_wheel[i].pop_front();
                mp.erase(timer->_id);
                delete timer;
            }
        }
    }

    void Start()
    {
        _thread = thread([&]() {
            while (true)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(_slot_interval));
                Tick();
            }
            });
        _thread.detach();
    }

    int AddTimer(int delay, Func& cb)
    {
        int rotation = delay / (_slots * _slot_interval);
        int slot = (_curr_slot + (delay / _slot_interval) % _slots) % _slots;
        _time_wheel[slot].push_front(new Timer(++timer_id, rotation, slot, cb));
        mp[timer_id] = _time_wheel[slot].begin();
        return timer_id;
    }

    void Remove(int id)
    {
        if (mp.count(id))
        {
            auto it = mp[id];
            _time_wheel[(*it)->_slot].erase(it);
            mp.erase(id);
        }
    }

    void Tick()
    {
        for (auto it = _time_wheel[_curr_slot].begin(); it != _time_wheel[_curr_slot].end(); )
        {
            Timer* timer = *it;
            if (timer->_rotation > 0)
            {
                ++it;
                continue;
            }
            timer->_cb();
            it = _time_wheel[_curr_slot].erase(it);
            mp.erase(timer->_id);
            delete timer;
        }
        _curr_slot = (_curr_slot + 1) % _slots;
    }

private:
    static int timer_id;
    unordered_map<int, list<Timer*>::iterator> mp;
    vector<list<Timer*>> _time_wheel;  // 时间轮
    int _slots;  // 槽数
    int _slot_interval;  // 槽间隔
    int _curr_slot;   // 当前槽
    thread _thread;
};

int TimeWheel::timer_id = 0;


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
    TimeWheel time_wheel(60, 1000);

    Func cb1 = work1;
    Func cb2 = work2;
    Func cb3 = work3;

    time_wheel.Start();

    int id1 = time_wheel.AddTimer(5000, cb1);
    int id2 = time_wheel.AddTimer(10000, cb2);
    int id3 = time_wheel.AddTimer(15000, cb3);

    time_wheel.Remove(id2);

    std::this_thread::sleep_for(std::chrono::seconds(100));

    return 0;
}
