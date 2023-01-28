#include <iostream>
#include <fstream>
#include <vector>
#include "util.h"
#include "boot_record.h"
#include "directory_entry.h"

using namespace std;

class Node{
    public:
        Node(DirectoryEntry* de, ifstream* ifs)
        {
            this->cluster_nos = de->whole_cluster;
            this->ifs = ifs;
        }
        bool ExportTo(string path)
        {
            ofstream ofs(path);
            char buffer[0x1000] = { 0 };
            for (int i = 0; i < cluster_nos.size(); i++)
            {
                ifs->seekg(0x400000 + (cluster_nos[i]-2) * 0x1000, ios_base::beg);
                ifs->read(buffer, 0x1000);
                ofs.write(buffer, 0x1000);
            }
            return true;
        }
    private:
        vector<uint32_t> cluster_nos;
        ifstream* ifs;
};

class FatTable{
    public:
        FatTable(char* fat_bytes, int fat_size)
        {
            for (auto i=0; i<fat_size; i+=4){
                auto entry = io::to_le4((char*)&fat_bytes[i]);
                fat.push_back(entry);
            }
        }
        vector<uint32_t> fat;
};

class Fat32
{
    public:
        Fat32(ifstream* ifs)
        {
            this->ifs = ifs;
            char buffer[0x200] = { 0 };
            ifs->read(buffer, 0x200);
            br = new BootRecord(buffer);

            ifs->seekg(br->fat1_offset, ios_base::beg);
            auto fat_size = br->fat_num_sector * br->bytes_per_sector;
            vector<char> fat_bytes(fat_size);
            ifs->read(&fat_bytes[0], fat_size);
            fat = new FatTable(&fat_bytes[0], fat_size);
        }

        Node* GetNode(char const* name)
        {
            //auto leaf1 = new DirectoryEntry();
            char buffer[0x20] = { 0 };
            ifs->seekg(0x404040, ios_base::beg);
            ifs->read(buffer, 0x20);
            auto leaf1 = new DirectoryEntry(buffer, fat->fat);
            auto node = new Node(leaf1, ifs);
            return node;
        }
    private:
        ifstream* ifs;
        BootRecord* br;
        FatTable* fat;
        Node* root;
};

int main(int argc, char* argv[]){
    ifstream ifs(argv[1]);
    Fat32 fat32(&ifs);
    fat32.GetNode("LEAF.JPG")->ExportTo("LEAF.JPG");
    return 0;
}