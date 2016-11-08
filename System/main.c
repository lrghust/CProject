#include"head.h"
int main(void)
{
    head=InitInfo();
    gh_std_out = GetStdHandle(STD_OUTPUT_HANDLE); /* 获取标准输出设备句柄*/
    gh_std_in = GetStdHandle(STD_INPUT_HANDLE);   /* 获取标准输入设备句柄*/
    SetConsoleTitle("贪腐案件信息管理系统");                 /*设置窗口标题*/
    COORD size={SCR_COL,SCR_ROW};
    SetConsoleScreenBufferSize(gh_std_out, size); /*设置窗口缓冲区大小120*28*/
    InitInterface();
    RunSys(&head);
    return 0;
}


