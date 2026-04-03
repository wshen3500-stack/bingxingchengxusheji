#include <iostream>
#include <sys/time.h>

using namespace std;

// 保持与 2-b.cpp 相同的数据规模
const int Max = 500000; 
double arr[Max];

int main() {
    // 初始化数据，与 2-b.cpp 保持绝对一致，确保结果可比
    for (int i = 0; i < Max; i++) {
        arr[i] = i * 1.5;
    }

    struct timeval begin, end;
    int rounds = 1000; 
    double final_result = 0.0;

    gettimeofday(&begin, NULL);
    for (int i = 0; i < rounds; i++) {
        // 核心优化：定义 4 个独立的累加器，打破数据依赖
        double sum0 = 0.0, sum1 = 0.0, sum2 = 0.0, sum3 = 0.0;
        
        int j = 0;
        // 每次循环处理 4 个元素（循环展开 + 多路累加）
        for (; j <= Max - 4; j += 4) {
            sum0 += arr[j];
            sum1 += arr[j+1];
            sum2 += arr[j+2];
            sum3 += arr[j+3];
        }
        
        // 处理末尾剩余的元素（虽然 500000 能被 4 整除，但加上尾部处理是好习惯）
        for (; j < Max; j++) {
            sum0 += arr[j];
        }
        
        // 将多路结果汇总，并赋值给外部变量防优化
        final_result = sum0 + sum1 + sum2 + sum3; 
    }
    gettimeofday(&end, NULL);

    double time = (end.tv_sec - begin.tv_sec) * 1000.0 + (end.tv_usec - begin.tv_usec) / 1000.0;
    
    // 输出平均耗时和最终结果（用来和 2-b 对比，验证计算是否正确）
    cout << time / rounds << " ms " << final_result << ")\n";
    
    return 0;
}