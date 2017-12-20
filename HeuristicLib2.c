//
// Created by Dell on 17/12/19.
//


#include <mem.h>
#include <stdlib.h>

#define MAX 100 //最大值
#define number_of_task MAX-1 //任务的数量
#define number_of_resource MAX/10 //资源的数量
#define INF 2147483647

int resources[MAX][MAX]; //机器的运行状态，初始化为0
int resource_finish_time[MAX]; //机器结束的时间，初始化为0
int performance[MAX]; //机器的性能，随机数10-30
int task[MAX]; //任务队列，随机数500-1000

void initialize();

int opportunities_load_balancing();

int min_execution_time();
int min_completion_time();
int min_min();
int min_max();

int main(){
    initialize();

    min_max();
}

void initialize(){
    memset(resources, 0, MAX*MAX* sizeof(int));
    memset(resource_finish_time, 0, MAX* sizeof(int));

    for (int i = 1; i <= number_of_resource ; ++i) {
        performance[i] = 10 + rand()*1.0/RAND_MAX*20;
    }
    for (int i = 1; i <= number_of_task ; ++i) {
        task[i] = 500 + rand()*1.0/RAND_MAX*500;
    }
    return;
}

int opportunities_load_balancing(){
    for (int i = 1; i <= number_of_task; ++i) {
        //找出最早运行结束的资源
        int index = 1;
        for (int j = 2; j <= number_of_resource; ++j) {
            if(resource_finish_time[j] < resource_finish_time[index]){
                index = j;
            }
        }

        //资源队列加上本任务
        resources[index][0]++;
        resources[index][resources[index][0]] = i;

        //结束时间加上本任务运行的时间
        resource_finish_time[index] += (task[i]/performance[index]);
    }

    int index = 1;
    for (int j = 2; j <= number_of_resource; ++j) {
        if(resource_finish_time[j] > resource_finish_time[index]){
            index = j;
        }
    }
    return resource_finish_time[index];
}

int min_execution_time(){

}

int min_completion_time(){
    for (int i = 1; i <= number_of_task; ++i) {
        int index = 1;
        int value = resource_finish_time[index] + task[i]/performance[index];
        for (int j = 2; j <= number_of_resource; ++j) {
            int temp = resource_finish_time[j] + task[j]/performance[j];
            if (temp < value){
                index = j;
                value = temp;
            }
        }

        //资源队列加上本任务
        resources[index][0]++;
        resources[index][resources[index][0]] = i;

        //结束时间加上本任务运行的时间
        resource_finish_time[index] += (task[i]/performance[index]);
    }

    int index = 1;
    for (int j = 2; j <= number_of_resource; ++j) {
        if(resource_finish_time[j] > resource_finish_time[index]){
            index = j;
        }
    }
    return resource_finish_time[index];
}

int min_min(){

    //找出min_min
    int temp[MAX][MAX];
    memset(temp, 0, MAX*MAX* sizeof(int));
    int done[MAX];
    memset(done, 0, MAX* sizeof(int));

    for (int k = 1; k <= number_of_task; ++k) {
        int t = 1, r = 1;
        int value = INF;
        for (int i = 1; i <= number_of_task; ++i) {
            if(done[i] == 0){
                for (int j = 1; j <= number_of_resource; ++j) {
                    temp[i][j] = resource_finish_time[j] + task[i]/performance[j];
                    if(temp[i][j] < value){
                        value = temp[i][j];
                        t = i;
                        r = j;
                    }
                }
            }
        }

        //将任务t加入到资源r的队列中。
        //资源队列加上本任务
        resources[r][0]++;
        resources[r][resources[r][0]] = t;

        //结束时间加上本任务运行的时间
        resource_finish_time[r] += (task[t]/performance[r]);
        done[t] = 1;
    }

    int index = 1;
    for (int j = 2; j <= number_of_resource; ++j) {
        if(resource_finish_time[j] > resource_finish_time[index]){
            index = j;
        }
    }
    return resource_finish_time[index];
}

int min_max(){

    //找出min_max
    int temp[MAX][MAX];
    memset(temp, 0, MAX*MAX* sizeof(int));
    int done[MAX];
    memset(done, 0, MAX* sizeof(int));

    for (int k = 1; k <= number_of_task; ++k) {
        int t, r;
        int value = -1;
        for (int i = 1; i <= number_of_task; ++i) {
            if(done[i] == 0){
                for (int j = 1; j <= number_of_resource; ++j) {
                    temp[i][j] = resource_finish_time[j] + task[i]/performance[j];
                    if(temp[i][j] > value){
                        value = temp[i][j];
                        t = i;
                        r = j;
                    }
                }
            }
        }

        //将任务t加入到资源r的队列中。
        //资源队列加上本任务
        resources[r][0]++;
        resources[r][resources[r][0]] = t;

        //结束时间加上本任务运行的时间
        resource_finish_time[r] += (task[t]/performance[r]);
        done[t] = 1;
    }

    int index = 1;
    for (int j = 2; j <= number_of_resource; ++j) {
        if(resource_finish_time[j] > resource_finish_time[index]){
            index = j;
        }
    }
    return resource_finish_time[index];
}