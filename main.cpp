//主程序

#include <iostream>
#include <vector>
#include <time.h>
#include <random>
#include<cmath>
#include <Eigen/Dense>
#include "fun.h"//自定义的函数库


using namespace std;
using namespace Eigen;

vector<double> ran_dot(int x, int y);//随机点生成器
double Gaus(int x, double miu, double t);//高斯函数
vector<int> pick_dot(int a);//得到模拟点坐标
double Sim_dot(vector<int> c, vector<double> d);//得到拟合高斯函数的期望值
vector<double> Sim(vector<double> v, vector<int> xy);//输入生成点信息，得到拟合点
vector<double> par(vector<double> ex, int n);//输入点坐标与取点个数生成空间直线参数
vector<double> line_dot(vector<double> gx, double z);//获取直线上某点坐标
double distance_dot(vector<double> v, vector<double> e);//给出两点间距离

int main()
{
    vector<double> v1;//储存两个模拟点位置
    vector<double> v2;
    vector<double> v3;
    vector<double> v4;
    vector<double> gx;//储存真实直线参数
    vector<double> ex;
    vector<int> xy(2);//储存探测器尺寸信息
    double d = 50;//平板间隔

    xy[0] = 50;
    xy[1] = 50;//探测器尺寸

    v1 = ran_dot(xy[0], xy[1]);//获得在50*50范围内的随机点
  // v1.push_back(49.23);
   // v1.push_back(0.22);

    v3 = ran_dot(xy[0], xy[1]);
    v1.push_back(0);
    v3.push_back(d*2);

    ex = v1;
    ex.push_back(v3[0]);
    ex.push_back(v3[1]);
    ex.push_back(v3[2]);

    gx = par(ex, 2);
    v2 = line_dot(gx, d);
    

    cout << "生成点1为 ";//测试
	for (int i = 0; i < 3; i++)
	{
		cout << v1[i] << " ";
	}
    cout << endl;

    cout << "生成点2为 ";
	for (int i = 0; i < 3; i++)
	{
		cout << v2[i] << " ";
	}
    cout << endl;

    cout << "生成点3为 ";//测试
	for (int i = 0; i < 3; i++)
	{
		cout << v3[i] << " ";
	}
    cout << endl;

    vector<double> e1;//e储存最终拟合点坐标
    vector<double> e2;
    vector<double> e3;
    vector<double> e4;
    vector<double> dx;//用于储存拟合直线系数
    int n = 3;//取点个数/探测器平面数

    e1 = Sim(v1, xy);
    e1.push_back(0);

    cout << endl;

    cout << "拟合点1为: ";
	for (int i = 0; i < 3; i++)
	{
		cout << e1[i] << " ";
	}

    cout << endl;

    e2 = Sim(v2, xy);
    e2.push_back(d);

    cout << endl;

    cout << "拟合点2为: ";
	for (int i = 0; i < 3; i++)
	{
		cout << e2[i] << " ";
	}

    cout << endl;

    e3 = Sim(v3, xy);
    e3.push_back(2*d);

    cout << endl;

    cout << "拟合点3为: ";
	for (int i = 0; i < 3; i++)
	{
		cout << e3[i] << " ";
	}

    ex.clear();

    ex = e1;
    ex.push_back(e2[0]);
    ex.push_back(e2[1]);
    ex.push_back(e2[2]);
    ex.push_back(e3[0]);
    ex.push_back(e3[1]);
    ex.push_back(e3[2]);
    dx = par(ex, n);

    cout << endl;

    cout << "真实系数为: " << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << gx[i] << endl;
	}

    cout << "拟合系数为: " << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << dx[i] << endl;
	}

    cout << "拟合点误差（由点距离给出）: " << endl;
	
	cout << "点" << 1 << "为" << distance_dot(v1,e1) << endl;
    cout << "点" << 2 << "为" << distance_dot(v2,e2) << endl;
    cout << "点" << 3 << "为" << distance_dot(v3,e3) << endl;
	

    return 0;
}




