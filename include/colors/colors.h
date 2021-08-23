#ifndef COLORS_H_
#define COLORS_H_

#include <stdio.h>

#if defined(_WIN32) || defined(_WIN64)
#   define COLORS_TARGET_WINDOWS
#elif defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
#   define COLORS_TARGET_POSIX
#endif

#if !defined(COLORS_USE_ANSI_ESCAPE) && !defined(COLORS_USE_WINDOWS_API)
#   if defined(COLORS_TARGET_POSIX)
#       define COLORS_USE_ANSI_ESCAPE
#   elif defined(COLORS_TARGET_WINDOWS)
#       define COLORS_USE_WINDOWS_API
#   endif
#endif

#if defined(COLORS_USE_WINDOWS_API)
#   include <Windows.h>
#endif

#define RESET "\033[00m"
#define BOLD "\033[1m"
#define FAINT "\033[2m"
#define ITALIC "\033[3m"
#define UNDERLINE "\033[4m"
#define BLINK "\033[5m"
#define REVERSE "\033[7m"
#define INVISIBLE "\033[8m"
#define STRIKETHROUGH "\033[9m"

#define GREY "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

#define BRIGHT_GREY "\033[90m"
#define BRIGHT_RED "\033[91m"
#define BRIGHT_GREEN "\033[92m"
#define BRIGHT_YELLOW "\033[93m"
#define BRIGHT_BLUE "\033[94m"
#define BRIGHT_MAGENTA "\033[95m"
#define BRIGHT_CYAN "\033[96m"
#define BRIGHT_WHITE "\033[97m"

#define ON_GREY "\033[40m"
#define ON_RED "\033[41m"
#define ON_GREEN "\033[42m"
#define ON_YELLOW "\033[43m"
#define ON_BLUE "\033[44m"
#define ON_MAGENTA "\033[45m"
#define ON_CYAN "\033[46m"
#define ON_WHITE "\033[47m"

#define ON_BRIGHT_GREY "\033[100m"
#define ON_BRIGHT_RED "\033[101m"
#define ON_BRIGHT_GREEN "\033[102m"
#define ON_BRIGHT_YELLOW "\033[103m"
#define ON_BRIGHT_BLUE "\033[104m"
#define ON_BRIGHT_MAGENTA "\033[105m"
#define ON_BRIGHT_CYAN "\033[106m"
#define ON_BRIGHT_WHITE "\033[107m"


#if defined(COLORS_USE_WINDOWS_API)
    void wset_attributes(int foreground, int background) {
        // some comments because its windows :/

        // for save default attributes of output
        static WORD defaultAttributes = 0;

        // get the terminal handle
        HANDLE handleTerminal = GetStdHandle(STD_OUTPUT_HANDLE);

        // save default attributes
        if (!defaultAttributes) {
            CONSOLE_SCREEN_BUFFER_INFO info;
            if (!GetConsoleScreenBufferInfo(handleTerminal, &info)) return;
            defaultAttributes = info.wAttributes;
        }

        // restore all to the default settings
        if (foreground == -1 && background == -1) {
            SetConsoleTextAttribute(handleTerminal, defaultAttributes);
            return;
        }

        // get the current settings
        CONSOLE_SCREEN_BUFFER_INFO info;
        if (!GetConsoleScreenBufferInfo(handleTerminal, &info)) return;

        if (foreground != -1) {
            info.wAttributes &= ~(info.wAttributes & 0x0F);
            info.wAttributes |= (WORD)foreground;
        }

        if (background != -1) {
            info.wAttributes &= ~(info.wAttributes & 0xF0);
            info.wAttributes |= (WORD)background;
        }

        SetConsoleTextAttribute(handleTerminal, info.wAttributes);
    }
#endif

void reset() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[00m");
    #else
        wset_attributes(-1, -1);
    #endif
}

void bold() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[1m");
    #endif
}

void faint() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[2m");
    #endif
}

void italic() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[3m");
    #endif
}

void underline() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[4m");
    #endif
}

void blink() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[5m");
    #endif
}

void reverse() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[7m");
    #endif
}

void invisible() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[8m");
    #endif
}

void strikethrough() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[9m");
    #endif
}

void grey() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[30m");
    #else
        wset_attributes(0, -1);
    #endif
}

void red() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[31m");
    #else
        wset_attributes(FOREGROUND_RED, -1);
    #endif
}

void green() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[32m");
    #else
        wset_attributes(FOREGROUND_GREEN, -1);
    #endif
}

void yellow() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[33m");
    #else
        wset_attributes(FOREGROUND_RED | FOREGROUND_GREEN, -1);
    #endif
}

void blue() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[34m");
    #else
        wset_attributes(FOREGROUND_BLUE, -1);
    #endif
}

void magenta() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[35m");
    #else
        wset_attributes(FOREGROUND_RED | FOREGROUND_BLUE, -1);
    #endif
}

void cyan() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[36m");
    #else
        wset_attributes(FOREGROUND_BLUE | FOREGROUND_GREEN, -1);
    #endif
}

void white() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[37m");
    #else
        wset_attributes(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, -1);
    #endif
}

void bright_grey() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[90m");
    #else
        wset_attributes(0 | FOREGROUND_INTENSITY, -1);
    #endif
}

void bright_red() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[91m");
    #else
        wset_attributes(FOREGROUND_RED | FOREGROUND_INTENSITY, -1);
    #endif
}

void bright_green() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[92m");
    #else
        wset_attributes(FOREGROUND_GREEN | FOREGROUND_INTENSITY, -1);
    #endif
}

void bright_yellow() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[93m");
    #else
        wset_attributes(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY, -1);
    #endif
}

void bright_blue() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[94m");
    #else
        wset_attributes(FOREGROUND_BLUE | FOREGROUND_INTENSITY, -1);
    #endif
}

void bright_magenta() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[95m");
    #else
        wset_attributes(FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY, -1);
    #endif
}

void bright_cyan() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[96m");
    #else
        wset_attributes(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY, -1);
    #endif
}

void bright_white() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[97m");
    #else
        wset_attributes(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY, -1);
    #endif
}

void color256(int color_code) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[38;5;%d;m", color_code);
    #endif
}

void color_rgb(int r, int g, int b) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[38;2;%d;%d;%dm", r, g, b);
    #endif
}

void on_grey() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[40m");
    #else
        wset_attributes(-1, 0);
    #endif
}

void on_red() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[41m");
    #else
        wset_attributes(-1, BACKGROUND_RED);
    #endif
}

void on_green() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[42m");
    #else
        wset_attributes(-1, BACKGROUND_GREEN);
    #endif
}

void on_yellow() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[43m");
    #else
        wset_attributes(-1, BACKGROUND_RED | BACKGROUND_GREEN);
    #endif
}

void on_blue() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[44m");
    #else
        wset_attributes(-1, BACKGROUND_BLUE);
    #endif
}

void on_magenta() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[45m");
    #else
        wset_attributes(-1, BACKGROUND_RED | BACKGROUND_BLUE);
    #endif
}

void on_cyan() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[46m");
    #else
        wset_attributes(-1, BACKGROUND_BLUE | BACKGROUND_GREEN);
    #endif
}

void on_white() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[47m");
    #else
        wset_attributes(-1, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
    #endif
}

void on_bright_grey() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[100m");
    #else
        wset_attributes(-1, 0 | BACKGROUND_INTENSITY);
    #endif
}

void on_bright_red() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[101m");
    #else
        wset_attributes(-1, BACKGROUND_RED | BACKGROUND_INTENSITY);
    #endif
}

void on_bright_green() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[102m");
    #else
        wset_attributes(-1, BACKGROUND_GREEN | BACKGROUND_INTENSITY);
    #endif
}

void on_bright_yellow() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[103m");
    #else
        wset_attributes(-1, BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
    #endif
}

void on_bright_blue() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[104m");
    #else
        wset_attributes(-1, BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    #endif
}

void on_bright_magenta() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[105m");
    #else
            wset_attributes(-1, BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY);
    #endif
}

void on_bright_cyan() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[106m");
    #else
            wset_attributes(-1, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
    #endif
}

void on_bright_white() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        puts("\033[107m");
    #else
            wset_attributes(-1, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
    #endif
}

void on_color256(int color_code) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[48;5;%d;m", color_code);
    #endif
}

void on_color_rgb(int r, int g, int b) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[48;2;%d;%d;%dm", r, g, b);
    #endif
}

#undef COLORS_TARGET_POSIX
#undef COLORS_TARGET_WINDOWS
#undef COLORS_USE_ANSI_ESCAPE
#undef COLORS_USE_WINDOWS_API

#endif