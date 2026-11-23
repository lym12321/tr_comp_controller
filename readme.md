### components::controller

- `controller/pid.h`: 简单 PID 控制器的实现
- `filter/lowpass_filter.h` 的频率参数是模拟 RC 截止频率，单位为 Hz。后向欧拉离散化保留原有调参，数字响应的 −3 dB 频率可低于该值。NaN 或无穷样本返回 NaN，下一次有效样本从上一有效状态继续。
