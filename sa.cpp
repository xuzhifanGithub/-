#include"sa.h"

struct BestPos
{
	double x;
	double y;
	double value;

};

//ģ���˻��㷨,������|x|<=5,���Ž�f=-1.0316285
void SA()
{
	int iter = 100;//��ѭ����������,��ΪL =100
	double alpha = 0.99; //����ϵ����alpha = 0.99
	double T0 = 100; //��ʼ�¶�T0Ϊ100
	double TF = 0.01; //�¶���ֵTfΪ0.01
	int count = 0;
	double T = T0;
	double f_old,f_new;
	double x_old , y_old;
	double x_new, y_new;

	//��ʼ��
	x_old = rand() % 10 - 5;
	y_old = rand() % 10 - 5;
	f_old = fun(x_old, y_old);

	BestPos bestPos;
	bestPos.x = x_old;
	bestPos.y = y_old;
	bestPos.value = f_old;
	

	while (T > TF)
	{
		count++;
		for (int i = 0; i < iter; ++i)
		{
			x_new = x_old;
			y_new = y_old;
			generate_new(x_new, y_new, T);//�����½�
			f_new = fun(x_new, y_new);

			if (metrospolis(f_old, f_new, T))
			{
				x_old = x_new; y_old = y_new;
				f_old = f_new;
			}

		}
		//printf("sa_info [iter:%d pos(%f,%f) min value:%f]\n", count, x_new, y_new, f_new);

		if (f_new < bestPos.value)
		{
			bestPos.x = x_new;
			bestPos.y = y_new;
			bestPos.value = f_new;
		}

		T *= alpha;
	}

	printf("SAģ���˻�:\npos(%f,%f)\nmin value:%f;\n", bestPos.x, bestPos.y, bestPos.value);

}

/*double fun(double x, double y)
{
	double res = 4 * pow(x, 2) - 2.1 * pow(x, 4) + pow(x, 6) / 3.0
		+ x * y - 4 * pow(y, 2) + 4 * pow(y, 4);
	return res;
}*/

//Metropolis׼��
int metrospolis(double f_old, double f_new,double t)
{
	if (f_new <= f_old)
	{
		return 1;
	}
	else
	{
		double randX = (rand() % 100) / 100.0;
		
		if (randX < exp((f_old - f_new) / t))
		{	
			return 1;
		}
		else
		{
			return 0;
		}
		

	}
}

void generate_new(double& x, double& y,double T)
{
	double xNew, yNew;
	while (true)
	{
		xNew = x + T * ((rand() % 100) / 100.0 - (rand() % 100) / 100.0);
		yNew = y + T * ((rand() % 100) / 100.0 - (rand() % 100) / 100.0);
		
		if (xNew >= -5 && xNew <= 5 && yNew >= -5 && yNew <= 5)
		{
			break;
		}

	}
	x = xNew;
	y = yNew;
}

