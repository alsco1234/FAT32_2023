#include <iostream>
#include <fstream>
#include <vector>
#include "utils.h"
#include "boot_record.h"
#include "directory_entry.h"
#include "fat_table.h"

using namespace std;

class Node{
    public:
        Node(ifstream& ifs, DirectoryEntry* de){
            Fat_table = new(&fat_bytes[0], de->fat_size);
            cluster_cur = 7
            for(i=400080; i<fat_size; i+=4){
                if(entry(cluster_cur) != 0xfffff){
                    cluster_nos.push_back(entry);
                    cluster_cur = Fat_table[cluster_cur];
                }
                else{
                    break;
                }
            }
        }

        bool ExportTo(string path){
            ofstream ofs(path);

            for (auto& cluster: cluster_nos){
                // read cluster from ifstream
                char buffer[de->cluster_size] = {0};
                // write vuffer to ofs;
                ofs.write(buffer, de->cluster_size);
            }

            return true;
        }
    private:
        vector<unit32_t> cluster_nos; //이 노드에 대한 cluster numbers
        ifstream ifs;
};

class Fat32{
    private:
        BootRecord* br;
        FatTable* fat;
        Node* root;
        ifstream& ifs;
    public :
        Fat32(char const* fname){
            ifstream ifs(fname, ios_base::binary);
            char buffer[0x200] = {0};

            // 버퍼 이동
            ifs.read(buffer, 0x200);
            br = new BootRecord(buffer);

            ifs.seekg(br->fat1_area, ios_base::beg); //40080으로 이동
            ifs.read(&br->fat_bytes[0], br->fat_size);

            fat = new FatTable(&fat_bytes[0], br->fat_size);

            cout << hex << fat[8] << endl;
            cout << hex << fat[0x96] << endl;
        }

        Node* GetNode(char const*(name)){
            auto leaf1 = new DirectoryEntry();
            auto node = new Node(ifs, leaf1);
            return node;
        }
};