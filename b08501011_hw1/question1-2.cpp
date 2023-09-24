#include <iostream>
#include <cmath>
int main(){
    float hb = 51.5, hr = 1.5;
    float path_loss = 0;
    //noise in dBm
    float noise = 10 * log10(1.38 * 300 * pow(10, -19));
    for(int i = 1; i <= 150; i++){
        path_loss = (hb * hr) * (hb * hr) / i / i / i / i;
        float dB = 10 * log10(path_loss);
        printf("%3d,%3.3f\n", i, 61 + dB - noise);
    }
    return 0;
}