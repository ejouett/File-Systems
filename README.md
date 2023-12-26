1. Create a FAT FS image

$ dd if=/dev/zero of=test.img bs=1M count=32
$ mkfs.vfat -F16 test.img

2. Mount your FAT FS image on your Linux machine

$ sudo mkdir /mnt/disk
$ sudo mount test.img /mnt/disk

3. Create a file in your disk image

$ echo "test" > /mnt/disk/test.txt

4. Unmount you disk image

$ umount /mnt/disk

5. Write a function in C that reads one sector (512 bytes) from your disk image. Function prototype should be something like:

int read_sector(int fd, unsigned int sector_num, char *buf) {
  // ...
}

Your read_sector() function needs to read from an offset from the beginning of the filesystem image. That offset is 512*sector_num bytes. You can use the lseek() syscall to seek to the position in the file that you want to read from.

Call your read_sector() function and read the contents of one of the sectors. Print the contents in hex to the terminal. Use the hexdump utility to confirm that you have read the correct data:

$ hexdump -C test.img | less

This activity extends the functionality of Filesystems Activity Part 1.


1. Download fat.h from the following link and put it in the same directory as your code from Filesystems Activity Part 1:

https://neilklingensmith.com/teaching/loyola/cs310-s2023/activities/fat.h

2. #include "fat.h" in your activity's C file.

3. In your main() function, call read_sector() to read in the first sector from your disk image. This is the boot sector, and it contains info about where to find the FAT table and the root directory entries.

4. Call printf() to print out the following elements from your boot sector:

   (a) num_sectors_per_cluster
   (b) num_reserved_sectors
   (c) num_fat_tables
   (d) num_root_dir_entries

   Some code below to get started:

   char boot_sector[512]; // boot sector buffer. Make this a global

   // Inside main:

   read_sector(XXX, YYY, ZZZ);

   struct boot_sector *bsptr = boot_sector;

   printf("num_sectors_per_cluster = %d\n", bsptr->num_sectors_per_cluster);

5. Using the same technique as in steps 3-4, print out the filename and extension of first few RDEs from the RDE region.
