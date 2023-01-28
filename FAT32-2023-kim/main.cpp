#include <iostream>
#include <fstream>
#include <vector>
#include "utils.h"
#include "fat32.h"

using namespace std;

// 사용자로부터 파일이름 받아서 fat한테 넘겨줌
int main(int argc, char *argv[]){
    ifstream ifs(argv[1], ios_base::binary);
    Fat32 fat32(argv[1]);

    auto node = fat32.GetNode("LEAF.JPG");
    node->ExportTo('Leaf.jpg');

    return 0;
}