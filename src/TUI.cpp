#include "TUI.hpp"
#include "Time.hpp"
#include <ncurses.h>
#include <thread>
#include <unistd.h>
#include <iostream>

using namespace std;

WINDOW *container;
Time *t;

void TUI::start() {

  initscr();
  cbreak();
  noecho();
  curs_set(0);

  start_color();
  use_default_colors();
  init_pair(1, COLOR_GREEN, -1);

  printw("Flipd");
  refresh();

  int height, width;
  getmaxyx(stdscr, height, width);

  container = newwin(5, width, (height - 5) / 2, 0);
  wattron(container, COLOR_PAIR(1));

  t = new Time(21);
  refreshTime();
  thread th(&Time::run, t);
  th.detach();

  int ch;
  bool running = true;

  while (running) {
    ch = getch();
    switch (ch) {
      case 'q':
        running = false;
        break;
    }
  }
  // getch();
  endwin();
}

void TUI::refreshTime() {
  for (int i = 0; i < 5; i++) {
    wmove(container, i, 0);
    wclrtoeol(container);
    mvwprintw(container, i, 0, "%s", t->time[i].c_str());
  }
  wrefresh(container);
}

int TUI::getHeight() { return getmaxy(stdscr); }

int TUI::getWidth() { return getmaxx(stdscr); }
