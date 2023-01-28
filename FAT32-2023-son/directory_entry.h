#include <string>
#include <vector>

using namespace std;

class DirectoryEntry{

    public:
        DirectoryEntry(char* buffer, vector<uint32_t> fat);
        bool is_dir;
        string name;
        int cluster_no;
        int file_size;
        vector<uint32_t> whole_cluster;
};