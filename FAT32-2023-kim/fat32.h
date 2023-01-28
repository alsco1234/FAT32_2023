class Node{
    public:
        Node(ifstream& ifs, DirectoryEntry* de);

        bool ExportTo(string path);
    private:
        vector<unit32_t> cluster_nos; //이 노드에 대한 cluster numbers
};

class Fat32{
    private:
        BootRecord* br;
        FatTable* fat;
        Node* root;
        ifstream& ifs;
    public :
        Fat32(char const* fname);

        Node* GetNode(char const*(name));
};