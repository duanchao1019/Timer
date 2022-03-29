# Timer
A simple timer managed by time heap using C++.

包含三个接口：
// 往时间堆中添加一个定时器，在 delay 秒后执行 cb 任务，返回定时器 ID
int AddTimer(int delay, std::function<void()>& cb);
// 根据定时器 ID 删除定时器
void Remove(int id);
// 根据时间来从时间堆中取出定时器执行任务
void Update(int time);

其中删除定时器的操作只是简单地将其 deleted 标记置为 true，在 Update 中检查到 deleted 标记为 true 的定时器不去执行直接删除即可。
