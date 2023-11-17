#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "fat.h"

int read_sector(int fd, unsigned int sector_num, char *buf) {
  lseek(fd, 512 * sector_num, SEEK_SET);
  read(fd, buf, 512);
  return 0;
}

int main() {
  int fd = open("test.img", O_RDONLY);
  char sector[512];

  // Read the first sector from the disk image
  read_sector(fd, 0, sector);

  // Print the contents of the first sector in hexadecimal format
  for (int i = 0; i < 512; i++) {
    printf("%02X ", (unsigned char)sector[i]);
    if ((i + 1) % 16 == 0) {
      printf("\n");
    }
  }

  // Extract information from the boot sector
  struct boot_sector {
    // Define the structure of the boot sector
    // ...
  };

  struct boot_sector *bsptr = (struct boot_sector *)sector;

  // Print the required elements from the boot sector
  printf("num_sectors_per_cluster = %d\n", bsptr->num_sectors_per_cluster);
  printf("num_reserved_sectors = %d\n", bsptr->num_reserved_sectors);
  printf("num_fat_tables = %d\n", bsptr->num_fat_tables);
  printf("num_root_dir_entries = %d\n", bsptr->num_root_dir_entries);

  // Extract information from the root directory entries
  struct root_directory_entry {
    // Define the structure of the root directory entry
    // ...
  };

  // Read the first few root directory entries
  for (int i = 0; i < num_entries; i++) {
    read_sector(fd, sector_offset + i, sector);
    struct root_directory_entry *rdeptr = (struct root_directory_entry *)sector;
    printf("Filename: %s\n", rdeptr->file_name);
    printf("Extension: %s\n", rdeptr->file_extension);
  }

  close(fd);
  return 0;
}
