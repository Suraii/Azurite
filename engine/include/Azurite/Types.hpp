#ifndef __AZURITE__INNER__TYPES
#define __AZURITE__INNER__TYPES

#include <concepts>

namespace Azurite {

    struct Vector2D {
        float x = 0;
        float y = 0;
    };

    struct Transform2D {
        Vector2D location = Vector2D{};
        float rotation = 0;
        Vector2D scale = Vector2D{1, 1};
    };

    struct Color {
        unsigned char r = static_cast<unsigned char>(0);
        unsigned char g = static_cast<unsigned char>(0);
        unsigned char b = static_cast<unsigned char>(0);
        unsigned char a = static_cast<unsigned char>(255);
    };

    enum class Input : int {
        UNDEF = -1, A = 0, B, C, D, E, F, G, H, I, J,
        K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        I0, I1, I2, I3, I4, I5, I6, I7, I8, I9, ESC,
        LCTRL, LSHIFT, LALT, LSYS, RCTRL, RSHIFT, RALT, RSYS,
        MENU, LBRACKET, RBRACKET, SEMICOLON, COMMA, PERIOD, QUOTE,
        SLASH, BSLASH, TILDE, EQUAL, HYPHEN, SPACE, ENTER, BSPACE, TAB,
        PUP, PDOWN, END, HOME, INSER, DELETE, ADD, SUBSTRACT, MULTIPLY, DIVIDE,
        ARROW_LEFT, ARROW_RIGHT, ARROW_UP, ARROW_DOWN,
        NP0, NP1, NP2, NP3, NP4, NP5, NP6, NP7, NP8, NP9,
        F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, PAUSE,
        MOUSE1 = 100, MOUSE2 = 101, MOUSE3 = 102, MOUSE4 = 103, MOUSE5 = 104,
        MOUSE_LEFT_CLICK = MOUSE1, MOUSE_RIGHT_CLICK = MOUSE2,
        MOUSE_MIDDLE_CLICK = MOUSE3
    };

    // Utils
    static inline bool isMouse(Input input) {
        return static_cast<int>(input) >= 100;
    }
    static inline bool isKeyboard(Input input) {
        return input != Input::UNDEF && !isMouse(input);
    }
};

#endif
