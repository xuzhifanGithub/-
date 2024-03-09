#include"pso.h"

struct POP
{
	double x;
	double y;
	double value;
	double x_v;
	double y_v;
};

struct ITER_INFO
{
	double x;
	double y;
	double value;
};

struct P_BEST
{
	double x;
	double y;
	double value;
};

struct G_BEST
{
	double x;
	double y;
	double value;
};

const double c1 = 1.5; //���ٶ�����һ���Ǹ��ݴ���ʵ������
const double c2 = 1.5;
const int  max_iteration = 300;  // ��������
const int size_pop = 30; // ��Ⱥ��ģ
const int pop_max = 5; // �������ȡֵ
const int pop_min = -5; // ������Сȡֵ
const double v_max = 0.5; // �ٶ����ֵ
const double v_min = -0.5; //�ٶ���Сֵ


void PSO()
{
	POP pop[size_pop];
	P_BEST pBest[size_pop];
	G_BEST gBest;
	ITER_INFO iterInfo[max_iteration];
	int iterTemp = 0;
	G_BEST  iterBest;

	//��ʼ��
	for (int i = 0; i < size_pop; ++i)
	{
		
		pop[i].x = (double)rand() / RAND_MAX * 10.0 - 5.0;
		pop[i].y = (double)rand() / RAND_MAX * 10.0 - 5.0;
		pop[i].x_v = (double)rand() / RAND_MAX * v_max * 2 - v_max;
		pop[i].y_v = (double)rand() / RAND_MAX * v_max * 2 - v_max;
		pop[i].value = fun(pop[i].x, pop[i].y);

		pBest[i].x = pop[i].x;
		pBest[i].y = pop[i].y;
		pBest[i].value = pop[i].value;
	}
	//Ⱥ������λ����ֵ
	gBest.x = pop[0].x;
	gBest.y = pop[0].y;
	gBest.value = pop[0].value;
	iterInfo[iterTemp].x = pop[0].x;
	iterInfo[iterTemp].y = pop[0].y;
	iterInfo[iterTemp].value = pop[0].value;

	iterBest.x = pop[0].x;
	iterBest.y = pop[0].y;
	iterBest.value = pop[0].value;

	//�ҳ�ʼ����ֵ
	for (int i = 1; i < size_pop; ++i)
	{
		if (pop[i].value < gBest.value)
		{
			gBest.x = pop[i].x;
			gBest.y = pop[i].y;
			gBest.value = pop[i].value;
			iterInfo[iterTemp].x = pop[i].x;
			iterInfo[iterTemp].y = pop[i].y;
			iterInfo[iterTemp].value = pop[i].value;
		}
	}


	while (iterTemp < max_iteration)
	{
		iterTemp++;

		for (int i = 0; i < size_pop; ++i)
		{
			pop[i].x_v += c1 * ((double)rand() / RAND_MAX * 10.0 - 5.0 )* (pBest[i].x - pop[i].x)
				+ c2 * ((double)rand() / RAND_MAX * 10.0 - 5.0) * (gBest.x - pop[i].x);
			pop[i].y_v += c1 * ((double)rand() / RAND_MAX * 10.0 - 5.0) * (pBest[i].y - pop[i].y)
				+ c2 * ((double)rand() / RAND_MAX * 10.0 - 5.0) * (gBest.y - pop[i].y);

			//Խ�紦��
			if (pop[i].x_v > v_max)
				pop[i].x_v = v_max;

			if (pop[i].x_v < v_min)
				pop[i].x_v = v_min;

			if (pop[i].y_v > v_max)
				pop[i].y_v = v_max;

			if (pop[i].y_v < v_min)
				pop[i].y_v = v_min;

			pop[i].x += pop[i].x_v;
			//λ��Խ���������
			if (pop[i].x > pop_max || pop[i].x < pop_min)
			{
				pop[i].x = (double)rand() / RAND_MAX * 10.0 - 5.0;
			}
			pop[i].y += pop[i].y_v;
			//λ��Խ���������
			if (pop[i].y > pop_max || pop[i].y < pop_min)
			{
				pop[i].y = (double)rand() / RAND_MAX * 10.0 - 5.0;
			}



			//����ÿ������ֵ
			pop[i].value = fun(pop[i].x, pop[i].y);
			if (pop[i].value < pBest[i].value)
			{
				pBest[i].x = pop[i].x;
				pBest[i].y = pop[i].y;
				pBest[i].value = pop[i].value;

				//����Ⱥ������ֵ
				if (pop[i].value < gBest.value)
				{
					gBest.x = pop[i].x;
					gBest.y = pop[i].y;
					gBest.value = pop[i].value;
					iterInfo[iterTemp].x = pop[i].x;
					iterInfo[iterTemp].y = pop[i].y;
					iterInfo[iterTemp].value = pop[i].value;
				}

			}
		}

		//printf("pso_info [iter:%d pos(%f,%f) min value:%f]\n", iterTemp, gBest.x, gBest.y, gBest.value);

		if (gBest.value < iterBest.value)
		{
			iterBest.x = gBest.x;
			iterBest.y = gBest.y;
			iterBest.value = gBest.value;
		}
	}

	printf("PSO����Ⱥ:\npos(%f,%f)\nmin value:%f;\n", iterBest.x, iterBest.y, iterBest.value);



}