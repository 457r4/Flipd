#include "ActivityMonitor.hpp"
#include "globals.hpp"
#include "utils.hpp"
#include <ctime>
#include <string>
#include <thread>
#include <unistd.h>

using namespace std;

void ActivityMonitor::countdown() {
  system("termux-notification -c 'return, or else...'");
  int i;
  for (i = 15; i > 0 && !foreground_; i--) {
    sleep(1);
  }
  if (i != 0)
    system("termux-notification -c 'you returned :)'");
  else {
    session_active = false;
    system("termux-notification -c 'terminating...'");
  }
}

void ActivityMonitor::monitor() {

  FILE *pipe =
      popen("logcat -v brief -T 1 | grep --line-buffered WindowStopped", "r");
  if (pipe == NULL) {
    log("Error executing logcat");
  }

  char buffer[512];
  while (fgets(buffer, sizeof(buffer), pipe)) {
    string line(buffer);
    if (line.find("true") != string::npos) {
      log("Termux in the background");
      system("termux-vibrate -f");
      foreground_ = false;
      thread th(countdown);
      th.detach();
    } else if (line.find("false") != string::npos) {
      log("Termux in the foreground");
      foreground_ = true;
    } else {
      log("No info about Termux state");
    }
  }

  pclose(pipe);
}
