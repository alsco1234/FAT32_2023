class BootRecord{
    public:
        BootRecord(char* buffer);

        int bytes_per_sector;
        int sectors_per_cluster;
        int cluster_size;
        int fat_count;
        int reserved_area;
        int fat1_offset;
        int fat_num_sector;
        int data_block_area;
};