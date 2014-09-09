#include "config.h"
#include <assert.h>
#include <stdlib.h>

int main()
{
    printf(">config_test.\n");
    FILE *fp = fopen("test.config.chef", "ab+");
    fprintf(fp, "name=chef\n");
    fprintf(fp, "name=pengrl\n"); ///
    fprintf(fp, "#name=sss\n");
    fprintf(fp, "age=12\n");
    fprintf(fp, "test1 =a\n"); ///
    fprintf(fp, "test2= b\n");
    fprintf(fp, "test3 = c\n"); ///
    fclose(fp);

    chef::config c;
    assert(c.load("test2.config.chef") == -1);
    assert(c.load("test.config.chef") == 0);
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

