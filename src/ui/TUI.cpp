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

TUI::TUI(Session session) {
  this->session_ = session;
}

void TUI::start() {

  initscr();
  cbreak();
  noecho();
  curs_set(0);

  start_color();
  use_default_colors();
  init_pair(1, COLOR_RED, -1);

  drawLayout();
  wattron(container, COLOR_PAIR(1));
  thread th(Time::run, this, &session_);
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
    case KEY_RESIZE:
      TUI::drawLayout();
      break;
    }
  }
  endwin();
}

void TUI::drawLayout() {
  wclear(stdscr);
  refresh();

  attron(A_BOLD);
  mvprintw(1, (getWidth() - 5) / 2, "Flipd\n");
  attroff(A_BOLD);
  string title = " " + session_.getSubject().getName();
  mvprintw(2, (getWidth() - utf8::distance(title.begin(), title.end())) / 2,
           "%s", title.c_str());
  refresh();

  if (container == nullptr) {
    container = newwin(5, getWidth(), (getHeight() - 5) / 2, 0);
    wattron(container, COLOR_PAIR(1));
  } else {
    wresize(container, 5, getWidth());
    mvwin(container, (getHeight() - 5) / 2, 0);
  }
  wrefresh(container);
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
