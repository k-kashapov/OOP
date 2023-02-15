#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "TextView.h"
#include "view.h"

void win_hdlr(int param) {
    (void) param;

    View *curr = View::get();

    curr->WinXY();
    
    fprintf(stderr, 
            "Window size changed!\n"
            "New (x, y) = (%d, %d)\n", 
            curr->_x, curr->_y);
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

void TextView::draw(void) {
    printf("Drawing window of size (%d, %d)\n", _x, _y);

    for (int y = 0; y < _y; y++) {
        // putchar('#');
        printf("%d", y / 10);
        
        for (int x = 1; x < _x - 1; x++) {
            putchar('.');
        }

        // putchar('#');
        printf("%d", y % 10);
    }
}
