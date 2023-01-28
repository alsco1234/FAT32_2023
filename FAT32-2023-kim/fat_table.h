class Fat_table{
    private:

    public :
        vector<uint32_t> fat; //cluster area
        vector<char> fat_bytes(fat_size);

        Fat_table(vector<char>* fat_bytes[0], int fat_size);
};