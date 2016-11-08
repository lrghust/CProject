#include"head.h"
/**
 * 函数名称: RestoreInfo
 * 函数功能: 从备份文件中还原信息，新建链表，并保存.
 * 输入参数: head 主链表头结点指针；path 文件路径
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void RestoreInfo(Province **head,char *path)
{
    char space;
    int flag=0;
	FILE *pf = fopen(path, "r");
	if(!pf)
    {
        char *plabel_name[] = {"文件打开失败！",
                               "确定"
                          };
        ShowModule(plabel_name, 2);
        Province *phead = (Province *)malloc(sizeof(Province));
        *head=phead;
        return;
    }
	Province *phead = (Province *)malloc(sizeof(Province));
	Province *tail = phead;
	tail->next=NULL;
	int num;
	char temp[50];
	while(fscanf(pf,"%d",&num)!=EOF)
	{
		if(num==1)
		{
			tail=phead;
			while(tail->next!=NULL)
				tail=tail->next;
			tail->next = (Province *)malloc(sizeof(Province));
			tail = tail->next;
			fscanf(pf, "%s%s%s", tail->ProvProv,tail->ProvLeader, tail->ProvTel);
			tail->ProvCase = (Case *)malloc(sizeof(Case));
			tail->ProvCase->next = NULL;
			tail->next=NULL;
		}
		else if(num==2)
		{
		    flag=0;
			tail=phead;
			fscanf(pf,"%s",temp);
			while (tail->next != NULL)
			{
				tail = tail->next;
				if (!strcmp(temp, tail->ProvProv))
				{
				    flag=1;
					Case *tail1 = tail->ProvCase;
					while (tail1->next != NULL)
						tail1 = tail1->next;
					tail1->next = (Case *)malloc(sizeof(Case));
					tail1 = tail1->next;
					strcpy(tail1->CaseProv, temp);
					fscanf(pf, "%s%s%s%c%c%c%c%f%d", tail1->CaseId, tail1->CaseDate, tail1->CaseName, &space, &tail1->CaseLevel, &space, &tail1->CaseCharge, &tail1->CaseMoney, &tail1->CaseJudge);
					tail1->CaseRepo = (Report *)malloc(sizeof(Report));
					tail1->CaseRepo->next = NULL;
					tail1->next=NULL;
					break;
				}
			}
			if(!flag)
            {
                char *plabel_name[] = {"备份文件有误！",
                                        "确定"
                                        };
                ShowModule(plabel_name, 2);
                Province *phead = (Province *)malloc(sizeof(Province));
                *head=phead;
                return;
            }
		}
		else if(num==3)
		{
		    flag=0;
			tail=phead;
			Case *tail1=NULL;
			fscanf(pf,"%s",temp);
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
                char *plabel_name[] = {"备份文件有误！",
                                        "确定"
                                        };
                ShowModule(plabel_name, 2);
                Province *phead = (Province *)malloc(sizeof(Province));
                *head=phead;
                return;
            }
		}
	}
	fclose(pf);
	*head=phead;
	SaveInfo(*head);
    char *plabel_name[] = {"恢复成功！",
                            "确定"
                          };
    ShowModule(plabel_name, 2);
}
