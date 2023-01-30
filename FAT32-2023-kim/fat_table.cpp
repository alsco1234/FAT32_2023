#include <iostream>
#include <fstream>
#include <vector>
#include "utils.h"
#include "boot_record.h"

using namespace std;

class Fat_table{
    private:

    public :
        vector<uint32_t> fat; //cluster area

        Fat_table(vector<char>* fat_bytes[0], int fat_size){
            
            // 시작 cluster 가지고 지금 파일이 어디 cluster에 있는지
            for(auto i=0; i<fat_size; i+=4){
                auto entry = io::to_le4((char*)&fat_bytes[i]);
                fat.push_back(entry);
            }

            fat = new Fat_table(&fat_bytes[0], fat_size);
        }
};