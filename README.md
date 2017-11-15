To clone, make and run:

```
git clone https://github.com/JayFoxRox/rc4-256-drop-2048.git
cd rc4-256-drop-2048
mkdir build
cd build
cmake ..
make
./rc4-256-drop-2048 0 0 | hexdump -ve '/1 "%02X"'
```

You'll need a working C99 toolchain, CMake and OpenSSL.
