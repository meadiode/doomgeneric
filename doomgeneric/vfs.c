#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "vfs.h"
#include "vfs_data.h"

#define VFS_N_HANDLES 8

static VFS_FILE handles[VFS_N_HANDLES] = {0};


VFS_FILE *vfs_open(const char *name, const char *mode)
{
    if (!mode || mode[0] == 'w')
    {
        return NULL; /* vfs is read-only */
    }

    VFS_FILE *hdl = NULL;

    for (int i = 0; i < vfs_data_list_size; i++)
    {
        if (!strcasecmp(name, (const char*)vfs_data_list[i].file_name))
        {
            for (int j = 0; j < VFS_N_HANDLES; j++)
            {
                if (!handles[j].active)
                {
                    hdl = &handles[j];
                    hdl->idx = i;
                    hdl->pos = 0;
                    hdl->active = true;
                    return hdl;
                }
            }
        }
    }

    return hdl;
}


int vfs_close(VFS_FILE *stream)
{
    if (stream)
    {
        stream->active = false;
        stream->pos = 0;
        return 0;
    }

    return -1;
}


int vfs_seek(VFS_FILE *stream, int offset, int whence)
{
    if (!stream || !stream->active)
    {
        return -1;
    }
    
    uint32_t npos = 0;
    uint32_t len = vfs_data_list[stream->idx].size;

    switch (whence)
    {
    case SEEK_SET:
        npos = offset;
        break;

    case SEEK_CUR:
        npos = stream->pos + offset;
        break;

    case SEEK_END:
        npos = len + offset;
        break;

    default:
        return -1;
    }

    if (npos < len)
    {
        stream->pos = npos;
        return 0;
    }

    return -1;
}


long vfs_tell(VFS_FILE *stream)
{
    if (!stream || !stream->active)
    {
        return -1;
    }
    
    return stream->pos;
}


size_t vfs_read(void *ptr, size_t size, size_t nmemb, VFS_FILE *stream)
{
    if (!stream || !stream->active)
    {
        return 0;
    }

    size_t n_items = nmemb;
    uint32_t len = vfs_data_list[stream->idx].size;
    const uint8_t *data = vfs_data_list[stream->idx].file_contents + stream->pos;

    if (n_items * size > len - stream->pos) 
    {
        n_items = (len - stream->pos) / size;
    }

    memcpy(ptr, data, n_items * size);
    stream->pos += n_items * size;

    return n_items;
}


size_t vfs_write(const void *ptr, size_t size, size_t nmemb, VFS_FILE *stream)
{
    return 0;
}