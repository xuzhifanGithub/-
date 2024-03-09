#include"tabu.h"


const int max_iteration = 1000; // ����������
const int tabu_size = 10; // ���ɳ���
const int neighborhood_size = 50; // �����С

// �Զ���ıȽϺ��������ڱȽ�����Person�ṹ���Ƿ����
bool isEqual(const POS& p1, const POS& p2) 
{
    return p1.x == p2.x && p1.y == p2.y;
}


void TABU()
{
    vector<POS> tabuList;  //���ɱ�
    POS node_now;  //������ɳ�ʼ��
    node_now.x = (double)rand() / RAND_MAX * 10.0 - 5.0;
    node_now.y = (double)rand() / RAND_MAX * 10.0 - 5.0;
    double node_now_value = fun(node_now.x, node_now.y);
    double bestSofar = node_now_value;
    double candidate;


    POS node_temp_best;
    
    for (int i = 0; i < max_iteration; i++)
    {
        node_temp_best = getBestNeighborValue(candidate);
        while (find_if(tabuList.begin(), tabuList.end(), [&](const POS& p) { return isEqual(p, node_temp_best); }) != tabuList.end())
        {//���ɱ����ҵ��������������������
            node_temp_best = getBestNeighborValue(candidate);
        }

        if (candidate > node_now_value)
        {
            node_now = node_temp_best;
            node_now_value = candidate;
            tabuList.push_back(node_temp_best);    //����ǰ�ڵ��������б�
            if (tabuList.size() > tabu_size)
            {
                tabuList.erase(tabuList.begin()); // �����б���ֻ�������µĸ��ڵ�
            }
        }
        else if (candidate < node_now_value)
        {
            if (candidate < bestSofar)
            {
                node_now = node_temp_best;
                node_now_value = candidate;
                bestSofar = candidate;
                tabuList.push_back(node_temp_best);    //����ǰ�ڵ��������б�
                if (tabuList.size() > tabu_size)
                {
                    tabuList.erase(tabuList.begin()); // �����б���ֻ�������µĸ��ڵ�
                }
            }
            else
            {
                //if (find_if(tabuList.begin(), tabuList.end(), [&](const POS& p) { return isEqual(p, node_temp_best); }) != tabuList.end())
                node_now = node_temp_best;
                node_now_value = candidate;
                tabuList.push_back(node_temp_best);    //����ǰ�ڵ��������б�
                if (tabuList.size() > tabu_size)
                {
                    tabuList.erase(tabuList.begin()); // �����б���ֻ�������µĸ��ڵ�
                }
            }
        }
    }

    printf("TABU��������:\npos(%f,%f)\nmin value:%f;\n", node_now.x, node_now.y, bestSofar);

}


POS getBestNeighborValue(double& candidate)
{
    POS node_temp_best;
    double minn = 8888888;
    for (int i = 0; i < neighborhood_size; i++)
    {
        POS node_temp;
        double value_temp;
        node_temp.x = (double)rand() / RAND_MAX * 10.0 - 5.0;
        node_temp.y = (double)rand() / RAND_MAX * 10.0 - 5.0;
        value_temp = fun(node_temp.x, node_temp.y);

        if (value_temp < minn)
        {
            node_temp_best = node_temp;
            minn = value_temp;
            candidate = minn;
        }

    }

    return node_temp_best;
}