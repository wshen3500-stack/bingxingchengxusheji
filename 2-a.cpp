#include <iostream>
#include <sys/time.h>

using namespace std;

const int Max = 500000; 
double arr[Max];

int main() {
    // 随便灌点数据
    for (int i = 0; i < Max; i++) {
        arr[i] = i * 1.5;
    }

    struct timeval begin, end;
    int rounds = 1000; // 累加操作太快了，循环次数设大点
    double final = 0.0;

    gettimeofday(&begin, NULL);
    for (int i = 0; i < rounds; i++) {
        double sum = 0.0;
        // 单路串行累加，有严格的数据依赖
        for (int j = 0; j < Max; j++) {
            sum += arr[j];
        }
        final = sum; // 记录最后一次结果防编译器把无用循环优化没
    }
    gettimeofday(&end, NULL);

    double time = (end.tv_sec - begin.tv_sec) * 1000.0 + (end.tv_usec - begin.tv_usec) / 1000.0;
    cout  << time / rounds << "  ms " << final << "\n";
    return 0;
}