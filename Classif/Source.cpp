#include<iostream>
#include<vector>
#include<string>
#include<cmath>
#include<random>
using namespace std;
using Data = vector<vector<double>>;
using std::cout;
struct Point
{
	double x;
	double y;
	Point() = default;
	Point(double a, double b) :x(a), y(b) {}
};
double L2(Point& p1, Point&p2)
{
	return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}
//Data dt = { {98,97,111,109,178,178,190,189,143},
//			{86,99,99,85,85,95,97,85,46} };
//Point c1b{ dt[0][0],dt[1][0] };
//Point c2b{ dt[0][4],dt[1][4] };
int n=100;
Data dt;
Point c1b;
Point c2b;
Point c1next{ 0,0 };
Point c2next{ 0,0 };
void randomInit()
{
	random_device rd;
	uniform_int_distribution<int> uid(25, 250);
	dt.emplace_back(vector<double>());
	dt.emplace_back(vector<double>());
	for (int i = 0; i < n; i++)
	{
		dt[0].push_back(uid(rd));
		dt[1].push_back(uid(rd));
	}
	c1b = Point(dt[0][0], dt[1][0]);
	c2b = Point(dt[0][dt.size() / 2], dt[1][dt.size() / 2]);
}
void HCM()
{
	Point c1 = c1b;
	Point c2 = c2b;
	vector<vector<int>> dkmp_hcm;
	dkmp_hcm.emplace_back(vector<int>(dt.begin()->size()));
	dkmp_hcm.emplace_back(vector<int>(dt.begin()->size()));
	double eps = 0.1;
	while (true)
	{
		for (int i = 0; i < dt.begin()->size(); i++)
		{
			double p1 = L2(c1, Point(dt[0][i], dt[1][i]));
			double p2 = L2(c2, Point(dt[0][i], dt[1][i]));
			if (p1 < p2)
			{
				dkmp_hcm[0][i] = 1;
				dkmp_hcm[1][i] = 0;
			}
			else
			{
				dkmp_hcm[0][i] = 0;
				dkmp_hcm[1][i] = 1;
			}
		}

		if (L2(c1, c1next) < eps&&L2(c2, c2next) < eps)
			break;

		c1next = c1;
		c2next = c2;

		double sum_x = 0;
		double sum = 0;
		double sum_y = 0;
		for (int i = 0; i < dt.begin()->size(); i++)
		{
			if (dkmp_hcm[0][i] > 0)
			{
				sum_x += dt[0][i];
				++sum;
				sum_y += dt[1][i];
			}
		}
		c1.x = sum_x / sum;
		c1.y = sum_y / sum;
		sum_x = 0;
		sum = 0;
		sum_y = 0;
		for (int i = 0; i < dt.begin()->size(); i++)
		{
			if (dkmp_hcm[1][i] > 0)
			{
				sum_x += dt[0][i];
				++sum;
				sum_y += dt[1][i];
			}
		}
		c2.x = sum_x / sum;
		c2.y = sum_y / sum;
	}
	cout << "x=" << c1.x << endl;
	cout << "y=" << c1.y << endl;
	cout << endl;
	cout << "x=" << c2.x << endl;
	cout << "y=" << c2.y << endl;
	/*cout << "Matrix: " << endl;

	for (int j = 0; j < dt.begin()->size(); j++)
	{
		for (int i = 0; i < 2; i++)
		{
			cout << dkmp_hcm[i][j] << " ";
		}
		cout << endl;
	}*/

}
void FCM()
{
	Point c1 = c1b;
	Point c2 = c2b;
	vector<vector<double>> dkmp;
	dkmp.emplace_back(vector<double>(dt.begin()->size()));
	dkmp.emplace_back(vector<double>(dt.begin()->size()));
	double eps = 0.3;
	while (true)
	{
		for (int i = 0; i < dt.begin()->size(); i++)
		{
			double p1 = L2(c1, Point(dt[0][i], dt[1][i]));
			double p2 = L2(c2, Point(dt[0][i], dt[1][i]));

			double temp = p1*p1*(1 / (p1*p1) + 1 / (p2*p2));
			if (p1 == 0)
				dkmp[0][i] = 1;
			else
				dkmp[0][i] = (1 / temp);

			temp = p2*p2*(1 / (p1*p1) + 1 / (p2*p2));
			if (p2 == 0)
				dkmp[1][i] = (1);
			else
				dkmp[1][i] = (1 / temp);
		}

		if (L2(c1, c1next) < eps&&L2(c2, c2next) < eps)
			break;
		c1next = c1;
		c2next = c2;
		double sum1 = 0;
		double sum2 = 0;
		double sum3 = 0;

		for (int i = 0; i < dt.begin()->size(); i++)
		{

			sum1 += dkmp[0][i] * dkmp[0][i] * dt[0][i];
			sum2 += dkmp[0][i] * dkmp[0][i] * dt[1][i];
			sum3 += dkmp[0][i] * dkmp[0][i];
		}
		c1.x = sum1 / sum3;
		c1.y = sum2 / sum3;

		sum1 = 0;
		sum2 = 0;
		sum3 = 0;
		for (int i = 0; i < dt.begin()->size(); i++)
		{

			sum1 += dkmp[1][i] * dkmp[1][i] * dt[0][i];
			sum2 += dkmp[1][i] * dkmp[1][i] * dt[1][i];
			sum3 += dkmp[1][i] * dkmp[1][i];
		}
		c2.x = sum1 / sum3;
		c2.y = sum2 / sum3;
	}
	cout << "x=" << c1.x << endl;
	cout << "y=" << c1.y << endl;
	cout << endl;
	cout << "x=" << c2.x << endl;
	cout << "y=" << c2.y << endl;
	/*cout << "Matrix: " << endl;

	for (int j = 0; j < dt.begin()->size(); j++)
	{
		for (int i = 0; i < 2; i++)
		{
			cout << dkmp[i][j] << " ";
		}
		cout << endl;
	}*/
}
void PCM()
{
	Point c1 = c1b;
	Point c2 = c2b;
	vector<vector<double>> dkmp;
	dkmp.emplace_back(vector<double>(dt.begin()->size()));
	dkmp.emplace_back(vector<double>(dt.begin()->size()));
	double eps = 0.3;
	double cof = 20;
	while (true)
	{
		for (int i = 0; i < dt.begin()->size(); i++)
		{
			double p1 = L2(c1, Point(dt[0][i], dt[1][i]));
			double p2 = L2(c2, Point(dt[0][i], dt[1][i]));

			double temp = (1 + (p1*p1 / (cof*cof)));
			dkmp[0][i] = (1 / temp);
			temp = (1 + (p2*p2 / (cof*cof)));
			dkmp[1][i] = (1 / temp);
		}

		if (L2(c1, c1next) < eps&&L2(c2, c2next) < eps)
		{
			break;
		}
		c1next = c1;
		c2next = c2;
		double sum1 = 0;
		double sum2 = 0;
		double sum3 = 0;

		for (int i = 0; i < dt.begin()->size(); i++)
		{

			sum1 += dkmp[0][i] * dkmp[0][i] * dt[0][i];
			sum2 += dkmp[0][i] * dkmp[0][i] * dt[1][i];
			sum3 += dkmp[0][i] * dkmp[0][i];
		}
		c1.x = sum1 / sum3;
		c1.y = sum2 / sum3;

		sum1 = 0;
		sum2 = 0;
		sum3 = 0;
		for (int i = 0; i < dt.begin()->size(); i++)
		{

			sum1 += dkmp[1][i] * dkmp[1][i] * dt[0][i];
			sum2 += dkmp[1][i] * dkmp[1][i] * dt[1][i];
			sum3 += dkmp[1][i] * dkmp[1][i];
		}
		c2.x = sum1 / sum3;
		c2.y = sum2 / sum3;
	}
	cout << "x=" << c1.x << endl;
	cout << "y=" << c1.y << endl;
	cout << endl;
	cout << "x=" << c2.x << endl;
	cout << "y=" << c2.y << endl;
	/*cout << "Matrix: " << endl;

	for (int j = 0; j < dt.begin()->size(); j++)
	{
		for (int i = 0; i < 2; i++)
		{
			cout << dkmp[i][j] << " ";
		}
		cout << endl;
	};*/
}
int main()
{
	randomInit();
	cout << "Start" << endl;
	cout << "x=" << c1b.x << endl;
	cout << "y=" << c1b.y << endl;
	cout << endl;
	cout << "x=" << c2b.x << endl;
	cout << "y=" << c2b.y << endl << endl;

	cout << "HCM" << endl;
	HCM();
	cout << endl << "FCM" << endl;
	FCM();
	cout << endl << "PCM" << endl;
	PCM();
	system("pause");

}
