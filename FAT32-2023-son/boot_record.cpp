#include "boot_record.h"
#include "util.h"
#include <fstream>
#include <iostream>

using namespace std;

BootRecord::BootRecord(char* buffer)
{
    bytes_per_sector = io::to_le2(buffer + 0x0b);
    sectors_per_cluster = io::to_le1(buffer + 0x0d);
    cluster_size = bytes_per_sector * sectors_per_cluster;
    fat_count = io::to_le1(buffer + 0x10);

    reserved_area = io::to_le2(buffer + 0x0e) * bytes_per_sector;
    fat1_offset = reserved_area;
    fat_num_sector = io::to_le4(buffer + 0x24);
    data_block_area = reserved_area + fat_count * fat_num_sector * bytes_per_sector;
}