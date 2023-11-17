#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int read_sector(int fd, unsigned int sector_num, char *buf) {
    off_t offset = 512 * sector_num;
    if (lseek(fd, offset, SEEK_SET) == -1) {
        perror("lseek");
        return -1;
    }
    if (read(fd, buf, 512) == -1) {
        perror("read");
        return -1;
    }
    return 0;
}

int main() {
    int fd = open("test.img", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    char buf[512];
    if (read_sector(fd, 0, buf) == -1) {
        close(fd);
        return 1;
    }

    for (int i = 0; i < 512; i++) {
        printf("%02X ", (unsigned char)buf[i]);
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }

    close(fd);
    return 0;
}
