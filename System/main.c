#include"head.h"
int main(void)
{
    head=InitInfo();
    gh_std_out = GetStdHandle(STD_OUTPUT_HANDLE); /* ��ȡ��׼����豸���*/
    gh_std_in = GetStdHandle(STD_INPUT_HANDLE);   /* ��ȡ��׼�����豸���*/
    SetConsoleTitle("̰��������Ϣ����ϵͳ");                 /*���ô��ڱ���*/
    COORD size={SCR_COL,SCR_ROW};
    SetConsoleScreenBufferSize(gh_std_out, size); /*���ô��ڻ�������С120*28*/
    InitInterface();
    RunSys(&head);
    return 0;
}


