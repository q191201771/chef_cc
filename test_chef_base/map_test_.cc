#include <map>
#include <unordered_map>
#include "chef_time.h"
#include "random.h"

int main()
{
    printf("initializing test data...\n");
    const int element_num[3] = {100, 10000, 1000000};
    const int find_num = 100;
    int tmp = 0;

    int *random_arr[3] = {0};
    int *datas[3] = {0};
    for (int i = 0; i < 3; ++i) {
        /// let ::find key random,half-has-half-not-found
        random_arr[i] = new int[find_num];
        for (int j = 0; j < find_num; ++j) {
            random_arr[i][j] = chef::random::uniform_unsigned(element_num[i] * 2);
        }

        /// shuffle,let ::insert key random
        datas[i] = new int[element_num[i]];
        for (int j = 0; j < element_num[i]; ++j) {
            datas[i][j] = j;
        }
        for (int j = 0; j < element_num[i] / 2; ++j) {
            tmp = datas[i][j];
            int index = chef::random::uniform_unsigned(element_num[i]);
            datas[i][j] = datas[i][index];
            datas[i][index] = tmp;
        }
    }
    printf("go go go!!!\n");

    std::map<int, int> m1;
    std::unordered_map<int, int> m2;
    int64_t time1;
    for (int i = 0; i < 3; ++i) {
        printf("<<<<<round %d,element_num=%d\n", i, element_num[i]);
        time1 = chef::time::now(NULL, NULL);
        int j = 0;
        for (; j < element_num[i]; ++j) {
            m1.insert(std::pair<int, int>(datas[i][j], 0));
        }
        printf(" map insert %d element:%fms\n", element_num[i],
                (chef::time::now(NULL, NULL) - time1) / 1000.0);
        time1 = chef::time::now(NULL, NULL);
        j = 0;
        for (; j < element_num[i]; ++j) {
            m2.insert(std::pair<int, int>(datas[i][j], 0));
        }
        printf("umap insert %d element:%fms\n", element_num[i],
                (chef::time::now(NULL, NULL) - time1) / 1000.0);

        time1 = chef::time::now(NULL, NULL);
        j = 0;
        for (; j < find_num; ++j) {
            m1.find(random_arr[i][j]);
        }
        printf(" map find %d element average:%fms\n", 1, 
                (chef::time::now(NULL, NULL) - time1) / (find_num * 1000.0));

        time1 = chef::time::now(NULL, NULL);
        j = 0;
        for (; j < find_num; ++j) {
            m1.find(random_arr[i][j]);
        }
        printf("umap find %d element average:%fms\n", 1,
                (chef::time::now(NULL, NULL) - time1) / (find_num * 1000.0));
        time1 = chef::time::now(NULL, NULL);
        j = 0;
        for (; j < find_num; ++j) {
            m1.erase(random_arr[i][j]);
        }
        printf(" map erase %d element average:%fms\n", 1,
                (chef::time::now(NULL, NULL) - time1) / (find_num * 1000.0));
        time1 = chef::time::now(NULL, NULL);
        j = 0;
        for (; j < find_num; ++j) {
            m2.erase(random_arr[i][j]);
        }
        printf("umap erase %d element average:%fms\n", 1,
                (chef::time::now(NULL, NULL) - time1) / (find_num * 1000.0));
        time1 = chef::time::now(NULL, NULL);
        m1.clear();
        printf(" map clear:%fms\n", (chef::time::now(NULL, NULL) - time1) / 1000.0);
        time1 = chef::time::now(NULL, NULL);
        m2.clear();
        printf("umap clear:%fms\n", (chef::time::now(NULL, NULL) - time1) / 1000.0);
        printf("---------------------\n");
    }

    for (int i = 0; i < 3; ++i) {
        delete []random_arr[i];
        delete []datas[i];
    }
    return 0;
}

