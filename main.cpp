#include <iostream>
#include <ConsistencyHash.h>

using namespace std;

int main()
{
    ConsistencyHash hash(5);

    hash.addHashNodesFromString("192.168.1.1:8899");
    hash.addHashNodesFromString("192.168.1.1:7799");
    hash.addHashNodesFromString("192.168.1.1:6699");
    hash.addHashNodesFromString("192.168.1.1:5599");

    hash.ShowNodeMsg();

    MD5 md5;

    for (int i = 0; i < 8000; i++) {
        string str = "Start";
        string str2 = str + "test" + std::to_string(i * 100);

        md5.GenerateMD5(str2.c_str(), str2.length());

        hash.getMappingNodeFromKey(md5.ToULong32());
    }

    hash.ShowMappingStatisticMsg();

    return 0;
}

