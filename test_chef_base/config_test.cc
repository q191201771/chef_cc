#include "config.h"
#include <assert.h>
#include <stdlib.h>

int main()
{
    printf(">config_test.\n");
    FILE *fp = fopen("cfg.test", "wb+");
    fprintf(fp, "name=chef\r\n");
    fprintf(fp, "name=pengrl\r\n"); ///
    fprintf(fp, "#name=sss\r\n");
    fprintf(fp, "age=12\r\n");
    fprintf(fp, "test1 =a\r\n"); ///
    fprintf(fp, "test2= b\r\n");
    fprintf(fp, "test3 = c\r\n"); ///
    fclose(fp);

    chef::config c;
    assert(c.load("cfg.test2") == -1);
    assert(c.load("cfg.test") == 0);
    std::string value;
    assert(c.get("name", value) == 0);
    assert(value == "pengrl");
    assert(c.get("age", value) == 0);
    int age = atoi(value.c_str());
    assert(age == 12);
    assert(c.get("test1", value) == -1);
    assert(c.get("test1 ", value) == 0);
    assert(value == "a");
    assert(c.get("test2", value) == 0);
    assert(value == " b");
    printf("<config_test.\n");

    return 0;
}

