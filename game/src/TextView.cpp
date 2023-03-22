#include <cstdint>
#include <cstdio>
#include <ctime>
#include <functional>
#include <iostream>
#include <signal.h>
#include <termios.h>
#include <poll.h>
#include <time.h>
#include "TextView.h"
#include "model.h"
#include "view.h"

static void win_hdlr(int param) {
    (void) param;

    View *curr = View::get();
    
    curr->WinXY();
    curr->clear();
}

static termios old;

TextView::TextView() {
    int xy_err = WinXY();
    if (xy_err) {
        fprintf(stderr, "Could not get xy!\n");
    }

    struct sigaction act = {};
    act.sa_handler = win_hdlr;

    sigaction(SIGWINCH, &act, NULL);

    if (tcgetattr(STDIN_FILENO, &old)) {
        std::cerr << "Could not get stdin attributes!\n" << std::endl;
    }

    termios term = old;
    cfmakeraw(&term);
    
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term)) {
        std::cerr << "Could not set stdin attributes to raw!\n" << std::endl;
    }
}

TextView::~TextView() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &old)) {
        std::cerr << "Could not reset stdin attributes to normal!\n" << std::endl;
    }
}

int TextView::WinXY() {
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

void TextView::drawPixel(int x, int y, int ch) {
    printf("\e[%d;%dH", y + 1, x + 1);
    putchar(ch);
}

void TextView::vline(int x, int y, int len) {
    for (int i = 0; i <= len; i++) {
        setCaret(x, y + i);
        putchar('|');
    }
}

void TextView::hline(int x, int y, int len) {
    setCaret(x, y);
    for (int i = 0; i <= len; i++) {
        putchar('-');
    }
}

void TextView::setModel(Model* model) {
    _model = model;
}

void TextView::draw() {
    clear();
    vline(0,  0, _y);
    vline(_x, 0, _y);

    hline(0,  0, _x - 1);
    hline(0, _y, _x - 2);

    setCaret(_x / 2 - 15, _y / 2);
    printf("Drawing window of size (%d, %d)\n", _x, _y);

    _model->Update();
    
    for (coord &curr : _model->rabbits) {
        drawPixel(curr.first, curr.second, '#');
    }

    for (coord &curr : _model->snake.body) {
        drawPixel(curr.first, curr.second, 'S');
    }

    setCaret(_x, _y);

    fflush(stdout);
    usleep(100000);
}

void TextView::clear(void) {
    printf("\e[H\e[J");
}

int TextView::getKey() {
    int key_buff[128];

    pollfd fd = {.fd = STDIN_FILENO, .events = POLLIN, .revents = 0};
    int res = poll(&fd, 1, 100);
    if (res < 0) {
        std::cerr << "Polling keyboard error!\n" << std::endl;
    } else {
        if (fd.revents & POLLIN) {
            int len = read(STDIN_FILENO, key_buff, 128);
            return key_buff[len - 1];
        }
    }

    return -1;
}

void TextView::subTimer(const unsigned interval, hndlr func) {
    timer_subs.push_back(std::pair<const unsigned, hndlr>(interval, func));
    timer_vals.push_back(interval);
}

void TextView::tickTimer() {
    static double last_time = 0;
    double new_time = 0;

    struct timespec tp;
    int res = clock_gettime(CLOCK_REALTIME_COARSE, &tp);
    if (res) {
        fprintf(stderr, "Error getting time!!!\n");
        return;
    }

    
    
    double diff = new_time - last_time;
    for (auto &timer: timer_vals) {
        timer -= diff;
    }

    last_time = new_time;
}

void TextView::loop() {
    bool finish = false;

    while (!finish) {
        tickTimer();

        int key = getKey();
        if (key > 0) {
            callOnKey(key);
        }

        draw();
        if (key == 'q') finish = true;
    }
}
