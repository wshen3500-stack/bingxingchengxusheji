#include <iostream>
#include <sys/time.h>

using namespace std;

const int Max = 10000;
// 设为全局变量，防止爆栈
double data[Max][Max];
double x[Max];
double y[Max];

void set() {
    for (int r = 0; r < Max; r++) {
        x[r] = r * 0.5;
        y[r] = 0.0;
        for (int c = 0; c < Max; c++) {
            data[r][c] = r + c * 0.1;
        }
    }
}

int main() {
    set();
    struct timeval start, end;
    int rounds = 10;

    gettimeofday(&start, NULL);
    for (int k = 0; k < rounds; k++) {
        // 每轮清理结果
        for(int i = 0; i < Max; i++) y[i] = 0.0;
        
        // 核心：外层循环列，内层循环行（平凡逻辑）
        for (int a = 0; a < Max; a++) {
            for (int b = 0; b < Max; b++) {
                y[a] += data[b][a] * x[b];
            }
        }
    }
    gettimeofday(&end, NULL);

    double time = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1000.0;
    cout << time / rounds << " ms\n";
    return 0;
}