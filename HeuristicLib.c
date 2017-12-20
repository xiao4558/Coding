//
// Created by Dell on 17/12/12.
//

#include <stdlib.h>
#include <stdio.h>
#include <mem.h>
#include <math.h>

#define NUM 1 //流程图的数量
#define MAX 10 //数组的大小，值为顶点数+1
#define INF 2147483647 //定义无穷大

struct flow{
    int vertex; //当前流程图中任务的数量
    int map[MAX][MAX]; //当前流程图中的map，值表示两个任务之间需要传递的数据，大小随机，范围100-300
    int sequence[MAX]; //任务执行的顺序
    double lft[MAX]; //每个任务的lft
    double est[MAX]; //每个任务的est
    int duration[MAX]; //每个任务的d，大小随机，范围200-500
    int length; //整个流程图最长的长度
};

struct flow maps[NUM];

void initialize(); //初始化
int find_hinder_longest_length(int f, int t); //找到流程图f中某节点t后续的最长的路径
int find_ahead_longest_length(int f, int t); //找到流程图f中某节点t到开头的最短路径

void min_slack_time(struct flow *);
void min_last_finish_time(struct flow *);
void min_spt(struct flow *);
void min_random(struct flow *);
void min_weighted_resource_utilization_precedence(struct flow *);
void min_late_start_time(struct flow *);
void min_early_start_time(struct flow *);
void min_early_finish_time(struct flow *);
void min_all_sons(struct flow *);

int main(){

    initialize();

    min_all_sons(&maps[0]);



    return 0;
}

void initialize(){
    for (int i = 0; i < NUM; ++i) {
        FILE * file = fopen("9.txt", "r");

        //从文件中读取vertex和edge的值
        int vertex, edge;
        fscanf(file,"%d %d", &vertex, &edge);
        maps[i].vertex = vertex;

        //从文件中读取map
        memset(maps[i].map, -1, MAX*MAX*sizeof(int)); //将map初始化为-1，-1表示两个任务间没有联系

        int temp, from, to;
        for (int j = 0; j < edge; ++j) {
            fscanf(file, "%d %d %d",&temp, &from, &to);
            maps[i].map[from][to] = 100 + 200*rand()*1.0/RAND_MAX;
        }

        //初始化duration等变量
        for (int j = 1; j <= vertex; j++){
            maps[i].duration[j] = 200 + 300 * rand() * 1.0 / RAND_MAX;
        }

        //计算est，lft, length;
        maps[i].length =  find_hinder_longest_length(i, 1);

        for (int j = 1; j <= maps[i].vertex; j++){
            maps[i].lft[j] = maps[i].length - find_hinder_longest_length(i, j) + maps[i].duration[j];
            maps[i].est[j] = find_ahead_longest_length(i, j) - maps[i].duration[j];
        }
    }
}

int find_hinder_longest_length(int f, int t){

    int total = 0;
    int islast = 1;

    //遍历流程图f中的t节点所指向的任务
    for(int i = 1; i <= maps[f].vertex; i++){
        if( maps[f].map[t][i] != -1){
            islast = 0;
            int temp = find_hinder_longest_length(f, i);
            if(temp > total){
                total = temp;
            }
        }
    }

    //判断是否是最后一个节点，如果是，则返回当前节点的duration，如果不是，则返回duration + total
    if(islast == 1){
        return maps[f].duration[t];
    }else{
        return maps[f].duration[t] + total;
    }
}

int find_ahead_longest_length(int f, int t){

    int total = 0;
    int islast = 1;

    //遍历流程图f中的t节点所指向的任务
    for(int i = 1; i <= maps[f].vertex; i++){
        if( maps[f].map[i][t] != -1){
            islast = 0;
            int temp = find_ahead_longest_length(f, i);
            if(temp > total){
                total = temp;
            }
        }
    }

    //判断是否是最后一个节点，如果是，则返回当前节点的duration，如果不是，则返回duration + total
    if(islast == 1){
        return maps[f].duration[t];
    }else{
        return maps[f].duration[t] + total;
    }
}

void min_slack_time(struct flow * f){
    int temp[MAX]; //保存需要比较的任务
    int done = 0; //保存任务是否已经完成
    memset(temp,INF,MAX*sizeof(int));
    temp[0] = 0;

    int current = 1;
    f->sequence[0] = 1;
    f->sequence[1] = 1;
    done += pow(2, current);

    while (f->sequence[0] != f->vertex){
        //检查当前节点current指向的合格的节点保存早temp数组中
        for (int i = 1; i <= f->vertex; ++i) {
            if (f->map[current][i] != -1){ //如果current指向有节点i
                //获取其指向的节点的任务完成度t
                int t = 0;
                //遍历节点i的父节点j
                for (int j = 1; j <= f->vertex; ++j) {
                    if (f->map[j][i] != -1){
                        t += pow(2, j);
                    }
                }
                if ((t & done) == t){ //如果父任务全部完成，加入到temp数组中
                    temp[0]++;
                    temp[temp[0]] = i;
                }
            }
        }

        //根据不同的规则，在temp数组中找到最合适的节点
        int index = 1;
        int value = f->lft[temp[index]] - f->est[temp[index]] - f->duration[temp[index]];
        for (int i = 2; i <= temp[0] ; ++i) {
            int node = temp[i];
            int node_value = f->lft[node] - f->est[node] - f->duration[node];
            if(node_value < value){
                index = i;
                value = node_value;
            }
        }

        //保存最合适的节点，删除其在temp中的位置
        current = temp[index];

        f->sequence[++f->sequence[0]] = temp[index];
        done += pow(2, temp[index]);

        temp[index] = temp[temp[0]];
        temp[0]--;
    }
}

void min_last_finish_time(struct flow * f){
    int temp[MAX]; //保存需要比较的任务
    int done = 0; //保存任务是否已经完成
    memset(temp,INF,MAX*sizeof(int));
    temp[0] = 0;

    int current = 1;
    f->sequence[0] = 1;
    f->sequence[1] = 1;
    done += pow(2, current);

    while (f->sequence[0] != f->vertex){
        //检查当前节点current指向的合格的节点保存早temp数组中
        for (int i = 1; i <= f->vertex; ++i) {
            if (f->map[current][i] != -1){ //如果current指向有节点i
                //获取其指向的节点的任务完成度t
                int t = 0;
                //遍历节点i的父节点j
                for (int j = 1; j <= f->vertex; ++j) {
                    if (f->map[j][i] != -1){
                        t += pow(2, j);
                    }
                }
                if ((t & done) == t){ //如果父任务全部完成，加入到temp数组中
                    temp[0]++;
                    temp[temp[0]] = i;
                }
            }
        }

        //根据不同的规则，在temp数组中找到最合适的节点
        int index = 1;
        int value = f->lft[temp[index]];
        for (int i = 2; i <= temp[0] ; ++i) {
            int node = temp[i];
            int node_value = f->lft[node];
            if(node_value < value){
                index = i;
                value = node_value;
            }
        }

        //保存最合适的节点，删除其在temp中的位置
        current = temp[index];

        f->sequence[++f->sequence[0]] = temp[index];
        done += pow(2, temp[index]);

        temp[index] = temp[temp[0]];
        temp[0]--;
    }
    return;
}

void min_spt(struct flow * f){
    int temp[MAX]; //保存需要比较的任务
    int done = 0; //保存任务是否已经完成
    memset(temp,INF,MAX*sizeof(int));
    temp[0] = 0;

    int current = 1;
    f->sequence[0] = 1;
    f->sequence[1] = 1;
    done += pow(2, current);

    while (f->sequence[0] != f->vertex){
        //检查当前节点current指向的合格的节点保存早temp数组中
        for (int i = 1; i <= f->vertex; ++i) {
            if (f->map[current][i] != -1){ //如果current指向有节点i
                //获取其指向的节点的任务完成度t
                int t = 0;
                //遍历节点i的父节点j
                for (int j = 1; j <= f->vertex; ++j) {
                    if (f->map[j][i] != -1){
                        t += pow(2, j);
                    }
                }
                if ((t & done) == t){ //如果父任务全部完成，加入到temp数组中
                    temp[0]++;
                    temp[temp[0]] = i;
                }
            }
        }

        //根据不同的规则，在temp数组中找到最合适的节点
        int index = 1;
        int value = f->duration[temp[index]];
        for (int i = 2; i <= temp[0] ; ++i) {
            int node = temp[i];
            int node_value = f->duration[node];
            if(node_value < value){
                index = i;
                value = node_value;
            }
        }

        //保存最合适的节点，删除其在temp中的位置
        current = temp[index];

        f->sequence[++f->sequence[0]] = temp[index];
        done += pow(2, temp[index]);

        temp[index] = temp[temp[0]];
        temp[0]--;
    }
    return;
}

void min_random(struct flow * f){
    int temp[MAX]; //保存需要比较的任务
    int done = 0; //保存任务是否已经完成
    memset(temp,INF,MAX*sizeof(int));
    temp[0] = 0;

    int current = 1;
    f->sequence[0] = 1;
    f->sequence[1] = 1;
    done += pow(2, current);

    while (f->sequence[0] != f->vertex){
        //检查当前节点current指向的合格的节点保存早temp数组中
        for (int i = 1; i <= f->vertex; ++i) {
            if (f->map[current][i] != -1){ //如果current指向有节点i
                //获取其指向的节点的任务完成度t
                int t = 0;
                //遍历节点i的父节点j
                for (int j = 1; j <= f->vertex; ++j) {
                    if (f->map[j][i] != -1){
                        t += pow(2, j);
                    }
                }
                if ((t & done) == t){ //如果父任务全部完成，加入到temp数组中
                    temp[0]++;
                    temp[temp[0]] = i;
                }
            }
        }

        //根据不同的规则，在temp数组中找到最合适的节点
        int index = 1;
        int value = rand();
        for (int i = 2; i <= temp[0] ; ++i) {
            int node = temp[i];
            int node_value = rand();
            if(node_value < value){
                index = i;
                value = node_value;
            }
        }

        //保存最合适的节点，删除其在temp中的位置
        current = temp[index];

        f->sequence[++f->sequence[0]] = temp[index];
        done += pow(2, temp[index]);

        temp[index] = temp[temp[0]];
        temp[0]--;
    }
    return;
}

//todo 这个情况有点复杂
void min_weighted_resource_utilization_precedence(struct flow * f){
    int temp[MAX]; //保存需要比较的任务
    int done = 0; //保存任务是否已经完成
    memset(temp,INF,MAX*sizeof(int));
    temp[0] = 0;

    int current = 1;
    f->sequence[0] = 1;
    f->sequence[1] = 1;
    done += pow(2, current);

    while (f->sequence[0] != f->vertex){
        //检查当前节点current指向的合格的节点保存早temp数组中
        for (int i = 1; i <= f->vertex; ++i) {
            if (f->map[current][i] != -1){ //如果current指向有节点i
                //获取其指向的节点的任务完成度t
                int t = 0;
                //遍历节点i的父节点j
                for (int j = 1; j <= f->vertex; ++j) {
                    if (f->map[j][i] != -1){
                        t += pow(2, j);
                    }
                }
                if ((t & done) == t){ //如果父任务全部完成，加入到temp数组中
                    temp[0]++;
                    temp[temp[0]] = i;
                }
            }
        }

        //根据不同的规则，在temp数组中找到最合适的节点
        int index = 1;
        int value = rand();
        for (int i = 2; i <= temp[0] ; ++i) {
            int node = temp[i];
            int node_value = rand();
            if(node_value < value){
                index = i;
                value = node_value;
            }
        }

        //保存最合适的节点，删除其在temp中的位置
        current = temp[index];

        f->sequence[++f->sequence[0]] = temp[index];
        done += pow(2, temp[index]);

        temp[index] = temp[temp[0]];
        temp[0]--;
    }
    return;
}

void min_late_start_time(struct flow * f){
    int temp[MAX]; //保存需要比较的任务
    int done = 0; //保存任务是否已经完成
    memset(temp,INF,MAX*sizeof(int));
    temp[0] = 0;

    int current = 1;
    f->sequence[0] = 1;
    f->sequence[1] = 1;
    done += pow(2, current);

    while (f->sequence[0] != f->vertex){
        //检查当前节点current指向的合格的节点保存早temp数组中
        for (int i = 1; i <= f->vertex; ++i) {
            if (f->map[current][i] != -1){ //如果current指向有节点i
                //获取其指向的节点的任务完成度t
                int t = 0;
                //遍历节点i的父节点j
                for (int j = 1; j <= f->vertex; ++j) {
                    if (f->map[j][i] != -1){
                        t += pow(2, j);
                    }
                }
                if ((t & done) == t){ //如果父任务全部完成，加入到temp数组中
                    temp[0]++;
                    temp[temp[0]] = i;
                }
            }
        }

        //根据不同的规则，在temp数组中找到最合适的节点
        int index = 1;
        int value = f->lft[temp[index]] - f->duration[temp[index]];
        for (int i = 2; i <= temp[0] ; ++i) {
            int node = temp[i];
            int node_value = f->lft[node] - f->duration[node];
            if(node_value < value){
                index = i;
                value = node_value;
            }
        }

        //保存最合适的节点，删除其在temp中的位置
        current = temp[index];

        f->sequence[++f->sequence[0]] = temp[index];
        done += pow(2, temp[index]);

        temp[index] = temp[temp[0]];
        temp[0]--;
    }
    return;
}

void min_early_start_time(struct flow * f){
    int temp[MAX]; //保存需要比较的任务
    int done = 0; //保存任务是否已经完成
    memset(temp,INF,MAX*sizeof(int));
    temp[0] = 0;

    int current = 1;
    f->sequence[0] = 1;
    f->sequence[1] = 1;
    done += pow(2, current);

    while (f->sequence[0] != f->vertex){
        //检查当前节点current指向的合格的节点保存早temp数组中
        for (int i = 1; i <= f->vertex; ++i) {
            if (f->map[current][i] != -1){ //如果current指向有节点i
                //获取其指向的节点的任务完成度t
                int t = 0;
                //遍历节点i的父节点j
                for (int j = 1; j <= f->vertex; ++j) {
                    if (f->map[j][i] != -1){
                        t += pow(2, j);
                    }
                }
                if ((t & done) == t){ //如果父任务全部完成，加入到temp数组中
                    temp[0]++;
                    temp[temp[0]] = i;
                }
            }
        }

        //根据不同的规则，在temp数组中找到最合适的节点
        int index = 1;
        int value = f->est[temp[index]];
        for (int i = 2; i <= temp[0] ; ++i) {
            int node = temp[i];
            int node_value = f->est[node];
            if(node_value < value){
                index = i;
                value = node_value;
            }
        }

        //保存最合适的节点，删除其在temp中的位置
        current = temp[index];

        f->sequence[++f->sequence[0]] = temp[index];
        done += pow(2, temp[index]);

        temp[index] = temp[temp[0]];
        temp[0]--;
    }
    return;
}

void min_early_finish_time(struct flow * f){
    int temp[MAX]; //保存需要比较的任务
    int done = 0; //保存任务是否已经完成
    memset(temp,INF,MAX*sizeof(int));
    temp[0] = 0;

    int current = 1;
    f->sequence[0] = 1;
    f->sequence[1] = 1;
    done += pow(2, current);

    while (f->sequence[0] != f->vertex){
        //检查当前节点current指向的合格的节点保存早temp数组中
        for (int i = 1; i <= f->vertex; ++i) {
            if (f->map[current][i] != -1){ //如果current指向有节点i
                //获取其指向的节点的任务完成度t
                int t = 0;
                //遍历节点i的父节点j
                for (int j = 1; j <= f->vertex; ++j) {
                    if (f->map[j][i] != -1){
                        t += pow(2, j);
                    }
                }
                if ((t & done) == t){ //如果父任务全部完成，加入到temp数组中
                    temp[0]++;
                    temp[temp[0]] = i;
                }
            }
        }

        //根据不同的规则，在temp数组中找到最合适的节点
        int index = 1;
        int value = f->est[temp[index]] + f->duration[temp[index]];
        for (int i = 2; i <= temp[0] ; ++i) {
            int node = temp[i];
            int node_value = f->est[node] + f->duration[node];
            if(node_value < value){
                index = i;
                value = node_value;
            }
        }

        //保存最合适的节点，删除其在temp中的位置
        current = temp[index];

        f->sequence[++f->sequence[0]] = temp[index];
        done += pow(2, temp[index]);

        temp[index] = temp[temp[0]];
        temp[0]--;
    }
    return;
}

void min_all_sons(struct flow * f){
    int nos[MAX]; //num_of_sons数组
    memset(nos, 0, MAX* sizeof(int));

    for(int i = f->vertex; i >= 1; i--){
        for (int j = 1; j <= f->vertex ; ++j) {
            if (f->map[j][i]!=-1){
                nos[j] = nos[j]|nos[i] + (int)pow(2,i);
            }
        }
    }

    for (int i = 1; i <= f->vertex; ++i) {
        int temp = 0;
        while(nos[i] != 0){
            if (nos[i] % 2 == 1){
                temp++;
            }
            nos[i] = nos[i] / 2;
        }
        nos[i] = temp;
    }

    //计算序列
    int temp[MAX]; //保存需要比较的任务
    int done = 0; //保存任务是否已经完成
    memset(temp,INF,MAX*sizeof(int));
    temp[0] = 0;

    int current = 1;
    f->sequence[0] = 1;
    f->sequence[1] = 1;
    done += pow(2, current);

    while (f->sequence[0] != f->vertex){
        //检查当前节点current指向的合格的节点保存早temp数组中
        for (int i = 1; i <= f->vertex; ++i) {
            if (f->map[current][i] != -1){ //如果current指向有节点i
                //获取其指向的节点的任务完成度t
                int t = 0;
                //遍历节点i的父节点j
                for (int j = 1; j <= f->vertex; ++j) {
                    if (f->map[j][i] != -1){
                        t += pow(2, j);
                    }
                }
                if ((t & done) == t){ //如果父任务全部完成，加入到temp数组中
                    temp[0]++;
                    temp[temp[0]] = i;
                }
            }
        }

        //根据不同的规则，在temp数组中找到最合适的节点
        int index = 1;
        int value = nos[temp[index]];
        for (int i = 2; i <= temp[0] ; ++i) {
            int node = temp[i];
            int node_value = nos[node];
            if(node_value < value){
                index = i;
                value = node_value;
            }
        }

        //保存最合适的节点，删除其在temp中的位置
        current = temp[index];

        f->sequence[++f->sequence[0]] = temp[index];
        done += pow(2, temp[index]);

        temp[index] = temp[temp[0]];
        temp[0]--;
    }
    return;
}