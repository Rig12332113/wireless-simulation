#include <iostream>
#include <cmath>
using namespace std;
class Point{
    float x, y;
    public:
        float getx(){
            return x;
        }
        float gety(){
            return y;
        }
        void setx(float a){
            x = a;
        }
        void sety(float b){
            y = b;
        }
        void printPoint(){
            cout << x << "," << y << endl;
        }
};
class Hexagon{
    Point center;  
    public:
        void setCenter(int a, int b){
            center.setx(a);
            center.sety(b);
        }
        Point getC(){
            return center;
        }
        Point getTL(){
            Point topLeft;
            topLeft.setx(center.getx() - 250 / sqrt(3));
            topLeft.sety(center.gety() + 250);
            return topLeft;
        }
        Point getTR(){
            Point topRight;
            topRight.setx(center.getx() + 250 / sqrt(3));
            topRight.sety(center.gety() + 250);
            return topRight;
        }
        Point getL(){
            Point Left;
            Left.setx(center.getx() - 500 / sqrt(3));
            Left.sety(center.gety());
            return Left;
        }
        Point getR(){
            Point Right;
            Right.setx(center.getx() + 500 / sqrt(3));
            Right.sety(center.gety());
            return Right;
        }
        Point getBL(){
            Point bottomLeft;
            bottomLeft.setx(center.getx() - 250 / sqrt(3));
            bottomLeft.sety(center.gety() - 250);
            return bottomLeft;
        }
        Point getBR(){
            Point bottomRight;
            bottomRight.setx(center.getx() + 250 / sqrt(3));
            bottomRight.sety(center.gety() - 250);
            return bottomRight;
        }
        void printHexagon(){
            getTL().printPoint();
            getTR().printPoint();
            getR().printPoint();
            getBR().printPoint();
            getBL().printPoint();
            getL().printPoint();                
            getTL().printPoint();
            cout << "" << endl;
        }
};
class Clusters{
    Hexagon cluster[19];
    public:
        void set_cluster(Point a){
            //中心
            cluster[0].setCenter(a.getx(), a.gety());
            //第一圈
            cluster[1].setCenter(a.getx(), a.gety() + 500);
            cluster[2].setCenter(a.getx() + 250 * sqrt(3), a.gety() + 250);
            cluster[3].setCenter(a.getx() + 250 * sqrt(3), a.gety() - 250);
            cluster[4].setCenter(a.getx(), a.gety() - 500);
            cluster[5].setCenter(a.getx() - 250 * sqrt(3), a.gety() - 250);
            cluster[6].setCenter(a.getx() - 250 * sqrt(3), a.gety() + 250);
            //第二圈
            cluster[7].setCenter(a.getx(), a.gety() + 1000);
            cluster[8].setCenter(a.getx() + 250 * sqrt(3), a.gety() + 750);
            cluster[9].setCenter(a.getx() + 500 * sqrt(3), a.gety() + 500);
            cluster[10].setCenter(a.getx() + 500 * sqrt(3), a.gety());
            cluster[11].setCenter(a.getx() + 500 * sqrt(3), a.gety() - 500);
            cluster[12].setCenter(a.getx() + 250 * sqrt(3), a.gety() - 750);
            cluster[13].setCenter(a.getx(), a.gety() - 1000);
            cluster[14].setCenter(a.getx() - 250 * sqrt(3), a.gety() - 750);
            cluster[15].setCenter(a.getx() - 500 * sqrt(3), a.gety() - 500);
            cluster[16].setCenter(a.getx() - 500 * sqrt(3), a.gety());
            cluster[17].setCenter(a.getx() - 500 * sqrt(3), a.gety() + 500);
            cluster[18].setCenter(a.getx() - 250 * sqrt(3), a.gety() + 750);
        }
        Hexagon get_hexagon(int index){
            return cluster[index];
        }
        Hexagon *get_hexagon_list(){
            return cluster;
        }
        void printCluster(){
            for(int i = 0; i < 19; i++){
                cluster[i].getTL().printPoint();
                cluster[i].getTR().printPoint();
                cluster[i].getR().printPoint();
                cluster[i].getBR().printPoint();
                cluster[i].getBL().printPoint();
                cluster[i].getL().printPoint();
                cluster[i].getTL().printPoint();
                cout << "" << endl;
            }
        }
};
class mobile{
    Point place;
    float shannon_capacity, distance;

    public:
        void set_place(float a, float b){
            place.setx(a);
            place.sety(b);
        }
        void set_capacity(float c){
            shannon_capacity = c;
        }
        void set_distance(float length){
            distance = length;
        }
        Point get_place(){
            return place;
        }
        float get_distance(){
            return distance;
        }
        float get_capacity(){
            return shannon_capacity;
        }
};