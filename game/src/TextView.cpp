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

#define POLL_TIME_MS 50

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

    if (_model) _model->SetXY(_x, _y);

    return 0;
}

void TextView::setCaret(unsigned x, unsigned y) {
    printf("\e[%u;%uH", y + 1, x + 1);
}

void TextView::setColor(int fg, int bg) {
    printf("\e[%d;%dm", 30 + fg, 40 + bg);
}

void TextView::drawPixel(unsigned x, unsigned y, int ch) {
    printf("\e[%u;%uH", y + 1, x + 1);
    putchar(ch);
}

void TextView::vline(unsigned x, unsigned y, unsigned len) {
    for (unsigned i = 0; i <= len; i++) {
        setCaret(x, y + i);
        putchar('|');
    }
}

void TextView::hline(unsigned x, unsigned y, unsigned len) {
    setCaret(x, y);
    for (unsigned i = 0; i <= len; i++) {
        putchar('-');
    }
}

void TextView::setModel(Model* model) {
    _model = model;
    WinXY();
    _model->SetXY(_x, _y);
}

void TextView::draw() {
    clear();
    vline(0,  0, _y);
    vline(_x, 0, _y);

    hline(0,  0, _x - 1);
    hline(0, _y, _x - 2);

    setCaret(_x / 2 - 15, _y / 2);
    printf("Drawing window of size (%u, %u)\n", _x, _y);

    // _model->Update();

    setColor(BRIGHT(COLOR_BLUE), COLOR_BLCK);
    for (coord &curr : _model->rabbits) {
        // std::cerr << "drawing rabbit at (" << curr.first << ", " << curr.second << ")" << std::endl;
        drawPixel(curr.first, curr.second, '#');
    }

    int snk_clr = COLOR_GREN;

    for (Snake& snake : _model->snakes) {
        setColor(COLOR_BLCK, snk_clr);
        snk_clr = (snk_clr + 1) % COLORS_NUM;
        auto curr = snake.body.begin();
        drawPixel(curr->first, curr->second, '@');
        ++curr;

        char pixel = 'a';
        for (; curr != snake.body.end(); curr++) {
            // std::cerr << "drawing snake at (" << curr.first << ", " << curr.second << ")" << std::endl;
            drawPixel(curr->first, curr->second, pixel++);
        }
    }
    setColor(BRIGHT(COLOR_WHIT), COLOR_BLCK);

    setCaret(_x, _y);

    fflush(stdout);
}

void TextView::clear(void) {
    printf("\e[H\e[J");
}

int TextView::getKey() {
    int key_buff[32];

    pollfd fd = {.fd = STDIN_FILENO, .events = POLLIN, .revents = 0};
    int res = poll(&fd, 1, POLL_TIME_MS);
    if (res < 0) {
        std::cerr << "Polling keyboard error!\n" << std::endl;
    } else {
        if (fd.revents & POLLIN) {
            ssize_t len = read(STDIN_FILENO, key_buff, 128);
            // std::cerr << "read = " << (char)key_buff[len - 1] << std::endl;
            return key_buff[len - 1];
        }
    }

    return -1;
}

void TextView::subTimer(const long interval, hndlr func) {
    if (interval <= POLL_TIME_MS) {
        std::cerr << "ERROR: could not subscribe to timer: Interval too small: " << interval << " <= " << POLL_TIME_MS << std::endl;
        return;
    }

    timer_subs.push_back(std::pair<const long, hndlr>(interval - POLL_TIME_MS, func));
    timer_vals.push_back(interval - POLL_TIME_MS);
}

void TextView::tickTimer() {
    const  uint64_t tick      = 1000;
    static uint64_t last_time = 0;
    
    uint64_t new_time  = 0;

    struct timespec tp;
    int res = clock_gettime(CLOCK_REALTIME_COARSE, &tp);
    if (res) {
        fprintf(stderr, "Error getting time!!!\n");
        return;
    }

    new_time = (uint64_t)tp.tv_sec * 1000000 + (uint64_t)tp.tv_nsec / 1000;
    uint64_t diff_ticks = (new_time - last_time) / tick;
    last_time = new_time;

    for (unsigned long iter = 0; iter < timer_vals.size(); iter++) {
        timer_vals[iter] -= (long) diff_ticks;

        if (timer_vals[iter] < 0) {
            timer_vals[iter] = timer_subs[iter].first;
            timer_subs[iter].second();
        }
    }
}

void TextView::loop() {
    bool finish = false;

    while (!finish) {
        tickTimer();
        finish = true;

        for (auto& snake : _model->snakes) {
            if (snake.state == RUNNING) {
                finish = false;
                break;
            }
        }

        char key = (char)getKey();

        if (key > 0) {
            callOnKey(key);
        }

        if (key == 'q')                  finish = true;
        if (_model->rabbits.size() == 0) finish = true;
        draw();
    }

    setCaret(_x / 2 - 30, _y / 2);

    std::cout << "FINISH! Scores: ";

    auto begin = _model->snakes.begin();
    for (unsigned long i = 0; i < _model->snakes.size(); i++) {
        printf("%lu: %d, ", i, (begin++)->score);
    }

    std::cout << "\n\rPress enter to exit!" << std::endl;

    fflush(stdout);
}
