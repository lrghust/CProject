#include"head.h"
/**
 * 函数名称: BackupInfo
 * 函数功能: 备份信息.
 * 输入参数: head 链表头结点指针
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:将链表中信息备份至Backup.txt文件中以便进行数据恢复
 */
void BackupInfo(Province *head)
{
	FILE *p=fopen("Backup.txt","w+");
	Province *tail=head;
	while(tail->next!=NULL)//第一级链表保存省份信息
	{
		tail=tail->next;
		fprintf(p,"%d %s %s %s\n",1,tail->ProvProv,tail->ProvLeader,tail->ProvTel);
		Case *tail1=tail->ProvCase;
		while(tail1->next!=NULL)//第二级链表保存案件信息
		{
			tail1=tail1->next;
			fprintf(p,"%d %s %s %s %s %c %c %f %d\n",2,tail1->CaseProv,tail1->CaseId,tail1->CaseDate,tail1->CaseName,tail1->CaseLevel,tail1->CaseCharge,tail1->CaseMoney,tail1->CaseJudge);
			Report *tail2=tail1->CaseRepo;
			while(tail2->next!=NULL)//第三级链表保存媒体信息
			{
				tail2=tail2->next;
				fprintf(p,"%d %s %s %s %s %s %c\n",3,tail2->RepoCaseId,tail2->RepoId,tail2->RepoDate,tail2->RepoFirm,tail2->RepoIndex,tail2->RepoField);
			}
		}
	}
	fclose(p);
}
