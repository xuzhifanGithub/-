#include"tabu.h"


const int max_iteration = 1000; // 最大迭代次数
const int tabu_size = 10; // 禁忌长度
const int neighborhood_size = 50; // 邻域大小

// 自定义的比较函数，用于比较两个Person结构体是否相等
bool isEqual(const POS& p1, const POS& p2) 
{
    return p1.x == p2.x && p1.y == p2.y;
}


void TABU()
{
    vector<POS> tabuList;  //禁忌表
    POS node_now;  //随机生成初始点
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
        {//禁忌表中找到则重新生成最优临域解
            node_temp_best = getBestNeighborValue(candidate);
        }

        if (candidate > node_now_value)
        {
            node_now = node_temp_best;
            node_now_value = candidate;
            tabuList.push_back(node_temp_best);    //将当前节点加入禁忌列表
            if (tabuList.size() > tabu_size)
            {
                tabuList.erase(tabuList.begin()); // 禁忌列表中只保留最新的个节点
            }
        }
        else if (candidate < node_now_value)
        {
            if (candidate < bestSofar)
            {
                node_now = node_temp_best;
                node_now_value = candidate;
                bestSofar = candidate;
                tabuList.push_back(node_temp_best);    //将当前节点加入禁忌列表
                if (tabuList.size() > tabu_size)
                {
                    tabuList.erase(tabuList.begin()); // 禁忌列表中只保留最新的个节点
                }
            }
            else
            {
                //if (find_if(tabuList.begin(), tabuList.end(), [&](const POS& p) { return isEqual(p, node_temp_best); }) != tabuList.end())
                node_now = node_temp_best;
                node_now_value = candidate;
                tabuList.push_back(node_temp_best);    //将当前节点加入禁忌列表
                if (tabuList.size() > tabu_size)
                {
                    tabuList.erase(tabuList.begin()); // 禁忌列表中只保留最新的个节点
                }
            }
        }
    }

    printf("TABU禁忌搜索:\npos(%f,%f)\nmin value:%f;\n", node_now.x, node_now.y, bestSofar);

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