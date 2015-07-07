#include "chef_md5.h"
#include <map>
#include <stdio.h>
#include <assert.h>

int main() {
    printf(">md5_test.\n");
    std::map<std::string, std::string> md5_2_src;
    md5_2_src["d41d8cd98f00b204e9800998ecf8427e"] = "";
    md5_2_src["187ef4436122d1cc2f40dc2b92f0eba0"] = "ab";
    md5_2_src["ab56b4d92b40713acc5af89985d4b786"] = "abcde";
    md5_2_src["a925576942e94b2ef57a066101b48876"] = "abcdefghij";
    md5_2_src["bff2dcb37ef3a44ba43ab144768ca837"] = "He who has a shady past knows that nice guys finish last.";
    md5_2_src["72c2ed7592debca1c90fc0100f931a2f"] = "The fugacity of a constituent in a mixture of gases at a given temperature is proportional to its mole fraction.  Lewis-Randall Rule";

    for (auto it : md5_2_src) {
        assert(chef::md5::marshal(it.second) == it.first);
    }
    printf("<md5_test.\n");

    return 0;
}
