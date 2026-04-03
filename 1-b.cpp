#include <iostream>
#include <sys/time.h>

using namespace std;

const int Max = 10000;
double data[Max][Max];
double x[Max];
double y[Max];

void ini() {
    for (int i = 0; i < Max; i++) {
        x[i] = i * 0.5;
        y[i] = 0.0;
        for (int j = 0; j < Max; j++) {
            data[i][j] = i + j * 0.1;
        }
    }
}

int main() {
    ini();
    struct timeval ts, te;
    int rounds = 10;

    gettimeofday(&ts, NULL);
    for (int i = 0; i < rounds; i++) {
        for(int j = 0; j < Max; j++) y[j] = 0.0;
        
        // 核心优化：外层循环行，内层循环列（连续内存访问）
        for (int a = 0; a < Max; a++) {
            for (int b = 0; b < Max; b++) {
                y[b] += data[a][b] * x[a];
            }
        }
    }
    gettimeofday(&te, NULL);

    double time = (te.tv_sec - ts.tv_sec) * 1000.0 + (te.tv_usec - ts.tv_usec) / 1000.0;
    cout << time / rounds << " ms\n";
    return 0;
}