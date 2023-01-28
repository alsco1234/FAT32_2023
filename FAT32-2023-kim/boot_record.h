class BootRecord{
        public:
                BootRecord(char* buffer);

                int bytes_per_sector;
                int sectors_per_sector;
                int cluster_size;
                int fat_count; //2

                int fat_size;
                int sectors_per_fat;
                int fat_area;

                int reserved_area; //0x215c00
                int fat1_area; //400000
                int data_block_area; //
};