#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "TextView.h"
#include "view.h"

void win_hdlr(int param) {
    (void) param;

    View *curr = View::get();
    
    curr->WinXY();
    curr->clear();

    // fprintf(stderr, 
    //         "Window size changed!\n"
    //         "New (x, y) = (%d, %d)\n", 
    //         curr->_x, curr->_y);
}

TextView::TextView(void) {
    int xy_err = WinXY();
    if (xy_err) {
        fprintf(stderr, "Could not get xy!\n");
    }

    struct sigaction act = {};
    act.sa_handler = win_hdlr;

    sigaction(SIGWINCH, &act, NULL);
}

int TextView::WinXY(void) {
    struct winsize size;
   
    int io_err = ioctl(STDIN_FILENO, TIOCGWINSZ, &size);
    if (io_err) {
        perror("ERROR: ioctl: ");
        return -1;
    }

    _x = size.ws_col;
    _y = size.ws_row;

    return 0;
}

void TextView::setCaret(int x, int y) {
    printf("\e[%d;%dH", y + 1, x + 1);
}

void TextView::vline(int x, int y, int len) {
    for (int i = 0; i <= len; i++) {
        setCaret(x, y + i);
        putchar('$');
    }
}

void TextView::hline(int x, int y, int len) {
    setCaret(x, y);
    for (int i = 0; i <= len; i++) {
        putchar('$');
    }
}

void TextView::draw(void) {
    clear();
    vline(0,  0, _y);
    vline(_x, 0, _y);

    hline(0,  0, _x - 1);
    hline(0, _y, _x - 2);

    setCaret(_x / 2 - 15, _y / 2);
    printf("Drawing window of size (%d, %d)\n", _x, _y);

    fflush(stdout);
    pause();
}

void TextView::clear(void) {
    printf("\e[H\e[J");
}
