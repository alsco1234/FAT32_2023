#include "directory_entry.h"
#include "util.h"
#include <iostream>
#include <vector>

using namespace std;

DirectoryEntry::DirectoryEntry(char* buffer, vector<uint32_t> fat){
    int attr = io::to_le1(buffer + 0x0b);
    if ((attr & 0x10) == 0x10) this->is_dir = true;
    else this->is_dir = false;

    this->name = string(buffer, 0, 8);

    this->cluster_no = io::to_le2(buffer+0x14)<<2 | io::to_le2(buffer+0x1a);

    this->file_size = io::to_le4(buffer+0x1c);
            
    whole_cluster.push_back(this->cluster_no);
    uint32_t current_no = fat[this->cluster_no];
    while (current_no != 0xfffffff)
    {
        whole_cluster.push_back(current_no);
        current_no = fat[current_no];
    }
}
