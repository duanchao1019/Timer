# Timer
Simple timer managed by time heap and time wheel using C++.

接口：
- 添加一个定时器，在 delay 秒后执行 cb 任务，返回定时器 ID
- int AddTimer(int delay, std::function<void()>& cb);
- 根据定时器 ID 删除定时器
- void Remove(int id);
