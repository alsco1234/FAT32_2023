class DirectoryEntry{
    private:
        bool is_dir;

    public :
        string name[0x8];
        string ext[0x3];
        int cluster_hi;
        int cluster_low;
        int file_size;

        DirectoryEntry(char* buffer);
};