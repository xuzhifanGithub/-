#include"ga.h"//遗传算法



const int INT_BIT = 3;
const int DNA_BIT = 16;
const int DNA_NUM = 2;//DNA条数
const int animal_num = 200;
const double cross_rate = 0.8;// 生殖交叉概率
const double variation_rate = 0.005; // 变异的概率
const int generator_n = 200; // 种群演变的次数
int limit_area[2] = { -5, 5 }; // 值域
int iter_count;

struct ANIMALS
{
	int DNA[DNA_BIT * DNA_NUM];
	double DNA_translated[DNA_NUM];
}animal[animal_num], selected_animal[animal_num];

struct DNA_RESULT
{//二进制转化为十进制的结果存储 
	double translated_result[DNA_NUM];
}DNA_result[animal_num];

struct FITNESS 
{//每个animal的适应度计算 
	double p;
	int id;
	//int flag;
}fitness[animal_num];

int cmp(FITNESS f1, FITNESS f2)
{
	return f1.p < f2.p;
}

void GA()
{
	//初始化种群
	for (int i = 0; i < animal_num; i++) 
	{ 
		for (int j = 0; j < DNA_BIT * DNA_NUM; j++) 
		{
			animal[i].DNA[j] = rand() % 2;
		}
	}
	//如果有不符合定义域的就再生成一遍 
	for (int i = 0; i < animal_num; i++) 
	{
		for (int j = 0; j < DNA_BIT * DNA_NUM; j++) 
		{
			animal[i].DNA[j] = rand() % 2;
		}
		if (flag_limit_area(limit_area, i) != 1)i -= 1;
	}

	iter_count = 0;

	//for (int i = 0; i < animal_num; i++)
	{
		//printf("%f,", DNA10(animal[i].DNA));
	}


    //遗传进化
	for (int i = 0; i < generator_n; i++) 
	{ 
		/*测试
		if (i >= generator_n - 1)
		{
			iter_count = 1;
		}*/

		get_fitness();//适应度计算 
		std::sort(fitness, fitness + animal_num, cmp);//排序，方便挑选 

		//printf("ga_info [iter:%d pos(%f,%f) min value:%f]\n", i,DNA_result[0].translated_result[0], DNA_result[0].translated_result[1],
		//   fun(DNA_result[0].translated_result[0], DNA_result[0].translated_result[1]));
		/*测试
		for (int j = 0; j < animal_num; j++)
		{
			if (i >= generator_n - 1)
			{
				printf("(%d,%d,%f)\n", j, fitness[j].id, fitness[j].p);
			}
		}*/

		select();//挑选种群 
		copy();//将挑选好的复制回原来的种群 
		crossover_and_variation();//交配、变异 
		copy();//将生成的子种群复制回原来的种群 

		//for (int i = 0; i < animal_num; i++)
		{
			//printf("%f,", DNA10(animal[i].DNA,0));
		}

	}

	//得出最终的最优结果 
	get_fitness();
	std::sort(fitness, fitness + animal_num, cmp);

	//测试
	//for (int i = 0; i < animal_num; i++)
	{
		//printf("(%d,%d)(%d,%d,%f)\n", DNA10(animal[i].DNA), DNA10(animal[i].DNA,1), i, fitness[i].id, fitness[i].p);
	}
	int id = fitness[0].id;
	double x = DNA_result[id].translated_result[0];
	double y = DNA_result[id].translated_result[1];
	printf("GA遗传算法:\npos(%f,%f)\nmin value:%f;\n",x,y, fun(x, y));
}

void DNA2to10(int n)
{
	for (int i = 0; i < DNA_NUM; i++)
	{
		double sum = 0;
		int base = i * DNA_BIT;
		double sign = animal[n].DNA[base];
		double flag;
		if (sign == 0)flag = -1;
		else flag = 1;
		for (int j = base + 1; j <= base + INT_BIT; j++) {
			if (animal[n].DNA[j] == 1)sum += pow(2, INT_BIT + base - j);
		}
		for (int j = base + INT_BIT + 1; j < DNA_BIT + base; j++) {
			if (animal[n].DNA[j] == 1)sum += pow(2, INT_BIT + base - j);
		}
		DNA_result[n].translated_result[i] = sum * flag;
		animal[n].DNA_translated[i] = sum * flag;
	}
}

double DNA10(int DNA[],int choice )
{
	
	for (int i = choice; i < DNA_NUM; i++)
	{
		double sum = 0;
		int base = i * DNA_BIT;
		double sign = DNA[base];
		double flag;
		if (sign == 0)flag = -1;
		else flag = 1;
		for (int j = base + 1; j <= base + INT_BIT; j++) {
			if (DNA[j] == 1)sum += pow(2, INT_BIT + base - j);
		}
		for (int j = base + INT_BIT + 1; j < DNA_BIT + base; j++) {
			if (DNA[j] == 1)sum += pow(2, INT_BIT + base - j);
		}
		sum *= flag;
		return sum;
	}
}

int DNA2to10_vaild(int DNA[DNA_BIT * DNA_NUM])
{
	for (int i = 0; i < DNA_NUM; i++)
	{
		double sum = 0;
		int base = i * DNA_BIT;
		double sign = DNA[base];
		double flag;
		if (sign == 0)flag = -1;
		else flag = 1;
		for (int j = base + 1; j <= base + INT_BIT; j++) {
			if (DNA[j] == 1)sum += pow(2, INT_BIT + base - j);
		}
		for (int j = base + INT_BIT + 1; j < DNA_BIT + base; j++) {
			if (DNA[j] == 1)sum += pow(2, INT_BIT + base - j);
		}
		sum *= flag;
		if (sum >= -5 && sum <= 5 )
		{
			;
		}
		else
		{
			return 0;
		}
	}
	return 1;
}



//检测是否超过定义域 
int flag_limit_area(int limit_area[], int i) 
{
	DNA2to10(i);
	if (DNA_result[i].translated_result[0] >= limit_area[0]
		&& DNA_result[i].translated_result[0] <= limit_area[1]
		&& DNA_result[i].translated_result[1] >= limit_area[0]
		&& DNA_result[i].translated_result[1] <= limit_area[1])
		return 1;
	else return 0;
}


//计算每个animal的适应度 
void get_fitness()
{
	double fitness_score[animal_num];
	double fit_flag[animal_num];
	for (int i = 0; i < animal_num; i++) 
	{
		DNA2to10(i);
		fitness_score[i] = fun(DNA_result[i].translated_result[0], DNA_result[i].translated_result[1]);
		fit_flag[i] = flag_limit_area(limit_area, i);
	}
	double minn = 8888888;
	for (int i = 0; i < animal_num; i++)
	{
		minn = std::min(minn, fitness_score[i]);
	}

	for (int i = 0; i < animal_num; i++)
	{
		fitness_score[i] = fitness_score[i] - minn + 1e-5;
	}

	double sum = 0;
	for (int i = 0; i < animal_num; i++)
	{
		/*if (iter_count == 1)
		{
			printf("[[(%f,%f)%d,%f,%f\n",DNA_result[i].translated_result[0], DNA_result[i].translated_result[1], i, fitness_score[i], fitness_score[i]+minn);
		}*/
		fitness_score[i] = fitness_score[i] * fit_flag[i];
		sum += fitness_score[i];

	};

	
	for (int i = 0; i < animal_num; i++) 
	{
		fitness[i].p = fitness_score[i] / sum + 1e-5;
		fitness[i].id = i;
	}
}

//根据适应度选择animal 
void select() 
{
	int n = 0;
	/*for (int i = animal_num; i >= 0; i--)
	{
		int num = ceil(fitness[i].p * animal_num);
		for (int j = 0; j < num; j++) 
		{
			for (int k = 0; k < DNA_BIT * DNA_NUM; k++) 
			{
				selected_animal[n].DNA[k] = animal[fitness[i].id].DNA[k];
			}
			n++;
			if (n == animal_num)break;
		}
		if (n == animal_num)break;
	}*/
	for (int i = 0; i < animal_num; i++)
	{
		int num = ceil((1-fitness[i].p) * animal_num);
		//if (num >= animal_num / 2)num = animal_num / 2;//防止过大
		for (int j = 0; j < num; j++)
		{
			for (int k = 0; k < DNA_BIT * DNA_NUM; k++)
			{
				selected_animal[n].DNA[k] = animal[fitness[i].id].DNA[k];
			}
			n++;
			if (n == animal_num)break;
		}
		if (n == animal_num)break;
	}
}

//生殖交叉、变异 
void crossover_and_variation() 
{
	for (int k = 0; k < animal_num; k++)
	{
		int father[DNA_BIT * DNA_NUM];
		int mother[DNA_BIT * DNA_NUM];
		int child[DNA_BIT * DNA_NUM];
		int father_id = rand() % 200;
		int mother_id = rand() % 200;
		for (int i = 0; i < DNA_BIT * DNA_NUM; i++)
		{
			father[i] = animal[father_id].DNA[i];
			mother[i] = animal[mother_id].DNA[i];
		}

		//是否生殖交叉
		if ((rand() % 100) / 100.0 < cross_rate)
		{
			int cross_pos = rand() % (DNA_BIT * DNA_NUM);
			for (int i = 0; i < cross_pos; i++)child[i] = father[i];
			for (int i = cross_pos; i < DNA_BIT * DNA_NUM; i++)child[i] = mother[i];

			while (!DNA2to10_vaild(child))
			{
				cross_pos = rand() % (DNA_BIT * DNA_NUM);
				for (int i = 0; i < cross_pos; i++)child[i] = father[i];
				for (int i = cross_pos; i < DNA_BIT * DNA_NUM; i++)child[i] = mother[i];
			} 
		}

		//是否变异
		if ((rand() % 100) / 100.0 < variation_rate) 
		{
			int variation_pos = rand() % (DNA_BIT * DNA_NUM);
			child[variation_pos] = 1 - child[variation_pos];

			while (!DNA2to10_vaild(child))
			{
				variation_pos = rand() % (DNA_BIT * DNA_NUM);
				child[variation_pos] = 1 - child[variation_pos];
			}
		}


		for (int j = 0; j < DNA_BIT * DNA_NUM; j++)
		{
			selected_animal[k].DNA[j] = child[j];
		}
	}
}

//将新的结果copy回animal以便进行下一轮迭代 
void copy() 
{
	for (int i = 0; i < animal_num; i++) 
	{
		for (int j = 0; j < DNA_BIT * DNA_NUM; j++) 
		{
			animal[i].DNA[j] = selected_animal[i].DNA[j];
		}
	}
}

