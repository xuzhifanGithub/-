#include"ac.h"

const int ant_num = 300;//��Ⱥ����
const int max_iteration = 100; // ����������
double rho = 0.9;//��Ϣ�ػӷ�����
double p0 = 0.2;//״̬ת�Ƴ���
double step = 0.01;//����
double tau[ant_num];//��Ϣ�ؾ���
double p[ant_num];//״̬ת�Ƹ���
double iter_min_value[max_iteration];//ÿ�ε�������ֵ

void AC()
{
	POS point[ant_num];

	//��ʼ��
	for (int i = 0; i < ant_num; i++)
	{
		point[i].x = (double)rand() / RAND_MAX * 10.0 - 5.0;
		point[i].y = (double)rand() / RAND_MAX * 10.0 - 5.0;
		tau[i] = 0;
	}

	double minn, maxx;
	for (int iter = 0; iter < max_iteration; iter++)
	{
		//��ʾ
		//printf("%d:\npos(%f,%f)min value:%f;\n", iter, point[1].x, point[1].y, fun(point[1].x, point[1].y));
		minn = 8888888;
		int minId = 0;
		for (int i = 0; i < ant_num; i++)
		{
			if (fun(point[i].x, point[i].y) < minn)
			{
				minId = i;
				minn = fun(point[i].x, point[i].y);
			}
		}
		iter_min_value[iter] = minn;

		minn = 8888888;
		maxx = -888888;
		for (int i = 0; i < ant_num; i++)
		{
			tau[i] += fun(point[i].x, point[i].y);
			minn = min(minn, tau[i]);
			maxx = max(maxx, tau[i]);
		}

		for (int i = 0; i < ant_num; i++)
		{
			tau[i] -= minn + 1e-6;
		}

		for (int i = 0; i < ant_num; i++)
		{
			p[i] = tau[i] / (maxx - minn);

			if (p[i] < p0)
			{
				do
				{
					point[i].x += rand() % 10 / 10.0 * step;
				} while (point[i].x < -5 || point[i].x > 5);
				
				do
				{
					point[i].y += rand() % 10 / 10.0 * step;
				} while (point[i].y < -5 || point[i].y > 5);
				
			}
			else
			{
				point[i].x = (double)rand() / RAND_MAX * 10.0 - 5.0;
				point[i].y = (double)rand() / RAND_MAX * 10.0 - 5.0;
			}
		}

		//������Ϣ��
		for (int i = 0; i < ant_num; i++)
		{
			tau[i] += minn + 1e-5;
			tau[i] *= (1 - rho);
		}


	}

	minn = 8888888;
	int minId = 0;
	for (int i = 0; i < ant_num; i++)
	{
		if (fun(point[i].x, point[i].y) < minn)
		{
			minId = i;
			minn = fun(point[i].x, point[i].y);
		}
	}

	for (int i = 0; i < max_iteration; i++)
	{
		if (iter_min_value[i] < minn)
		{
			minn = iter_min_value[i];
		}
	}


	printf("AC��Ⱥ:\npos(%f,%f)\nmin value:%f;\n", point[minId].x, point[minId].y, minn);
}

/*void AC()
{
	POS point[ant_num];

	for (int i = 0; i < ant_num; i++)
	{
		point[i].x = (double)rand() / RAND_MAX * 10.0 - 5.0;
		point[i].y = (double)rand() / RAND_MAX * 10.0 - 5.0;
		tau[i] = 0;
	}

	double minn, maxx;
	for (int i = 0; i < max_iteration; i++)
	{

		//printf("%d:\npos(%f,%f)min value:%f;\n",i, point[1].x, point[1].y, fun(point[1].x, point[1].y));
		minn = 8888888;
		maxx = -888888;
		for (int i = 0; i < ant_num; i++)
		{
			tau[i] += fun(point[i].x, point[i].y);
			minn = min(minn, tau[i]);
			maxx = max(maxx, tau[i]);
		}

		

		for (int i = 0; i < ant_num; i++)
		{
			p[i] = (maxx -tau[i]) / maxx;

			if (p[i] >  p0)
			{
				point[i].x += rand() % 10 / 10.0 * step;
				point[i].y += rand() % 10 / 10.0 * step;
			}
			else
			{
				point[i].x = (double)rand() / RAND_MAX * 10.0 - 5.0;
				point[i].y = (double)rand() / RAND_MAX * 10.0 - 5.0;
			}
		}

		//������Ϣ��
		for (int i = 0; i < ant_num; i++)
		{
			tau[i] *= (1 - rho);
		}
	}

	minn = 8888888;
	int minId = 0;
	for (int i = 0; i < ant_num; i++)
	{
		if (fun(point[i].x, point[i].y) < minn)
		{
			minId = i;
			minn = fun(point[i].x, point[i].y);
		}
	}


	printf("AC:\npos(%f,%f)\nmin value:%f;\n", point[minId].x, point[minId].y, minn);
}*/