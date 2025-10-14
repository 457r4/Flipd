#ifndef TUI_H
#define TUI_H

#include "core/Session.hpp"
class TUI {
public:
  TUI(Session session);
  ~TUI() = default;

  void start();
  void refreshTimeDrawing();
  int getHeight();
  int getWidth();

private:
  Session session_;
  void drawLayout();
};

#endif // !TUI
