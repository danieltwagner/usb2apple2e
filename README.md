# USB to Apple IIe keyboard emulator

I had an Apple IIe mainboard that I wanted to test but no keyboard.
This project turns a Raspberry Pi Pico into a USB Serial device that emits keystrokes when connected to the Apple IIe's keyboard connector.

I found that no further hardware other than the Pi Pico is required, despite the 5V logic levels. There are suggestions online that this is only the case if you first power up the Pi Pico and then the device, so that is what I did, without ill effects so far. Your device may vary so if in doubt you may want to convert voltage levels down.

A nice side-effect of doing this over a terminal connection was that it allowed me to copy-paste [S. Elliot's simple-but-effective Applesoft memory test](https://www.applefritter.com/content/very-effective-applesoft-memory-test) without having to type it out:

```
10 HIMEM: 4096
20 S = S - 1:R = RND (S)
30 PRINT "FILLING MEMORY WITH PSEUDORANDOM BYTES"
40 FOR A = 4096 TO 49151: POKE A,256 * RND (1): NEXT A
50 PRINT "READING AND COMPARING MEMORY"
60 R = RND (S)
70 FOR A = 4096 TO 49151: R = ABS ( PEEK (A) - INT (256 * RND (1)))
80 IF R = 0 THEN NEXT A: GOTO 20
90 PRINT "BIT MISMATCH ";
100 FOR B = 7 TO 0 STEP -1
110 PRINT INT (R / (2 ^ B)); CHR$ (32);
120 IF R >= (2 ^ B) THEN R = R - (2 ^ B)
130 NEXT B
140 PRINT "AT ";A; CHR$ (7)
150 NEXT A
160 GOTO 20
```

## Wiring
See declaration at the start of `main()`.

## Building
```
mkdir build
cd build
cmake ..
make
```
Drag uf2 file to Pi Pico, then `screen /dev/ttyACM1 115200`.
