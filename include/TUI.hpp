#ifndef TUI_H
#define TUI_H

class TUI {
public:
  TUI() = delete;

  static void start();
  static void refreshTime();
  static int getHeight();
  static int getWidth();

private:
};

#endif // !TUI
