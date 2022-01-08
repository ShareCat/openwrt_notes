#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#define TEMP_PATH "/sys/class/thermal/thermal_zone0/temp"
#define MAX_SIZE 32

int main(void)
{
    int fd;
    double temp = 0;
    char buffer[MAX_SIZE];
    int i;

    while(i < 100)
    {
        i+=1;

        //延时1s
        sleep(1);

        //打开文件
        fd = open(TEMP_PATH,O_RDONLY);
        if(fd < 0)
        {
            fprintf(stderr,"Failed to open thermal_zone0/temp\n");
            return - 1;
        }

        //读取文件
        if(read(fd,buffer,MAX_SIZE) < 0)
        {
            fprintf(stderr,"Failed to read temp\n");
            return -1;
        }

        //计算温度值
        temp = atoi(buffer) / 1000.0;

        //打印输出温度
        printf("Temp:%.4f\n",temp);

        //关闭文件
        close(fd);
    }
}