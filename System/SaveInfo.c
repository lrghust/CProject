#include"head.h"
/**
 * 函数名称: SaveInfo
 * 函数功能: 将链表中的信息保存到文件中.
 * 输入参数: head 主链表头结点指针
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void SaveInfo(Province *head)
{
	FILE *fprov=fopen("Prov.txt","w+");
	FILE *fcase=fopen("Case.txt","w+");
	FILE *frepo=fopen("Repo.txt","w+");
	Province *tail=head;
	while(tail->next!=NULL)
	{
		tail=tail->next;
		fprintf(fprov,"%s %s %s\n",tail->ProvProv,tail->ProvLeader,tail->ProvTel);
		Case *tail1=tail->ProvCase;
		while(tail1->next!=NULL)
		{
			tail1=tail1->next;
			fprintf(fcase,"%s %s %s %s %c %c %f %d\n",tail1->CaseProv,tail1->CaseId,tail1->CaseDate,tail1->CaseName,tail1->CaseLevel,tail1->CaseCharge,tail1->CaseMoney,tail1->CaseJudge);
			Report *tail2=tail1->CaseRepo;
			while(tail2->next!=NULL)
			{
				tail2=tail2->next;
				fprintf(frepo,"%s %s %s %s %s %c\n",tail2->RepoCaseId,tail2->RepoId,tail2->RepoDate,tail2->RepoFirm,tail2->RepoIndex,tail2->RepoField);
			}
		}
	}
	fclose(fprov);
	fclose(fcase);
	fclose(frepo);
}
