#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"

#include "keyboard_matrix.h"
#include <ctype.h>

#define LED_PIN 25

int main() {

      bi_decl(bi_program_description("Apple 2e keyboard emulator"));
      bi_decl(bi_1pin_with_name(LED_PIN, "On-board LED"));

      bi_decl(bi_1pin_with_name(Y0, "Keyboard Y0 (pin 1)"));
      bi_decl(bi_1pin_with_name(Y1, "Keyboard Y1 (pin 2)"));
      bi_decl(bi_1pin_with_name(Y2, "Keyboard Y2 (pin 4)"));
      bi_decl(bi_1pin_with_name(Y3, "Keyboard Y3 (pin 6)"));
      bi_decl(bi_1pin_with_name(Y4, "Keyboard Y4 (pin 8)"));
      bi_decl(bi_1pin_with_name(Y5, "Keyboard Y5 (pin 10)"));
      bi_decl(bi_1pin_with_name(Y6, "Keyboard Y6 (pin 23)"));
      bi_decl(bi_1pin_with_name(Y7, "Keyboard Y7 (pin 25)"));
      bi_decl(bi_1pin_with_name(Y8, "Keyboard Y8 (pin 12)"));
      bi_decl(bi_1pin_with_name(Y9, "Keyboard Y9 (pin 22)"));

      bi_decl(bi_1pin_with_name(X0, "Keyboard X0 (pin 14)"));
      bi_decl(bi_1pin_with_name(X1, "Keyboard X1 (pin 18)"));
      bi_decl(bi_1pin_with_name(X2, "Keyboard X2 (pin 16)"));
      bi_decl(bi_1pin_with_name(X3, "Keyboard X3 (pin 20)"));
      bi_decl(bi_1pin_with_name(X4, "Keyboard X4 (pin 21)"));
      bi_decl(bi_1pin_with_name(X5, "Keyboard X5 (pin 19)"));
      bi_decl(bi_1pin_with_name(X6, "Keyboard X6 (pin 26)"));
      bi_decl(bi_1pin_with_name(X7, "Keyboard X7 (pin 17)"));

      bi_decl(bi_1pin_with_name(SHIFT_PIN, "Keyboard SHIFT (pin 24)"));

      for (int i = 0; i <= 7; i++) {
            gpio_init(xPins[i]);
            gpio_set_dir(xPins[i], GPIO_IN);
      }
      for (int i = 0; i <= 9; i++) {
            gpio_init(yPins[i]);
            gpio_set_dir(yPins[i], GPIO_OUT);
            gpio_put(yPins[i], 0);
      }

      gpio_init(SHIFT_PIN);
      gpio_set_dir(SHIFT_PIN, GPIO_OUT);

      gpio_init(LED_PIN);
      gpio_set_dir(LED_PIN, GPIO_OUT);

      stdio_init_all();

      printf("Apple 2e keyboard emulator\n");

      int key = 0;
      int nextKey = 0;
      absolute_time_t keyDownTime= 0;
      while (1) {
            if (nextKey) {
                  key = nextKey;
                  nextKey = 0;
            } else {
                  key = getchar();
            }
            if (key != EOF) {

                  if (key == 27) {
                        // Escape key. Is the next character a '['?
                        sleep_ms(1); // Give the keyboard a moment to send the next character
                        nextKey = getchar();
                        if (nextKey == '[') {
                              sleep_ms(1);
                              // Arrow keys
                              nextKey = getchar();
                              switch (nextKey) {
                                    case 'A':
                                          key = '↑'; // Up arrow
                                          nextKey = 0;
                                          break;
                                    case 'B':
                                          key = '↓'; // Down arrow
                                          nextKey = 0;
                                          break;
                                    case 'C':
                                          key = '→'; // Right arrow
                                          nextKey = 0;
                                          break;
                                    case 'D':
                                          key = '←'; // Left arrow
                                          nextKey = 0;
                                          break;
                                    default:
                                          nextKey = 0; // Ignore other escape sequences
                                          continue;
                              }
                        }
                  }
                  key = toupper(key);
                  if (!keyMap.contains(key)) {
                        printf("Key with code '%d' not in keymap\n", key);
                        continue;
                  }
                  MatrixPosition pos = keyMap.at(key);
                  keyDownTime = get_absolute_time();
                  gpio_put(LED_PIN, 1);
                  gpio_put(SHIFT_PIN, pos.shift ? 0 : 1);
                  while (1) {
                        // Wait for the y line to be low (likely a no-op)
                        while(gpio_get(pos.x) == 1) {
                        }
                        // Set the x line high when the y line goes high
                        while(1) {
                              if (gpio_get(pos.x) == 1) {
                                    gpio_put(pos.y, 1);
                                    break;
                              }
                        }
                        // Wait for the y line to go low again
                        while (1) {
                              if (gpio_get(pos.x) == 0) {
                                    break;
                              }
                        }
                        gpio_put(pos.y, 0);

                        // Press keys for 20ms
                        if (absolute_time_diff_us(keyDownTime, get_absolute_time()) > 20000) {
                              break;
                        }
                  }
                  gpio_put(SHIFT_PIN, 0);
                  gpio_put(LED_PIN, 0);
                  printf("Key %c pressed at (%d, %d)\n", key, pos.x, pos.y);

                  // this allows us to press repeated keys, which would otherwise
                  // appear as a single (longer) keypress
                  sleep_ms(5);
                  if (key == '\r') {
                        // Simplify copy-pasting multiple lines of BASIC.
                        // Otherwise it may swallow the start of the next line.
                        sleep_ms(250);
                  }

            }
      }
}
