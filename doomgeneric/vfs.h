#ifndef __VFS_H
#define __VFS_H

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    int idx;
    bool active;
    uint32_t pos;

} VFS_FILE;

VFS_FILE *vfs_open(const char *name, const char *mode);
int vfs_close(VFS_FILE *stream);
int vfs_seek(VFS_FILE *stream, int offset, int whence);
long vfs_tell(VFS_FILE *stream);
size_t vfs_read(void *ptr, size_t size, size_t nmemb, VFS_FILE *stream);
size_t vfs_write(const void *ptr, size_t size, size_t nmemb, VFS_FILE *stream);


#endif