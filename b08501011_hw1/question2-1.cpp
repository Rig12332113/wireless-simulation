#include <iostream>
#include <cmath>
#include <random>
int main(){
    std::random_device rd;
    std::mt19937 generator(rd());
    std::normal_distribution<double> norm(0.0, 6.0);
    float hb = 51.5, hr = 1.5;
    float path_loss = 0;
    for(int i = 1; i <= 150; i++){
        double shadowing = norm(generator);
        path_loss = (hb * hr) * (hb * hr) / i / i / i / i;
        float dB = 10 * log10(path_loss);
        printf("%3d,%3.3f,%3.3f\n", i, 61 + dB - 30, 61 + dB - 30 + shadowing);
    }
    return 0;
}