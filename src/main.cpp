#include "ActivityMonitor.hpp"
#include "TUI.hpp"
#include <thread>

int main(int argc, char *argv[]) {

  std::thread th(ActivityMonitor::monitor);
  th.detach();
  TUI::start();

  return 0;
}
