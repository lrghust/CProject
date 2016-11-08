#include"head.h"
/**
 * 函数名称: DealString
 * 函数功能: 处理从屏幕上读的字符串，加\0.
 * 输入参数: str 要处理的字符串
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void DealString(char *str)//处理从屏幕上读的字符串，加\0
{
    int i=0;
    while(1)
    {
        if(str[i]==' ')
        {
            str[i]='\0';
            break;
        }
        i++;
    }
}
/**
 * 函数名称: TestProv
 * 函数功能: 测试省份信息是否存在.
 * 输入参数: str 要测试的省份名称
 * 输出参数: 无
 * 返 回 值: flag 1表示修改了省份名 0没有
 *
 * 调用说明:
 */
int TestProv(char *str)//测试省份信息是否存在
{
    Province *tail=head;
    int flag=0;
    while(tail->next!=NULL)
    {
        tail=tail->next;
        if(!strcmp(str,tail->ProvProv))
        {
            flag=1;
            break;
        }
    }
    return flag;
}

/**
 * 函数名称: TestProvForChange
 * 函数功能: 测试省份信息是否存在并传出省份信息.
 * 输入参数: str 要测试的省份名称
 * 输出参数: output 指向所保存的省份信息
 * 返 回 值: flag 1表示修改了省份名 0没有
 *
 * 调用说明:
 */
int TestProvForChange(char *str,char **output)//测试省份信息是否存在并传出省份信息
{
    Province *tail=head;
    int flag=0;
    while(tail->next!=NULL)
    {
        tail=tail->next;
        if(!strcmp(str,tail->ProvProv))
        {
            flag=1;
            sprintf(output[0],"%s",tail->ProvProv);
            sprintf(output[1],"%s",tail->ProvLeader);
            sprintf(output[2],"%s",tail->ProvTel);
            break;
        }
    }
    return flag;
}

/**
 * 函数名称: TestCase
 * 函数功能: 测试案件信息是否存在.
 * 输入参数: str 要测试的案件编号
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
int TestCase(char *str)//测试案件信息是否存在
{
    Province *tail=head;
    int flag=0;
    while(tail->next!=NULL)
    {
        tail=tail->next;
        Case *tail1=tail->ProvCase;
        while(tail1->next!=NULL)
        {
            tail1=tail1->next;
            if(!strcmp(str,tail1->CaseId))
            {
                flag=1;
                return flag;
            }
        }
    }
    return flag;
}

/**
 * 函数名称: TestCaseForChange
 * 函数功能: 测试案件信息是否存在.
 * 输入参数: str 要测试的案件编号
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
int TestCaseForChange(char *str,char **output)//测试案件信息是否存在
{
    Province *tail=head;
    int flag=0;
    while(tail->next!=NULL)
    {
        tail=tail->next;
        Case *tail1=tail->ProvCase;
        while(tail1->next!=NULL)
        {
            tail1=tail1->next;
            if(!strcmp(str,tail1->CaseId))
            {
                flag=1;
                sprintf(output[0],"%s",tail1->CaseProv);
                sprintf(output[1],"%s",tail1->CaseId);
                sprintf(output[2],"%s",tail1->CaseDate);
                sprintf(output[3],"%s",tail1->CaseName);
                *output[4]=tail1->CaseLevel;
                *output[5]=tail1->CaseCharge;
                sprintf(output[6],"%f",tail1->CaseMoney);
                sprintf(output[7],"%d",tail1->CaseJudge);
                return flag;
            }
        }
    }
    return flag;
}

/**
 * 函数名称: TestRepo
 * 函数功能: 测试媒体信息是否存在.
 * 输入参数: str 要测试的报道编号
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
int TestRepo(char *str)//测试媒体信息是否存在
{
    Province *tail=head;
    int flag=0;
    while(tail->next!=NULL)
    {
        tail=tail->next;
        Case *tail1=tail->ProvCase;
        while(tail1->next!=NULL)
        {
            tail1=tail1->next;
            Report *tail2=tail1->CaseRepo;
            while(tail2->next!=NULL)
            {
                tail2=tail2->next;
                if(!strcmp(str,tail2->RepoId))
                {
                    flag=1;
                    return flag;
                }
            }
        }
    }
    return flag;
}

/**
 * 函数名称: TestRepoForChange
 * 函数功能: 测试媒体信息是否存在.
 * 输入参数: str 要测试的报道编号
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
int TestRepoForChange(char *str,char **output)//测试媒体信息是否存在
{
    Province *tail=head;
    int flag=0;
    while(tail->next!=NULL)
    {
        tail=tail->next;
        Case *tail1=tail->ProvCase;
        while(tail1->next!=NULL)
        {
            tail1=tail1->next;
            Report *tail2=tail1->CaseRepo;
            while(tail2->next!=NULL)
            {
                tail2=tail2->next;
                if(!strcmp(str,tail2->RepoId))
                {
                    flag=1;
                    sprintf(output[0],"%s",tail2->RepoCaseId);
                    sprintf(output[1],"%s",tail2->RepoId);
                    sprintf(output[2],"%s",tail2->RepoDate);
                    sprintf(output[3],"%s",tail2->RepoFirm);
                    sprintf(output[4],"%s",tail2->RepoIndex);
                    *output[5]=tail2->RepoField;
                    return flag;
                }
            }
        }
    }
    return flag;
}

/**
 * 函数名称: TestLeader
 * 函数功能: 按省份负责人测试省份信息是否存在.
 * 输入参数: str 要测试的负责人
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
int TestLeader(char *str)//按省份负责人测试省份信息是否存在
{
    Province *tail=head;
    int flag=0;
    while(tail->next!=NULL)
    {
        tail=tail->next;
        if(!strcmp(str,tail->ProvLeader))
        {
            flag=1;
            break;
        }
    }
    return flag;
}

/**
 * 函数名称: TestYear
 * 函数功能: 测试某年份案件信息是否存在.
 * 输入参数: str 要测试的年份
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
int TestYear(char *str)//测试某年份案件信息是否存在
{
    Province *tail=head;
    int flag=0;
    while(tail->next!=NULL)
    {
        tail=tail->next;
        Case *tail1=tail->ProvCase;
        while(tail1->next!=NULL)
        {
            tail1=tail1->next;
            if(strstr(tail1->CaseDate,str))
            {
                flag=1;
                return flag;
            }
        }

    }
    return flag;
}

/**
 * 函数名称: TestBEDate
 * 函数功能: 测试某时间段案件信息是否存在.
 * 输入参数: begin 开始时间；end 截止时间
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
int TestBEDate(char *begin,char *end)//测试某时间段案件信息是否存在
{
    Province *tail=head;
    int flag=0;
    while(tail->next!=NULL)
    {
        tail=tail->next;
        Case *tail1=tail->ProvCase;
        while(tail1->next!=NULL)
        {
            tail1=tail1->next;
            int temp=atoi(tail1->CaseDate);
            if(temp>=atoi(begin)&&temp<=atoi(end))
            {
                flag=1;
                return flag;
            }
        }

    }
    return flag;
}

/**
 * 函数名称: TestNL
 * 函数功能: 按被告姓名和行政级别测试案件信息是否存在.
 * 输入参数: str 被告姓名；c 行政级别
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
int TestNL(char *str,char c)//按被告姓名和行政级别测试案件信息是否存在
{
    Province *tail=head;
    int flag=0;
    while(tail->next!=NULL)
    {
        tail=tail->next;
        Case *tail1=tail->ProvCase;
        while(tail1->next!=NULL)
        {
            tail1=tail1->next;
            if((!strcmp(str,tail1->CaseName))&&(c==tail1->CaseLevel))
            {
                flag=1;
                return flag;
            }
        }

    }
    return flag;
}

/**
 * 函数名称: TestRepoByIF
 * 函数功能: 按案件编号和媒体名称来测试媒体信息是否存在.
 * 输入参数: str1 案件编号；str2 媒体名称
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
int TestRepoByIF(char *str1,char *str2)//按案件编号和媒体名称来测试媒体信息是否存在
{
    Province *tail=head;
    int flag=0;
    while(tail->next!=NULL)
    {
        tail=tail->next;
        Case *tail1=tail->ProvCase;
        while(tail1->next!=NULL)
        {
            tail1=tail1->next;
            Report *tail2=tail1->CaseRepo;
            while(tail2->next!=NULL)
            {
                tail2=tail2->next;
                if((!strcmp(str1,tail2->RepoCaseId))&&(!strcmp(str2,tail2->RepoFirm)))
                {
                    flag=1;
                    return flag;
                }
            }
        }
    }
    return flag;
}

/**
 * 函数名称: TestRepoByDF
 * 函数功能: 按报道日期和媒体名称来测试媒体信息是否存在.
 * 输入参数: str1 报道日期；str2 媒体名称
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
int TestRepoByDF(char *str1,char *str2)//按报道日期和媒体名称来测试媒体信息是否存在
{
    Province *tail=head;
    int flag=0;
    while(tail->next!=NULL)
    {
        tail=tail->next;
        Case *tail1=tail->ProvCase;
        while(tail1->next!=NULL)
        {
            tail1=tail1->next;
            Report *tail2=tail1->CaseRepo;
            while(tail2->next!=NULL)
            {
                tail2=tail2->next;
                if((!strcmp(str1,tail2->RepoDate))&&strstr(tail2->RepoFirm,str2))
                {
                    flag=1;
                    return flag;
                }
            }
        }
    }
    return flag;
}
