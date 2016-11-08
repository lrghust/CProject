#include"head.h"
/**
 * 函数名称: InitInfo
 * 函数功能: 初始化链表信息.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: phead 新建的链表头结点指针
 *
 * 调用说明:
 */
Province *InitInfo(void)
{
    char space;//读取文件信息时用于匹配空格
	FILE *pf = fopen("Prov.txt", "r");
	if(!pf)
    {
        printf("信息文件打开失败...\n\n任意键继续");
        getchar();
        Province *phead = (Province *)malloc(sizeof(Province));
        phead->next=NULL;
        return phead;
    }
    //初始化省份信息,要求每条信息顺序与结构成员顺序相同
	Province *phead = (Province *)malloc(sizeof(Province));
	Province *tail = phead;
	char temp[50];
	while (fscanf(pf, "%s", temp) != EOF)
	{
		tail->next = (Province *)malloc(sizeof(Province));
		tail = tail->next;
		strcpy(tail->ProvProv, temp);
		fscanf(pf, "%s%s", tail->ProvLeader, tail->ProvTel);
		tail->ProvCase = (Case *)malloc(sizeof(Case));
		tail->ProvCase->next = NULL;
	}
	tail->next = NULL;
	fclose(pf);

	pf = fopen("Case.txt", "r");
	if(!pf)
    {
        printf("信息文件打开失败...\n\n任意键继续");
        getchar();
        return phead;
    }
    //初始化案件信息，要求每条信息顺序与结构成员顺序相同
    tail = phead;
	Case *tail1 = NULL;
	int flag=0;
	while (fscanf(pf, "%s", temp) != EOF)
	{
	    flag=0;
		while (tail->next != NULL)
		{
			tail = tail->next;
			if (!strcmp(temp, tail->ProvProv))
			{
			    flag=1;
				Case *tail1 = tail->ProvCase;
				while (tail1->next != NULL)tail1 = tail1->next;
				tail1->next = (Case *)malloc(sizeof(Case));
				tail1 = tail1->next;
				strcpy(tail1->CaseProv, temp);
				fscanf(pf, "%s%s%s%c%c%c%c%f%d", tail1->CaseId, tail1->CaseDate, tail1->CaseName, &space, &tail1->CaseLevel, &space, &tail1->CaseCharge, &tail1->CaseMoney, &tail1->CaseJudge);
				tail1->CaseRepo = (Report *)malloc(sizeof(Report));
				tail1->CaseRepo->next = NULL;
				tail1->next=NULL;
				tail = phead;
				break;
			}
		}
		if(!flag)
        {
            printf("案件信息文件有误...\n\n任意键继续");
            getchar();
            fclose(pf);
            return phead;
        }
	}
	fclose(pf);

	pf = fopen("Repo.txt", "r");
	if(!pf)
    {
        printf("信息文件打开失败...\n\n任意键继续");
        getchar();
        return phead;
    }
    //初始化媒体信息，要求每条信息顺序与结构成员顺序相同
	tail = phead;
	tail1 = NULL;
	while (fscanf(pf,"%s", temp) != EOF)
	{
	    flag=0;
		while (tail->next != NULL)
		{
			tail = tail->next;
			tail1 = tail->ProvCase;
			while (tail1->next != NULL)
			{
				tail1 = tail1->next;
				if (!strcmp(tail1->CaseId, temp))
				{
				    flag=1;
				    Report *tail2 = tail1->CaseRepo;
                    while (tail2->next != NULL)
                        tail2 = tail2->next;
                    tail2->next = (Report *)malloc(sizeof(Report));
                    tail2 = tail2->next;
                    strcpy(tail2->RepoCaseId, temp);
                    fscanf(pf, "%s%s%s%s%c%c", tail2->RepoId,tail2->RepoDate, tail2->RepoFirm, tail2->RepoIndex, &space, &tail2->RepoField);
                    tail2->next = NULL;
                    tail = phead;
					break;
				}
			}
			if(flag)
                break;
		}
		if(!flag)
        {
            printf("媒体信息文件有误...\n\n任意键继续");
            getchar();
            fclose(pf);
            return phead;
        }
	}
	fclose(pf);
	return phead;
}
