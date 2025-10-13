#ifndef TUI_H
#define TUI_H

class TUI {
public:
  TUI() = delete;

  static void start();
  static void refreshTimeDrawing();
  static int getHeight();
  static int getWidth();

private:
  static void drawLayout();
};

#endif // !TUI
