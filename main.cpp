// opengl32 glu32    glut32

#include <iostream>
#include <time.h>
#include <cstdlib>
#include <GL/glut.h>

#include<stdio.h>
#include<stdlib.h>
#include <locale.h>
#include<windows.h>
#include<math.h>
#include<conio.h>

#include <vector>
#include <cmath>

#include <dos.h>

/************************************/
/*
������ ����

����������� ������� ��������
    � ����������� ����������, �� ������� ���������� ������ ���� ������� ��� ������������.

    d = 2 * 10^-10 [�], ������� � ������� ����� �������� ����� �������� r = 10^-10 [�]

������ ���� ������� �����, ����� �������

2 * 10^-10 [�] = 4 [���� ������ ]

���� ���� ������� 500 � 500 [���� ������ ]

*/

/*********** ���������� ����������***************/

class box2D* my_box;
float fps = 25;
//����� ��� ����� ��� �� � ����������� ������
//� ��� ����� ���� 7*10^-11 �, �  � ����� 23 � �
/*�� ���������� ������ �� ������:

\[\frac{m}/{d^2} \cdot \frac{10^{-26}}{25*10^{-22}} \cdot 0.0014*6.67*10^{-11}*10^{-11}\]

������� �� ������� �������������� ���������� �� �������

\[ a t = 0.37*10^6 \cdot \frac{m}/{d^2} \]

������ �� ����� 7*0.01*V / 5
*/

/*********************************************************/

class box2D{
private:
    double x;
    double y;
    class molecule* fe;
public:
    class molecule* getFE(){
        return fe;
    };

    void setFE(class molecule* temp){
        fe = temp;
    }

    void setXY(int a, int b){
        x = a;
        y = b;
    }

    double getY(){
        return y;
    }

    double getX(){
        return x;
    }

    void movement();

    void info();
};

class molecule{
public:
    //�����
    double m;//10^-26 kg

    //��������
    double vx;
    double vy;

    //������ ������������
    double r;

    //����������
    double xp;
    double yp;

    molecule* next;
};

void create(box2D* cur_box);

void display();

void stat_pic();

void dynamic_pic();

//������� ��������� ��������, �� ���������� �� �������
int rand_num(int minim, int maxim);

int main(int argc, char **argv)
{
    my_box = new box2D;
    my_box->setXY(500, 500);
    create(my_box);

    srand(time(NULL));
    /**********************************/
    //���������� � �������� ����
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    //������ ����
    glutInitWindowSize(my_box->getX(),my_box->getY());

    //��������� ����
    glutCreateWindow("�������� �������");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //���� ���������
    gluOrtho2D(-20, my_box->getX() + 20, -20, my_box->getY() + 20);

    glutDisplayFunc(display);

    glutIdleFunc(display);//��������� ���� �������, ������� dislay ��� ����� ����������

    //������ ���� glutMainLoop ().
    glutMainLoop();
    /*************************************/

    //������� ��������

}

void display()
{
    int t1 = clock();//����� � ������� ������� ��������� �� ������ ������ ��������
/***************************/
    glClear(GL_COLOR_BUFFER_BIT);//����� ���������

    //������ ���� ����, ������ ��� ��������� ������� ������� �����, � ���������, ��� ����������
    glClearColor(0.1, 0.1, 0.1, 0.5);//����� � ������ ����� ����, ��������������

    glTranslatef(0, 0, 0); //����� ������ ������� ���������, � �� ���� �������, ������� ������� ���� ����
/**********************/
    //�������� ������
    //��-�������� �� �� ������ ���� ��������, � ���������������� �������� � 1*4
    stat_pic();

    //������� ������� �������, ���� ��� �������� ��������� � ������� ���� ������ �� ��� ��������
    dynamic_pic();

    //���������� ��������
    my_box->movement();

    //glFlush();//���� ����� ��� ����������, �������� ��������

    //������� ��������
    int t2 = clock();
    if((t2 - t1) < (1/fps)){
        Sleep((1000/fps) - (t2 - t1));//0.043 <=> 1/23 ��� <=>...
    }
    //std::cout<<t2<<std::endl;
    printf("OtladkKKa\n");
    my_box->info();
    glFlush();
}

void box2D::info(){
    std::cout<<"Chirina polya: "<<my_box->getX()<<std::endl;
    std::cout<<"Vysota polya: "<<my_box->getY()<<std::endl;
    molecule* temp = my_box->getFE();
    while(temp){
        std::cout<<"Ckorost x: "<<temp->vx<<"   Ckorost y:  "<<temp->vy<<std::endl;
        std::cout<<"Posicya x: "<<temp->xp<<"   Posicya y:  "<<temp->yp<<std::endl;
        temp = temp->next;
    }
}

void box2D::movement(){

    molecule* root = my_box->getFE();
    molecule* curM = root;
    molecule* cur = root;
    /*������� �� ������� �������������� ���������� �� �������
    \[ a t = 0.37*10^6 \cdot \frac{m}/{d^2} \]
    ������ �� ����� 7*0.01*V / 5*/

    //����� �������, ��� ���� ��������� �� ����������!! �� ����� �����������
    //� ������� ������ ������� �������, �� �����?

    while(curM){
        while(cur){

            if(cur == curM){
                cur = cur->next;
                continue;
            }

            curM->vx += 37*1*cur->m/(curM->xp - cur->xp);
            curM->vy += 37*1*cur->m/(curM->yp - cur->yp);

            cur = cur->next;
        }
        double x_temp;
        double y_temp;
        //���� � ������� � ����� ���������
        if(abs(curM->vx) >= 100){x_temp = curM->vx*7*0.01/5;}
        if(abs(curM->vx) < 100 && abs(curM->vx) > 10){x_temp = curM->vx*7*0.1/5;}
        if(abs(curM->vx) <= 10) {x_temp = curM->vx*7/5;}

        if(abs(curM->vy) >= 100){y_temp = curM->vy*7*0.01/5;}
        if(abs(curM->vy) < 100 && abs(curM->vx) > 10){y_temp = curM->vy*7*0.1/5;}
        if(abs(curM->vy) <= 10) {y_temp = curM->vy*7/5;}


        if((x_temp + curM->r) >=(my_box->getX())){
            curM->vx = (-1)*(curM->vx);
            curM->xp = (my_box->getX() - curM->r)-20;
        }
        else{
            if((x_temp - curM->r) <= 0){
            curM->vx = (-1)*(curM->vx);
            curM->xp = (0 + curM->r)+20;
            }
            else{
                curM->xp = x_temp;
            }
        }

        if((y_temp + curM->r) >=(my_box->getY())){
            curM->vy = (-1)*(curM->vy);
            curM->yp = (my_box->getY() - curM->r)-20;
        }
        else{
            if((y_temp - curM->r) <= 0){
            curM->vy = (-1)*(curM->vy);
            curM->yp = (0 + curM->r)+20;
            }
            else{
                curM->yp = y_temp;
            }
        }
        if(curM->vx > 800){
            curM->vx = 500;
        }
        if(curM->vy > 800){
            curM->vy = 500;
        }
        if(curM->vx < -800){
            curM->vx = -500;
        }
        if(curM->vy < -800){
            curM->vy  = -500;
        }
        curM = curM->next;
    }
}

void stat_pic(){

    //������ ������
    glBegin(GL_LINES);//����� �������� ������
        glColor3f(0.0, 1.0, 0.0);//������������� ���� ����������
        glVertex2f(0, 0);//����� ������ �� ����� ������ � �����
        glVertex2f(0, my_box->getY());
        glVertex2f(0, 0);//������ ������ �� ����� ������ � �����
        glVertex2f(my_box->getX(), 0);
        glVertex2f(0, my_box->getY());//������� ������ �� ����� ������ � �����
        glVertex2f(my_box->getX(), my_box->getY());
        glVertex2f(my_box->getX(), my_box->getY());//������ ������ �� ����� ������ � �����
        glVertex2f(my_box->getX(), 0);
    glEnd();
}

void dynamic_pic(){
molecule* cur = my_box->getFE();
    //std::cout<<cur->next<<std::endl;

    while(cur){

    //std::cout<<(cur->xp - cur->r)<<std::endl;
    //std::cout<<(cur->vx)<<std::endl;
    glBegin(GL_QUADS);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2i((cur->xp - cur->r),(cur->yp - cur->r));
        glVertex2i((cur->xp - cur->r),(cur->yp + cur->r));
        glVertex2i((cur->xp + cur->r),(cur->yp + cur->r));
        glVertex2i((cur->xp + cur->r),(cur->yp - cur->r));
    glEnd();

        cur = cur->next;
    }
}

void create(box2D* cur_box){

    molecule* temp = new molecule;
    molecule* saver = temp;
    temp->next = NULL;
    temp->vx = 500;
    temp->vy = 10;
    temp->xp = 60;
    temp->yp = 40;
    temp->r = 2;
    temp->m = 2;
    for(int i = 2; i < 6; ++i){
        temp->next = new molecule;
        temp->next->next = NULL;
        temp = temp->next;
        temp->xp = 60*i;
        temp->yp = 40*i;
        temp->r = 2;
        temp->vx = rand_num(-499, 499);
        temp->vy = 28;
        temp->m = 2;
    }
    cur_box->setFE(saver);
}

int rand_num(int minim, int maxim){

    int a = 0;

    if (minim > 0){
		a = minim+ rand() % (maxim- minim+ 1);
	}

    else{
    	a = minim + rand() % (abs(minim) + maxim+ 1);
	}

    printf("Otladka. Sgenerirovano: %d\n", a);

	return a;
}
