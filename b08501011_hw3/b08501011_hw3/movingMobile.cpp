#include <iostream>
#include <random>
#include "hexagon.hpp"
#define PI 3.1415926
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
int main(void){
    //六角形生成
    Hexagon *graph = new Hexagon[19];
    //中心
    graph[0].setCenter(0, 0);
    //第一圈
    graph[1].setCenter(0, 500);
    graph[2].setCenter(250 * sqrt(3), 250);
    graph[3].setCenter(250 * sqrt(3), -250);
    graph[4].setCenter(0, -500);
    graph[5].setCenter(-250 * sqrt(3), -250);
    graph[6].setCenter(-250 * sqrt(3), 250);
    //第二圈
    graph[7].setCenter(0, 1000);
    graph[8].setCenter(250 * sqrt(3), 750);
    graph[9].setCenter(500 * sqrt(3), 500);
    graph[10].setCenter(500 * sqrt(3), 0);
    graph[11].setCenter(500 * sqrt(3), -500);
    graph[12].setCenter(250 * sqrt(3), -750);
    graph[13].setCenter(0, -1000);
    graph[14].setCenter(-250 * sqrt(3), -750);
    graph[15].setCenter(-500 * sqrt(3), -500);
    graph[16].setCenter(-500 * sqrt(3), 0);
    graph[17].setCenter(-500 * sqrt(3), 500);
    graph[18].setCenter(-250 * sqrt(3), 750);

    for(int i = 0; i < 19; i++){
        graph[i].getTL().printPoint();
        graph[i].getTR().printPoint();
        graph[i].getR().printPoint();
        graph[i].getBR().printPoint();
        graph[i].getBL().printPoint();
        graph[i].getL().printPoint();
        graph[i].getTL().printPoint();
        cout << "" << endl;
    }
    
    //亂數移動
    Point startpoint;
    startpoint.setx(250);
    startpoint.sety(0);
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> degree_gen(0.0, 2 * PI);
    uniform_int_distribution<> speed_gen(1, 15);
    uniform_int_distribution<> time_gen(1, 6);
    int clock = 0;
    float degree = degree_gen(gen);
    int speed = speed_gen(gen);
    int time = time_gen(gen);
    int currentzone = 0, zonechange = 0;
    for(int i = 0; i < 19; i++){ 
        if (inHexagon(startpoint, graph[i])){
            currentzone = i;
            break;
        }
    }
    cout << "Time(s)" << "," << "Source cell ID," << "Destination cell ID" << endl;
    while(clock + time <= 900){
        //cout << startpoint.getx() << "," << startpoint.gety() << endl;
        for (int i = 1; i <= time; i++){
            startpoint.setx(startpoint.getx() + cos(degree) * speed);
            startpoint.sety(startpoint.gety() + sin(degree) * speed);
            for(int i = 0; i < 19; i++){ 
                if (inHexagon(startpoint, graph[i])){
                    if (currentzone != i){
                        //cout << "zone change :," << clock << "," << currentzone << "," << i << endl;
                        cout << clock << "," << currentzone << "," << i << endl;
                        currentzone = i;
                        zonechange++;
                    }
                    break;
                }
            }   
            clock++;
        }
        degree = degree_gen(gen);
        speed = speed_gen(gen);
        time = time_gen(gen);
    }
    //cout << startpoint.getx() << "," << startpoint.gety() << endl;
    for (int i = 1; i <= 900 - clock; i++){
            startpoint.setx(startpoint.getx() + cos(degree) * speed);
            startpoint.sety(startpoint.gety() + sin(degree) * speed);
            for(int i = 0; i < 19; i++){ 
                if (inHexagon(startpoint, graph[i])){
                    if (currentzone != i){
                        cout << clock << "," << currentzone << "," << i << endl;
                        currentzone = i;
                        zonechange++;
                    }
                    break;
                }
            }   
            clock++;
        }
    //cout << startpoint.getx() << "," << startpoint.gety() << endl;
    cout << zonechange << endl;
    return 0;
}