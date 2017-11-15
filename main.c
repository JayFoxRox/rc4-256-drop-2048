// This code assumes Little-Endian!
// Output with all 0x00-key should start with: C34B116DA018DA7E4E07965342...

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <openssl/rc4.h>

int main(int argc, char* argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <time since epoche> <time since boot>\n", argv[0]);
    return 1;
  }

  union {
    uint8_t raw[16];
    struct {
      // in 100ns intervals since 1601 using win32 GetSystemTimeAsFileTime()
      uint64_t time_since_epoche;

      // in cycles since boot using x86 rdtsc
      uint64_t time_since_boot;
    };
  } key;
  key.time_since_epoche = strtoull(argv[1], NULL, 10);
  key.time_since_boot = strtoull(argv[2], NULL, 10);

  RC4_KEY rc4key;
  RC4_set_key(&rc4key, 16, (unsigned char*)&key);

  const uint8_t zero = 0x00;
  uint8_t buffer;

  // drop-2048
  unsigned int i;
  for(i = 0; i < 2048; i++) {
    RC4(&rc4key, 1, &zero, &buffer);
  }

  // output keystream
  while(true) {
    RC4(&rc4key, 1, &zero, &buffer);
    fwrite(&buffer, 1, 1, stdout);
  }

  return 0;
}
