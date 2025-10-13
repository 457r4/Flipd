#include "ui/TUI.hpp"
#include "core/Session.hpp"
#include "core/Time.hpp"
#include <ncurses.h>
#include <thread>
#include <unistd.h>
#include <utf8cpp/utf8.h>

using namespace std;

WINDOW *container;
WINDOW *popup;

void TUI::start() {

  initscr();
  cbreak();
  noecho();
  curs_set(0);

  start_color();
  use_default_colors();
  init_pair(1, COLOR_GREEN, -1);

  int height = getHeight();
  int width = getWidth();

  attron(A_BOLD);
  mvprintw(1, (getWidth() - 5) / 2, "Flipd\n");
  attroff(A_BOLD);
  string title = " " + Session::getSubject();
  mvprintw(2, (getWidth() - utf8::distance(title.begin(), title.end())) / 2, "%s", title.c_str());
  refresh();

  container = newwin(5, width, (height - 5) / 2, 0);
  wattron(container, COLOR_PAIR(1));
  thread th(Time::run, Session::getDuration());
  th.detach();

  // popup = newwin(40, 40, 2, 2);
  // box(popup, 0, 0);
  // mvwprintw(popup, 20, 10, "Generic message");
  // wrefresh(popup);

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
  endwin();
}

void TUI::refreshTimeDrawing() {
  for (int i = 0; i < 5; i++) {
    wmove(container, i, 0);
    wclrtoeol(container);
    mvwprintw(container, i, 0, "%s", Time::time_[i].c_str());
  }
  wrefresh(container);
}

int TUI::getHeight() { return getmaxy(stdscr); }

int TUI::getWidth() { return getmaxx(stdscr); }
