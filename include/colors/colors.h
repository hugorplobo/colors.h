#ifndef COLORS_HPP_
#define COLORS_HPP_

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

#if defined(COLORS_USE_WINDOWS_API)
    void wset_attributes(const char* string, int foreground, int background = -1) {
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
            info.wAttributes |= static_cast<WORD>(foreground);
        }

        if (background != -1) {
            info.wAttributes &= ~(info.wAttributes & 0xF0);
            info.wAttributes |= static_cast<WORD>(background);
        }

        SetConsoleTextAttribute(handleTerminal, info.wAttributes);
    }
#endif

void reset() {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[00m");
    #else
        wset_attributes(stream, -1, -1);
    #endif
}

void bold(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[1m%s", string);
    #endif
}

void faint(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[2m%s", string);
    #endif
}

void italic(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[3m%s", string);
    #endif
}

void underline(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[4m%s", string);
    #endif
}

void blink(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[5m%s", string);
    #endif
}

void reverse(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[7m%s", string);
    #endif
}

void invisible(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[8m%s", string);
    #endif
}

void strikethrough(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[9m%s", string);
    #endif
}

void grey(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[30m%s", string);
    #else
        wset_attributes(stream, 0);
    #endif
}

void red(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[31m%s", string);
    #else
        wset_attributes(stream, FOREGROUND_RED);
    #endif
}

void green(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[32m%s", string);
    #else
        wset_attributes(stream, FOREGROUND_GREEN);
    #endif
}

void yellow(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[33m%s", string);
    #else
        wset_attributes(stream, FOREGROUND_RED | FOREGROUND_GREEN);
    #endif
}

void blue(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[34m%s", string);
    #else
        wset_attributes(stream, FOREGROUND_BLUE);
    #endif
}

void magenta(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[35m%s", string);
    #else
        wset_attributes(stream, FOREGROUND_RED | FOREGROUND_BLUE);
    #endif
}

void cyan(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[36m%s", string);
    #else
        wset_attributes(stream, FOREGROUND_BLUE | FOREGROUND_GREEN);
    #endif
}

void white(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[37m%s", string);
    #else
        wset_attributes(stream, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    #endif
}

void bright_grey(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[90m%s", string);
    #else
        wset_attributes(stream, 0 | FOREGROUND_INTENSITY);
    #endif
}

void bright_red(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[91m%s", string);
    #else
        wset_attributes(stream, FOREGROUND_RED | FOREGROUND_INTENSITY);
    #endif
}

void bright_green(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[92m%s", string);
    #else
        wset_attributes(stream, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    #endif
}

void bright_yellow(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[93m%s", string);
    #else
        wset_attributes(stream, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    #endif
}

void bright_blue(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[94m%s", string);
    #else
        wset_attributes(stream, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    #endif
}

void bright_magenta(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[95m%s", string);
    #else
        wset_attributes(stream, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
    #endif
}

void bright_cyan(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[96m%s", string);
    #else
        wset_attributes(stream, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    #endif
}

void bright_white(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[97m%s", string);
    #else
        wset_attributes(stream, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    #endif
}

void on_grey(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[40m%s", string);
    #else
        wset_attributes(stream, -1, 0);
    #endif
}

void on_red(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[41m%s", string);
    #else
        wset_attributes(stream, -1, BACKGROUND_RED);
    #endif
}

void on_green(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[42m%s", string);
    #else
        wset_attributes(stream, -1, BACKGROUND_GREEN);
    #endif
}

void on_yellow(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[43m%s", string);
    #else
        wset_attributes(stream, -1, BACKGROUND_RED | BACKGROUND_GREEN);
    #endif
}

void on_blue(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[44m%s", string);
    #else
        wset_attributes(stream, -1, BACKGROUND_BLUE);
    #endif
}

void on_magenta(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[45m%s", string);
    #else
        wset_attributes(stream, -1, BACKGROUND_RED | BACKGROUND_BLUE);
    #endif
}

void on_cyan(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[46m%s", string);
    #else
        wset_attributes(stream, -1, BACKGROUND_BLUE | BACKGROUND_GREEN);
    #endif
}

void on_white(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[47m%s", string);
    #else
        wset_attributes(stream, -1, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
    #endif
}

void on_bright_grey(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[100m%s", string);
    #else
        wset_attributes(stream, -1, 0 | BACKGROUND_INTENSITY);
    #endif
}

void on_bright_red(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[101m%s", string);
    #else
        wset_attributes(stream, -1, BACKGROUND_RED | BACKGROUND_INTENSITY);
    #endif
}

void on_bright_green(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[102m%s", string);
    #else
        wset_attributes(stream, -1, BACKGROUND_GREEN | BACKGROUND_INTENSITY);
    #endif
}

void on_bright_yellow(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[103m%s", string);
    #else
        wset_attributes(stream, -1, BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
    #endif
}

void on_bright_blue(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[104m%s", string);
    #else
        wset_attributes(stream, -1, BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    #endif
}

void on_bright_magenta(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[105m%s", string);
    #else
            wset_attributes(stream, -1, BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY);
    #endif
}

void on_bright_cyan(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[106m%s", string);
    #else
            wset_attributes(stream, -1, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
    #endif
}

void on_bright_white(const char* string) {
    #if defined(COLORS_USE_ANSI_ESCAPE)
        printf("\033[107m%s", string);
    #else
            wset_attributes(stream, -1, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
    #endif
}

#undef COLORS_TARGET_POSIX
#undef COLORS_TARGET_WINDOWS
#undef COLORS_USE_ANSI_ESCAPE
#undef COLORS_USE_WINDOWS_API

#endif