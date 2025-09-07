#include "ActivityMonitor.hpp"
#include <iostream>
#include <iterator>
#include <ncurses.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  std::cout << "Starting program..." << std::endl;

  ActivityMonitor::monitor();

  // initscr();
  // cbreak();
  // noecho();
  // curs_set(0);
  //
  // start_color();
  // init_pair(1, COLOR_CYAN, COLOR_BLACK);
  // for (int i = 10; i >= 0; i --) {
  //   clear();
  //   mvprintw(5, 10, "Focus Time Remaining %d", i);
  //   refresh();
  //   sleep(1);
  // }
  //
  // start_color();
  // init_pair(1, COLOR_CYAN, COLOR_BLACK);
  //
  // attron(COLOR_PAIR(1));
  // box(stdscr, 0, 0);
  // mvprintw(7, 10, "Session complete!");
  // attroff(COLOR_PAIR(1));
  //
  // refresh();
  // getch();
  //
  // endwin();
  return 0;
}
