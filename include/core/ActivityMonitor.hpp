#ifndef ACTIVITY_MONITOR_H
#define ACTIVITY_MONITOR_H

class ActivityMonitor {
public:
  ActivityMonitor() = delete;

  static void monitor();

private:
  static bool foreground_;

  static void countdown();
};

#endif // !ACTIVITY_MONITOR_H
