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
};