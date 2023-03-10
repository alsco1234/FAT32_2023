#include <iostream>
#include <vector>
#include "directory_entry.h"
#include "util.h"

using namespace std;

class DirectoryEntry{
    private:
        bool is_dir;

    public :
        string name[0x8];
        string ext[0x3];
        int cluster_hi;
        int cluster_low;
        int file_size;

        DirectoryEntry(char* buffer){
            int attr = io::to_le1(buffer + 0x0b);

            //dir인지 file인지 2진수로 변환해서 or시켜 확인
            if ((attr & 0x10) == 0x10){ 
                this->is_dir = true;
            }
            else if((attr & 0x20) == 0x20){
                this->is_dir = false;
            }

            string name(buffer, 0, 8);
            string ext(buffer, 8, 3);
            int cluster_hi = io::to_le2(buffer + 0x14);
            int cluster_low = io::to_le2(buffer + 0x1A);
            int file_size = io::to_le4(buffer + 0x1C);
        }
};