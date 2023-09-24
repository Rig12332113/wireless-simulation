#include <iostream>
#include <random>
#include "hexagon.hpp"
#define PI 3.1415926
#define peoplenum 100
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
int cal_length(Point a, Point b){
    return sqrt((a.getx() - b.getx()) * (a.getx() - b.getx()) + (a.gety() - b.gety()) * (a.gety() - b.gety()));
}
int switch_judge(mobile *people, Hexagon *graph, int k, int j){
    float interference1 = 0, interference2 = 0;
    float power1, power2;
    float noise = (1.38 * 300 * pow(10, -13));
    float distance1 = cal_length(people[j].get_place(), graph[people[j].get_cell()].getC());
    float distance2 = cal_length(people[j].get_place(), graph[k].getC());

    for(int i = 0; i < peoplenum; i++){
        float distance3 = cal_length(people[i].get_place(), graph[people[j].get_cell()].getC());
        float distance4 = cal_length(people[i].get_place(), graph[k].getC());
        if (i != j){
            interference1 += pow(10, 5.1) * (51.5 * 1.5) * (51.5 * 1.5) / pow(distance3, 4);
            interference2 += pow(10, 5.1) * (51.5 * 1.5) * (51.5 * 1.5) / pow(distance4, 4);
        }
        else{
            power1 = 51 + 10 * log10((51.5 * 1.5) * (51.5 * 1.5) / pow(distance1, 4));
            power2 = 51 + 10 * log10((51.5 * 1.5) * (51.5 * 1.5) / pow(distance2, 4));
        }
    }
    float sinr1 = power1 - 10 * log10(interference1 + noise);
    float sinr2 = power2 - 10 * log10(interference2 + noise);
    return sinr1 > sinr2 ? people[j].get_cell() : k;
}
int main(void){
    //cluster 生成
    Clusters clusters[7];
    Point zero, one, two, three, four, five, six;           //cluster center coordinate
    zero.setx(0);
    zero.sety(0);
    one.setx(-500 * sqrt(3));
    one.sety(2000);
    two.setx(2250 / sqrt(3));
    two.sety(1750);
    three.setx(3750 / sqrt(3));
    three.sety(-250);
    four.setx(500 * sqrt(3));
    four.sety(-2000);
    five.setx(-2250 / sqrt(3));
    five.sety(-1750);
    six.setx(-3750 / sqrt(3));
    six.sety(250);
    
    clusters[0].set_cluster(zero);
    clusters[1].set_cluster(one);
    clusters[2].set_cluster(two);
    clusters[3].set_cluster(three);
    clusters[4].set_cluster(four);
    clusters[5].set_cluster(five);
    clusters[6].set_cluster(six);
    //for(int i = 0; i < 7; i++)
        //clusters[i].printCluster();

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> radius_gen(0.0, 900);
    uniform_real_distribution<> degree_gen(0.0, 2 * PI);
    uniform_int_distribution<> speed_gen(1, 15);
    uniform_int_distribution<> time_gen(1, 6);
    mobile *people = new mobile[peoplenum];
    int count = 0;
    for (int i = 0; i < peoplenum; i++){
        people[i].set_place(radius_gen(gen) * cos(degree_gen(gen)), radius_gen(gen) * sin(degree_gen(gen)));
        people[i].set_time(degree_gen(gen));
        people[i].set_speed(speed_gen(gen));
        people[i].set_degree(degree_gen(gen));
        for (int j = 0; j < 19; j++){
            if (inHexagon(people[i].get_place(),clusters[0].get_hexagon(j))){
                people[i].set_cell(j);
            }
        }
        cout << people[i].get_place().getx() << "," << people[i].get_place().gety() << endl;
        cout << "" << endl;
    }
    cout << "Time(s)" << "," << "Source cell ID," << "Destination cell ID" << endl;
    for (int i = 900; i > 0; i--){
        for(int j = 0; j < peoplenum; j++){
            if (people[j].get_time() == 1){
                people[j].set_place(people[j].get_place().getx() + people[j].get_speed() * cos(people[j].get_degree())
                                  , people[j].get_place().gety() + people[j].get_speed() * sin(people[j].get_degree()));
                people[i].set_time(degree_gen(gen));
                people[i].set_speed(speed_gen(gen));
                people[i].set_degree(degree_gen(gen));
            }
            else{
                people[j].set_place(people[j].get_place().getx() + people[j].get_speed() * cos(people[j].get_degree())
                                  , people[j].get_place().gety() + people[j].get_speed() * sin(people[j].get_degree())); 
                people[j].set_time(people[j].get_time() - 1);
            }
        }
        for (int j = 0; j < peoplenum; j++){
            int found = 0;
            for (int m = 0; m < 7 && found == 0; m++){
                for (int k = 0; k < 19 && found == 0; k++){
                    if (inHexagon(people[j].get_place(), clusters[m].get_hexagon(k))){
                        if (k != people[j].get_cell()){
                            //利用SINR判斷是否handoff
                            int cellChange = switch_judge(people, clusters[m].get_hexagon_list(), k, j);
                            if (cellChange == k){
                                cout << 901 - i << "," << people[j].get_cell() << "," << k << endl;
                                count++;
                                people[j].set_cell(k);
                            }
                        }
                        found = 1;
                    }
                }
            }
        }
    }
    cout << count << endl;
}