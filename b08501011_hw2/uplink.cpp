#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
#define PI 3.14159
int main(void){
    //初始六邊形
    FILE *hexagon = fopen("hexagon.txt", "wt");
    FILE *origin = fopen("origin.txt", "wt");
    fprintf(origin, "0 0\n");
    fprintf(hexagon, "%.2f 0\n", 500 / sqrt(3));
    fprintf(hexagon, "%.2f 250\n", 250 / sqrt(3));
    fprintf(hexagon, "%.2f 250\n", -250 / sqrt(3));
    fprintf(hexagon, "%.2f 0\n", -500 / sqrt(3));
    fprintf(hexagon, "%.2f -250\n", -250 / sqrt(3));
    fprintf(hexagon, "%.2f -250\n", 250 / sqrt(3));
    fprintf(hexagon, "%.2f 0\n", 500 / sqrt(3));
    fclose(hexagon);
    fclose(origin);
    //隨機給50點
    float distance[50],location_x[50],location_y[50];
    FILE *location = fopen("location.txt", "wt");
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> degree_gen(0.0, 2 * PI);
    std::uniform_real_distribution<> length_gen(0.0, 500 / sqrt(3));
    for (int i = 0; i < 50; i++){
        float degree = degree_gen(gen);
        float length = length_gen(gen);
        float x = length * cos(degree);
        float y = length * sin(degree);
        //檢驗是否在六邊形中，真則輸出，假則重新產生新數據
        if ((y <= 250 && y >= -250) && 
            (x * sqrt(3) - y <= 500 && x * sqrt(3) - y >= -500) &&
            (x * sqrt(3) + y <= 500 && x * sqrt(3) + y >= -500)){
            distance[i] = sqrt(x * x + y * y);
            location_x[i] = x;
            location_y[i] = y;
            fprintf(location, "%.2f %.2f\n", x, y);
        }
        else
            i--;
    }
    fclose(location);
    //計算各點dB數值
    float received_power[50];
    FILE *power = fopen("power.txt", "wt");
    for (int i = 0; i < 50; i++){
        received_power[i] = ((51.5 * 1.5) * (51.5 * 1.5) / distance[i] / distance[i] / distance[i] / distance[i]);
        fprintf(power, "%.2f %.2f\n", distance[i], 51 + 10 * log10(received_power[i]) - 30);
    }
    fclose(power);
    //計算各點SINR
    FILE *SINR = fopen("SINR.txt", "wt");
    float noise = 0;
    for(int i = 0; i < 50; i++){
        float interfere = 0;
        for (int j = 0; j < 50; j++){
            if (i != j)
                interfere += pow(10, 5.1) * received_power[j];
        }
        noise = 10 * log10(interfere + (1.38 * 300 * pow(10, -13)));
        fprintf(SINR, "%.2f %.2f\n", distance[i], 51 + 10 * log10(received_power[i]) - noise);
    }
    fclose(SINR);
    return 0;
}