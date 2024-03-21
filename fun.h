#pragma once

#include <time.h>
#include <random>
#include<cmath>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

vector<double> ran_dot(int x, int y)//生成随机点向量
{
    vector<double> doty;

    random_device rd;//随机数生成器配置
    default_random_engine e(rd());
	uniform_real_distribution<double> u(0,x);
    uniform_real_distribution<double> h(0,y);

    doty.push_back(u(e));//向量赋值
    doty.push_back(h(e));

    return doty;
}

double Gaus(int x, double miu, double t)//构造高斯函数并在指定x上取点
{
    double a;
    random_device rd;//随机数生成器配置，制造误差
    default_random_engine e(rd());
	uniform_real_distribution<double> u(-0.07,0.07);

    a = exp((-pow(x-miu, 2))/2/t)/sqrt(2*acos(-1)*t) + u(e);

    if(a < 0)
    {
        a = - a;
    }
	
    return a;
}


vector<int> pick_dot(int a)//输入最大值出现位置
{
    vector<int> g(5);//使用c储存5个模拟信号位置


    if(a > 1 && a < 49)
    {
    for (int i = 0; i < 5; i++)
    {
		g[i] = a-2+i;
    }
    }

    else if(a <= 1)
    {
        for (int i = 0; i < 5; i++)
    {
		g[i] = i;
    }
    }

    else 
    {
        for (int i = 0; i < 5; i++)
    {
		g[i] = 46 + i;
    }
    }

    return g;

}

double Sim_dot(vector<int> c, vector<double> d)
{
    MatrixXd matrix_X(5, 3);//将模拟点信息放入矩阵中
    VectorXd matrix_Z(5);
    VectorXd matrix_B(3);

    matrix_X = MatrixXd::Zero(5, 3);
    matrix_Z = VectorXd::Zero(5);
    matrix_B = VectorXd::Zero(3);

	for (int i = 0; i < 5; i++)
	{
		matrix_X(i, 0) = 1;
        matrix_X(i, 1) = c[i];
        matrix_X(i, 2) = pow(c[i], 2);
	}

    for (int i = 0; i < 5; i++)
	{
		matrix_Z(i) = log(d[i]);
	}

    //SVD分解/Qr分解对5个模拟点拟合
    matrix_B = matrix_X.bdcSvd(ComputeThinU | ComputeThinV).solve(matrix_Z);//SVD分解
    //matrix_B = matrix_X.colPivHouseholderQr().solve(matrix_Z);//QR分解

    
    double miu;
    miu = - matrix_B[1]/matrix_B[2]/2;

    if(miu < 0)
    {
        miu = 0;
    }

    else if(miu > 50)
    {
        miu = 50;
    }
    else 
    {

    }

    return miu;
}

vector<double> Sim(vector<double> v, vector<int> xy)
{
    int a;
    vector<int> c;//用c储存5个点的横坐标
    vector<double> d;//用d储存所有传感器信号/纵坐标
    vector<double> f;//用f储存取点纵坐标
    vector<double> e;//e储存最终拟合坐标

    e.clear();//清空向量e，避免重复调用出现问题

    for (int u = 0; u < 2; u++)//分别对生成点x，y坐标拟合
 {

    
    c.clear();
    d.clear();
    f.clear();

    for (int j = 0; j < xy[u]+1; j++)//生成尺寸x下每个探测器坐标
    {

    c.push_back(j);//将点横坐标放入c中
    d.push_back(Gaus(c[j], v[u], 1));//将点纵坐标放入d中

    }

    auto it = std::max_element(d.begin(), d.end());//取d中最大值
    a = distance(d.begin(), it);//取最大值处横坐标

    c.clear();//之前使用的c初始化

    
    c = pick_dot(a);//将点横坐标放入c中

    for (int j = 0; j < 5; j++)//取5个模拟点的纵坐标
    {

    f.push_back(d[c[j]]);

    }

    e.push_back(Sim_dot(c, f));//模拟点坐标放入e
 }

 /*
    cout << "模拟点坐标为 " << endl;//测试
	for (int i = 0; i < 5; i++)
	{
		cout << c[i] << "," << d[i] << endl;
	}
    cout << endl;
    
 */
    
    return e;
}
vector<double> par(vector<double> ex, int n)//输入点坐标与取点个数生成空间直线参数
{
    vector<double> u;
    double sum_xz = 0;
    double sum_x = 0;
    double sum_z = 0;
    double sum_z2 = 0;
    double sum_y = 0;
    double sum_yz = 0;
    double k1 = 0;
    double k2 = 0;
    double b1 = 0;
    double b2 = 0;

    u.clear();

    for (int i = 0; i < n; i++)//求sum_x
    {
        sum_x = sum_x + ex[3*i];
    }

    for (int i = 0; i < n; i++)//求sum_y
    {
        sum_y = sum_y + ex[3*i+1];
    }

    for (int i = 0; i < n; i++)//求sum_z
    {
        sum_z = sum_z + ex[3*i+2];
    }

    for (int i = 0; i < n; i++)//求sum_z2
    {
        sum_z2 = sum_z2 + pow(ex[3*i+2], 2);
    }

    for (int i = 0; i < n; i++)//求sum_xz
    {
        sum_xz = sum_xz + ex[3*i]*ex[3*i+2];
    }

    for (int i = 0; i < n; i++)//求sum_yz
    {
        sum_yz = sum_yz + ex[3*i+1]*ex[3*i+2];
    }

    k1 = (n*sum_xz - sum_x*sum_z)/(n*sum_z2 - pow(sum_z, 2));
    b1 = (sum_x - k1*sum_z)/n;
    k2 = (n*sum_yz - sum_y*sum_z)/(n*sum_z2 - pow(sum_z, 2));
    b2 = (sum_y - k2*sum_z)/n;

    u.push_back(k1);
    u.push_back(b1);
    u.push_back(k2);
    u.push_back(b2);

    return u;
}

vector<double> line_dot(vector<double> gx, double z)
{
    vector<double> d(3);

    d.clear();

    d.push_back(gx[0]*z + gx[1]);
    d.push_back(gx[2]*z + gx[3]);
    d.push_back(z);

    return d;
}

double distance_dot(vector<double> v, vector<double> e)//给出两点间距离
{
    double o;

    o = pow(pow(v[0]-e[0],2) + pow(v[1]-e[1],2) + pow(v[2]-e[2],2),0.5);

    return o;
}