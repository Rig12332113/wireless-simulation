#include <iostream>
#include <random>
#include <cmath>
#include "hexagon.hpp"
#define PI 3.14159926
#define BUFFER_SIZE 6000000
using namespace std;
int inHexagon(Point p, Hexagon h){
    if ((h.getTL().getx() - p.getx()) * (h.getL().gety() - p.gety())
         - (h.getTL().gety() - p.gety()) * (h.getL().getx() - p.getx()) < 0)
            return 0;
    if ((h.getL().getx() - p.getx()) * (h.getBL().gety() - p.gety())
         - (h.getL().gety() - p.gety()) * (h.getBL().getx() - p.getx()) < 0)
            return 0;
    if ((h.getBL().getx() - p.getx()) * (h.getBR().gety() - p.gety())
         - (h.getBL().gety() - p.gety()) * (h.getBR().getx() - p.getx()) < 0)
            return 0;
    if ((h.getBR().getx() - p.getx()) * (h.getR().gety() - p.gety())
         - (h.getBR().gety() - p.gety()) * (h.getR().getx() - p.getx()) < 0)
            return 0;
    if ((h.getR().getx() - p.getx()) * (h.getTR().gety() - p.gety())
         - (h.getR().gety() - p.gety()) * (h.getTR().getx() - p.getx()) < 0)
            return 0;
    if ((h.getTR().getx() - p.getx()) * (h.getTL().gety() - p.gety())
         - (h.getTR().gety() - p.gety()) * (h.getTL().getx() - p.getx()) < 0)
            return 0;
    return 1;
}
float cal_length(Point a, Point b){
    return sqrt((a.getx() - b.getx()) * (a.getx() - b.getx()) + (a.gety() - b.gety()) * (a.gety() - b.gety()));
}
float cal_interference(float length){
    int interference = 0;
    interference = pow(10, 5.1) * (51.5 * 1.5) * (51.5 * 1.5) / pow(length, 4);
    return interference;
}
float simulation(int CBRin, mobile user[50]){
    int CBR = CBRin, buffer = 0;
    float total_sent = 0, total_loss = 0;
    for (int i = 0; i < 1000; i++){
        total_sent += CBR * 50;
        for(int j = 0; j < 50; j++){
            if (buffer <= BUFFER_SIZE){
                if (buffer + CBR > BUFFER_SIZE){
                    total_loss += buffer + CBR - BUFFER_SIZE;
                    buffer = BUFFER_SIZE;
                }
                else if (user[j].get_capacity() >= CBR)
                    continue;
                else
                    buffer += CBR - user[j].get_capacity();
            }
            else
                total_loss += CBR;
        }
    }
    return total_loss / total_sent;
}
int main(void){
    Point origin;
    origin.setx(0);
    origin.sety(0);
    Clusters map;
    map.set_cluster(origin);
    mobile user[50];

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> radius_gen(0.0, 500 / sqrt(3));
    uniform_real_distribution<> degree_gen(0.0, 2 * PI);

    //生成MS資料
    for (int i = 0; i < 50; i++){
        //生成隨機位置
        Point place;
        place.setx(radius_gen(gen) * cos(degree_gen(gen)));
        place.sety(radius_gen(gen) * cos(degree_gen(gen)));
        while (inHexagon(place, map.get_hexagon(0)) == 0){
            place.setx(radius_gen(gen) * cos(degree_gen(gen)));
            place.sety(radius_gen(gen) * cos(degree_gen(gen)));
        }
        user[i].set_place(place.getx(), place.gety());

        //計算SINR和shannon capacity
        float interference = 0;
        float distance = cal_length(place, map.get_hexagon(0).getC());
        user[i].set_distance(distance);
        float signal_power = cal_interference(distance);
        for (int i = 1; i < 19; i++)
            interference += cal_interference(cal_length(place, map.get_hexagon(i).getC()));
        float SINR = signal_power / (interference + (1.38 * pow(10, -23) * 300 * 2 * pow(10, 5) * 1000));
        float capacity = 2 * pow(10, 5) * log2(1 + SINR);
        user[i].set_capacity(capacity);

    }

    //輸出位置資訊
    cout << "central base station and cluster" << endl;
    map.get_hexagon(0).getC().printPoint();
    map.get_hexagon(0).printHexagon();
    cout << "mobile station location" << endl;
    for (int i = 0; i < 50; i++){
        user[i].get_place().printPoint();
        cout << "" << endl;
    }
    cout << "" << endl;
    //輸出shannon capacity
    cout << "shannon capacity" << endl;
    for (int i = 0; i < 50; i++){
        cout << user[i].get_distance() << "," << user[i].get_capacity() << endl;
    }
    cout << "" << endl;
    //模擬階段
    cout << "different CBR bits loss rate" << endl;
    float highCBR_loss_rate = simulation(800, user);
    float mediumCBR_loss_rate = simulation(600, user);
    float lowCBR_loss_rate = simulation(400, user);
    cout << "800," << highCBR_loss_rate << endl;
    cout << "600," << mediumCBR_loss_rate << endl;
    cout << "400," << lowCBR_loss_rate << endl;
    return 0;
}