#include <stdio.h>
#include <inttypes.h>
#include <string>

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("usage: <in file>\n");
        return 0;
    }
    FILE *fp = fopen(argv[1], "rb+");
    if (!fp) {
        printf("%s error.\n", argv[1]);
        return 0;
    }
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while((read = getline(&line, &len, fp)) != -1) {
        char *p = line;
        bool flag = false;
        char *begin = line;
        //printf("%s", line);
        for (; p != line + len; ++p) {
            if (*p == '\'') {
                if (!flag) {
                    begin = p;
                    flag = true;
                } else {
                    std::string str(begin + 1, p - begin - 1);
                    if (str.find("\\n") != std::string::npos) {
                        printf("\n");
                    } else {
                        printf("%s", str.c_str());
                    }
                    flag = false;
                }
            }
        }
    }
    printf("\n");

    return 0;
}
