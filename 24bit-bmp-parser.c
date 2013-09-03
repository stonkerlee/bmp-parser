#include <stdio.h>
#include <assert.h>

int main(int argc, char* argv[])
{
  FILE* fp = fopen("24bit-red.bmp", "rb");
  if (fp == NULL) {
    perror("fopen");
    return -1;
  }
  
  fseek(fp, 0, SEEK_END);
  uint32_t file_size = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  
  uint8_t buffer[1024] = {0};
  fread(buffer, 1, 1024, fp);
  
  int i = 0;
  for (; i < 32; i++) {
    printf("%02x ", buffer[i]);
    if ((i+1)%16 == 0)
      printf("\n");
  }
  
  assert(buffer[0] == 0x42 && buffer[1] == 0x4D);
  
  uint32_t bmp_size = buffer[4]<<16 | buffer[3]<<8 | buffer[2];
  printf("bmp_size = %u\n", file_size);
  assert(file_size == bmp_size);
  
  return 0;
}
