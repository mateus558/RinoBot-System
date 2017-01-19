#ifndef SOCCER_WINDOW_H
#define SOCCER_WINDOW_H

#include <QWidget>

namespace Ui {
class soccer_window;
}

class soccer_window : public QWidget
{
    Q_OBJECT

public:
    explicit soccer_window(QWidget *parent = 0);
    ~soccer_window();

private:
    Ui::soccer_window *ui;
};

#endif // SOCCER_WINDOW_H
