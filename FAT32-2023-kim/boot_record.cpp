#include "utils.h"
#include "boot_record.h"
#include <fstream>
#include <iostream>

using namespace std;

BootRecord::BootRecord(char* buffer){
        // 파일 읽기 (1byte, 2byte)   
        int bytes_per_sector = io::to_le2(buffer + 0x0b); //1섹터당 바이트 수 200
        int sectors_per_cluster = io::to_le1(buffer + 0x0d); //1클러스터당 섹터 수 8
        int cluster_size = bytes_per_sector * sectors_per_cluster; // 클러스터 크기
        int fat_count = io::to_le1(buffer + 0x10); //fat영역 개수 2

        sectors_per_fat = io::to_le4(buffer + 0x24);

        fat_area = fat_count * sectors_per_fat;
        fat_size = fat_area * bytes_per_sector;
        cout << hex << fat_size << endl;


        
        int sector_count_in_reserved = io::to_le2(buffer + 0x0e); //예약된 영역의 섹터 수 10ae
        // reserved 영역의 끝지점 = fat1의 시작주소
        int reserved_area = sector_count_in_reserved * bytes_per_sector; //215c00
        // fat 섹터의 시작지점s
        int fat1_area = io::to_le2(buffer + 0x24); //FAT 영역의 섹터 수 7a9
        // data 영역의 시작지점
        int data_block_area = reserved_area + (fat_count * fat1_area * bytes_per_sector); //400000
}