#include <map>
#include <cstdint>

// Mapping of keyboard pins to GPIO pins
#define Y0 16
#define Y1 0
#define Y2 1
#define Y3 2
#define Y4 3
#define Y5 4
#define Y6 5
#define Y7 6
#define Y8 7
#define Y9 17 // oops, forgot this one initially

#define X0 8
#define X1 9
#define X2 10
#define X3 11
#define X4 12
#define X5 13
#define X6 14
#define X7 15

#define SHIFT_PIN 18

int xPins[] = { X0, X1, X2, X3, X4, X5, X6, X7 };
int yPins[] = { Y0, Y1, Y2, Y3, Y4, Y5, Y6, Y7, Y8, Y9 };

// Letters to Matrix mapping
typedef struct {
    int8_t x;
    int8_t y;
    bool shift;
} MatrixPosition;

// X-line, Y-line, and shift line
static const std::map<int, MatrixPosition> keyMap = {
    {'A', {X2, Y0, true}},
    {'B', {X3, Y4, true}},
    {'C', {X3, Y2, true}},
    {'D', {X2, Y1, true}},
    {'E', {X1, Y3, true}},
    {'F', {X2, Y4, true}},
    {'G', {X2, Y5, true}},
    {'H', {X2, Y3, true}},
    {'I', {X1, Y8, true}},
    {'J', {X2, Y6, true}},
    {'K', {X2, Y7, true}},
    {'L', {X2, Y9, true}},
    {'M', {X3, Y6, true}},
    {'N', {X3, Y5, true}},
    {'O', {X1, Y9, true}},
    {'P', {X5, Y7, true}},
    {'Q', {X1, Y1, true}},
    {'R', {X1, Y4, true}},
    {'S', {X2, Y2, true}},
    {'T', {X1, Y6, true}},
    {'U', {X1, Y7, true}},
    {'V', {X3, Y3, true}},
    {'W', {X1, Y2, true}},
    {'X', {X3, Y1, true}},
    {'Y', {X1, Y5, true}},
    {'Z', {X3, Y0, true}},
    {' ', {X7, Y1, false}},
    {'\r', {X6, Y6, false}},
    {';', {X2, Y8, false}},
    {':', {X2, Y8, true}},
    {',', {X3, Y7, false}},
    {'<', {X3, Y7, true}},
    {'.', {X3, Y8, false}},
    {'>', {X3, Y8, true}},
    {'/', {X3, Y9, false}},
    {'?', {X3, Y9, true}},
    {'\\', {X4, Y6, false}},
    {'=', {X4, Y7, false}},
    {'-', {X4, Y9, false}},
    {'`', {X5, Y6, false}},
    {'[', {X5, Y8, false}},
    {']', {X5, Y9, false}},
    {'\'', {X6, Y9, false}},
    {'1', {X0, Y1, false}},
    {'2', {X0, Y2, false}},
    {'3', {X0, Y3, false}},
    {'4', {X0, Y4, false}},
    {'6', {X0, Y5, false}},
    {'5', {X0, Y6, false}},
    {'7', {X0, Y7, false}},
    {'8', {X0, Y8, false}},
    {'9', {X0, Y9, false}},
    {'0', {X4, Y8, false}},
    {'!', {X0, Y1, true}},
    {'@', {X0, Y2, true}},
    {'#', {X0, Y3, true}},
    {'$', {X0, Y4, true}},
    {'^', {X0, Y5, true}},
    {'%', {X0, Y6, true}},
    {'&', {X0, Y7, true}},
    {'*', {X0, Y8, true}},
    {'(', {X0, Y9, true}},
    {'|', {X4, Y6, true}},
    {'+', {X4, Y7, true}},
    {')', {X4, Y8, true}},
    {'_', {X4, Y9, true}},
    {'~', {X5, Y6, true}},
    {'{', {X5, Y8, true}},
    {'}', {X5, Y9, true}},
    {'"', {X6, Y9, true}},
    {'\t', {X1, Y0, false}},
    {27, {X0, Y0, false}}, // ESC
    {127, {X7, Y6, false}}, // Backspace -> DEL
    {'↑', {X6, Y7, false}},
    {'↓', {X7, Y7, false}},
    {'→', {X7, Y9, false}},
    {'←', {X7, Y8, false}},
};

