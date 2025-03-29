#ifndef __VFS_DATA_H
#define __VFS_DATA_H

/**
 *     This file was generated with makefsdata.py, do not edit manually.
 */

#include <stdint.h>
#include <stddef.h>

typedef struct
{
    uint32_t size;
    const uint8_t *file_name;
    const uint8_t *file_contents;

} t_vfs_data_entry;


extern const t_vfs_data_entry vfs_data_list[];
extern const size_t vfs_data_list_size;

#endif /* __VFS_DATA_H */