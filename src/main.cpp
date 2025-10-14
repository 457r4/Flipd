#include "core/ActivityMonitor.hpp"
#include "data/Database.hpp"
#include "core/Session.hpp"
#include "libs/cxxopts.hpp"
#include "ui/TUI.hpp"
#include <iostream>
#include <thread>

using namespace std;

int main(int argc, char *argv[]) {

  cxxopts::Options options("Flipd", "Improve your study habits");
  options.add_options()("h,help", "Print this message")(
      "add", "Add a new subject", cxxopts::value<string>())(
      "under", "Link a subject to a semester (must be used with add)",
      cxxopts::value<string>())("subject", "Subject name",
                                     cxxopts::value<string>())(
      "duration", "Study session duration in minutes", cxxopts::value<int>())(
      "color", "Give a color to the subject", cxxopts::value<string>());
  options.parse_positional({"subject", "duration"});

  auto result = options.parse(argc, argv);

  if (result.count("help")) {
    cout << options.help() << endl;
    return 0;
  }

  if (!result.count("subject")) {
    cout << "Cannot start" << endl;
    return 1;
  } else {
    Session::setSubject(result["subject"].as<string>());
  }
  if (result.count("duration")) {
    Session::setDuration(result["duration"].as<int>());
  }

  Database::open();

  thread th(ActivityMonitor::monitor);
  th.detach();
  TUI::start();

  return 0;
}
