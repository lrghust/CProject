#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXLEN 10000
#define KB 1024
#define VOLUME 16

//操作指令名称
const char *OP_NAME[]={"HLT","JMP","CJMP","OJMP","CALL","RET",
					   "PUSH","POP",
					   "LOADB","LOADW","STOREB","STOREW","LOADI","NOP",
					   "IN","OUT",
					   "ADD","ADDI","SUB","SUBI","MUL","DIV",
					   "AND","OR","NOR","NOTB","SAL","SAR",
					   "EQU","LT","LTE","NOTC",
					   "BYTE","WORD"};
//操作指令对应的类型
const int OP_STYLE[]={1,2,2,2,2,1,
					  3,3,
					  4,4,4,4,5,1,
					  6,6,
					  7,5,7,5,7,7,
					  7,7,7,8,7,7,
					  8,8,8,1,
					  0,0};

typedef struct Label{
	unsigned long LabelAddress;
	char LabelName[MAXLEN];
	struct Label *next;
}Label;
typedef struct Data{
	char num;
}Data;

Label *PreDeal(char *,char *);
unsigned long SearchLabel(Label *head,char *str);

int main(int argc, char *argv[])
{
	Label *plabel=PreDeal(argv[1],argv[2]);
	FILE *in=fopen(argv[1],"r");
	FILE *out=fopen(argv[2],"ab+");
	char line[MAXLEN];
	char opname[MAXLEN];
	char label[MAXLEN];
	char reg[2],reg1[2],reg2[2];
	unsigned long cmdnum;
	unsigned long addnum;
	unsigned long regnum;
	unsigned long reg1num;
	unsigned long reg2num;
	short imdnum;
	unsigned long portnum;
	while(fgets(line,MAXLEN,in)!=NULL)
	{
		int flag=0;//是否有label的标志
		char top[MAXLEN];
		sscanf(line,"%s",top);
		if(line[0]=='\n'||top[0]=='#')//空行或者注释行跳过
			continue;
		char *end=strchr(line,'#');
		if(end)
            *end='\0';//注释改为字符串尾
		sscanf(line,"%s",opname);
		if(opname[strlen(opname)-1]==':')//是否有标号
		{
			flag=1;
			sscanf(line,"%s%s",opname,opname);
		}
		unsigned long i=0;//i是指令对应编码数
		while(strcmp(opname,OP_NAME[i]))//查找指令
		{
			i++;
		}
		switch(OP_STYLE[i])
		{
			case 0:
					if(i==32)//BYTE
					{
                        char dec[MAXLEN];
                        char data[MAXLEN];
                        data[0]='\0';
                        char symbol[MAXLEN];
						sscanf(line,"%s%s%s%s",opname,dec,data,data);//第三个字符串是等号
						int j=0;//dec计数器
						int flag1=0;//[的标记
						int memvol=0;
						while(dec[j])
						{
							if(dec[j]=='[')//遇到[取出symbol，BYTE声明一个数据域的数据
							{
								dec[j]='\0';
								flag1=1;
								j++;
								while(dec[j]!=']')
								{
									memvol=memvol*10+dec[j]-'0';
									j++;
								}
								break;
							}
							j++;
						}
						if(!flag1)
                        {
                            memvol=1;
                        }
                        strcpy(symbol,dec);

                        char tempnum=0;
                        if(data[0]=='\0')//未初始化变量
                        {
                            int k;
                            for(k=1;k<=memvol;k++)
                            {
                                //fprintf(out,"0x%hx ",tempnum);
                                fwrite(&tempnum,1,1,out);
                            }
                        }
                        else if(data[0]=='{')//初始化数据域
                        {
                            int k;//数据个数
                            int l=0;//data数组元素位置
                            for(k=1;k<=memvol;k++)
                            {
                                l++;
                                tempnum=0;
                                int flag2=0;//负号的标记
                                while(data[l]!=','&&data[l]!='}')
                                {
                                    if(data[l]=='-')flag2=1;
                                    tempnum=tempnum*10+data[l]-'0';
                                    l++;
                                }
                                if(flag2)tempnum=0-tempnum;
                                //fprintf(out,"0x%hx ",tempnum);
                                fwrite(&tempnum,1,1,out);
                            }
                        }
                        else//初始化单个数据
                        {
                            int l=0;
                            tempnum=0;
                            int flag2=0;//负号的标记
                            while(data[l])
                            {
                                if(data[l]=='-')flag2=1;
                                tempnum=tempnum*10+data[l]-'0';
                                l++;
                            }
                            if(flag2)tempnum=0-tempnum;
                            //fprintf(out,"0x%hx",tempnum);
                            fwrite(&tempnum,1,1,out);
                        }
                        //fprintf(out,"\n");
                    }
					else if(i==33)//WORD
					{
						char dec[MAXLEN];
                        char data[MAXLEN];
                        char symbol[MAXLEN];
						sscanf(line,"%s%s%s%s",opname,dec,data,data);//第三个字符串是等号
						int j=0;//dec计数器
						int flag1=0;//[的标记
						int memvol=0;
						while(dec[j])
						{
							if(dec[j]=='[')//遇到[取出symbol，BYTE声明一个数据域的数据
							{
								dec[j]='\0';
								flag1=1;
								j++;
								while(dec[j]!=']')
								{
									memvol=memvol*10+dec[j]-'0';
									j++;
								}
								break;
							}
							j++;
						}
						if(!flag1)
                        {
                            memvol=1;
                        }
                        strcpy(symbol,dec);

                        short tempnum=0;
                        if(data[0]=='\0')//未初始化变量
                        {
                            int k;
                            for(k=1;k<=memvol;k++)
                            {
                                //fprintf(out,"0x%hx ",tempnum);
                                fwrite(&tempnum,2,1,out);
                            }
                        }
                        else if(data[0]=='{')//初始化数据域
                        {
                            int k;//数据个数
                            int l=0;//data数组元素位置
                            for(k=1;k<=memvol;k++)
                            {
                                l++;
                                tempnum=0;
                                int flag2=0;//负号的标记
                                while(data[l]!=','&&data[l]!='}')
                                {
                                    if(data[l]=='-')flag2=1;
                                    tempnum=tempnum*10+data[l]-'0';
                                    l++;
                                }
                                if(flag2)tempnum=0-tempnum;
                                //fprintf(out,"0x%hx ",tempnum);
                                fwrite(&tempnum,2,1,out);
                            }
                        }
                        else//初始化单个数据
                        {
                            int l=0;
                            tempnum=0;
                            int flag2=0;//负号的标记
                            while(data[l])
                            {
                                if(data[l]=='-')flag2=1;
                                tempnum=tempnum*10+data[l]-'0';
                                l++;
                            }
                            if(flag2)tempnum=0-tempnum;
                            //fprintf(out,"0x%hx",tempnum);
                            fwrite(&tempnum,2,1,out);
                        }
                        //fprintf(out,"\n");
					}
					continue;
			case 1:
					cmdnum=i<<27;
					break;
			case 2:
					if(flag)//如果有标号，多读一个字符串
					{
						sscanf(line,"%s%s%s",opname,opname,label);
					}
					else//如果没有标号
					{
						sscanf(line,"%s%s",opname,label);
					}
					addnum=SearchLabel(plabel,label);
					cmdnum=(i<<27)|(addnum&0x00ffffff);
					break;
			case 3:
					if(flag)//如果有标号，多读一个字符串
					{
						sscanf(line,"%s%s%s",opname,opname,reg);
					}
					else//如果没有标号
					{
						sscanf(line,"%s%s",opname,reg);
					}
					if(reg[0]=='Z')
						regnum=0;
					else
						regnum=reg[0]-'A'+1;
					cmdnum=(i<<27)|((regnum&0x00000007)<<24);
					break;
			case 4:
					if(flag)//如果有标号，多读一个字符串
					{
						sscanf(line,"%s%s%s%s",opname,opname,reg,label);
					}
					else//如果没有标号
					{
						sscanf(line,"%s%s%s",opname,reg,label);
					}
					if(reg[0]=='Z')
						regnum=0;
					else
						regnum=reg[0]-'A'+1;
					addnum=SearchLabel(plabel,label);
					cmdnum=(i<<27)|((regnum&0x00000007)<<24)|(addnum&0x00ffffff);
					break;
			case 5:
					if(flag)//如果有标号，多读一个字符串
					{
						sscanf(line,"%s%s%s%hd",opname,opname,reg,&imdnum);
					}
					else//如果没有标号
					{
						sscanf(line,"%s%s%hd",opname,reg,&imdnum);
					}
					if(reg[0]=='Z')
						regnum=0;
					else
						regnum=reg[0]-'A'+1;
					cmdnum=(i<<27)|((regnum&0x00000007)<<24)|(imdnum&0xffff);
					break;
			case 6:
					if(flag)//如果有标号，多读一个字符串
					{
						sscanf(line,"%s%s%s%lu",opname,opname,reg,&portnum);
					}
					else//如果没有标号
					{
						sscanf(line,"%s%s%lu",opname,reg,&portnum);
					}
					if(reg[0]=='Z')
						regnum=0;
					else
						regnum=reg[0]-'A'+1;
					cmdnum=(i<<27)|((regnum&0x00000007)<<24)|(portnum&0x000000ff);
					break;
			case 7:
					if(flag)//如果有标号，多读一个字符串
					{
						sscanf(line,"%s%s%s%s%s",opname,opname,reg,reg1,reg2);
					}
					else//如果没有标号
					{
						sscanf(line,"%s%s%s%s",opname,reg,reg1,reg2);
					}
					if(reg[0]=='Z')
						regnum=0;
					else
						regnum=reg[0]-'A'+1;
					if(reg1[0]=='Z')
						reg1num=0;
					else
						reg1num=reg1[0]-'A'+1;
					if(reg2[0]=='Z')
						reg2num=0;
					else
						reg2num=reg2[0]-'A'+1;
					cmdnum=(i<<27)|((regnum&0x00000007)<<24)|((reg1num&0x0000000f)<<20)|((reg2num&0x0000000f)<<16);
					break;
			case 8:
					if(flag)//如果有标号，多读一个字符串
					{
						sscanf(line,"%s%s%s%s",opname,opname,reg,reg1);
					}
					else//如果没有标号
					{
						sscanf(line,"%s%s%s",opname,reg,reg1);
					}
					if(reg[0]=='Z')
						regnum=0;
					else
						regnum=reg[0]-'A'+1;
					if(reg1[0]=='Z')
						reg1num=0;
					else
						reg1num=reg1[0]-'A'+1;
					cmdnum=(i<<27)|((regnum&0x00000007)<<24)|((reg1num&0x0000000f)<<20);
					break;
		}
		fwrite(&cmdnum,4,1,out);
	}
	fclose(in);
	fclose(out);
	return 0;
}

/**
 * 函数名称: PreDeal
 * 函数功能: 对汇编文件进行预处理，存储所有标号对应的地址，统计BYTE和WORD变量数据段数目、代码段数目，写到二进制文件开头.
 * 输入参数: input 汇编文件名
 * 输出参数: output dat文件名
 * 返 回 值: 返回存有所有标签信息的链表头结点指针
 *
 * 调用说明: 无
 */
Label *PreDeal(char *input,char *output)//存储所有标号对应的地址
{
	FILE *in=fopen(input,"r+");
	FILE *out=fopen(output,"wb+");
	char line[MAXLEN];
	char opname[MAXLEN];
	char dec[MAXLEN];
	unsigned long datanum=0;
	unsigned long codenum=0;
    unsigned long codeadd=0;
	unsigned long dataadd=VOLUME*KB;
	Label *head=(Label *)malloc(sizeof(Label));
	Label *tail=head;
	tail->next=NULL;
	while(fgets(line,MAXLEN,in)!=NULL)
	{
	    sscanf(line,"%s",opname);
		if(line[0]=='\n'||opname[0]=='#')//跳过空行和注释行
			continue;
		if(!strcmp(opname,"BYTE")||!strcmp(opname,"WORD"))//伪指令是数据段
		{
            char symbol[MAXLEN];
            sscanf(line,"%s%s",opname,dec);//第三个字符串是等号
            int j=0;//dec计数器
            int flag1=0;//[的标记
            int memvol=0;
            while(dec[j])
            {
                if(dec[j]=='[')//遇到[取出symbol，BYTE声明一个数据域的数据
                {
                    dec[j]='\0';
                    flag1=1;
                    j++;
                    while(dec[j]!=']')
                    {
                        memvol=memvol*10+dec[j]-'0';
                        j++;
                    }
                    break;
                }
                j++;
            }
            if(!flag1)
            {
                memvol=1;
            }

            strcpy(symbol,dec);

            //把symbol存入Label链表，更新数据域地址
            tail->next=(Label *)malloc(sizeof(Label));
            tail=tail->next;
            strcpy(tail->LabelName,symbol);
            tail->LabelAddress=dataadd;
            tail->next=NULL;
            if(!strcmp(opname,"WORD"))//WORD
                memvol*=2;
            dataadd+=memvol;
            datanum+=memvol;

			continue;
		}
        codenum++;
		if(opname[strlen(opname)-1]==':')
		{
			opname[strlen(opname)-1]='\0';
			tail->next=(Label *)malloc(sizeof(Label));
			tail=tail->next;
			tail->LabelAddress=codeadd;
			strcpy(tail->LabelName,opname);
			tail->next=NULL;
		}
		codeadd+=4;
	}
	//fprintf(out,"0x%x\n",datanum);
	fwrite(&datanum,4,1,out);
	fwrite(&codenum,4,1,out);
	fclose(in);
	fclose(out);
	return head;
}

/**
 * 函数名称: SearchLabel
 * 函数功能: 搜索标签获取地址.
 * 输入参数: head 存有所有标签信息的链表头结点指针；str 标签名
 * 输出参数: 无
 * 返 回 值: 标签对应地址值
 *
 * 调用说明: 无
 */
unsigned long SearchLabel(Label *head,char *str)
{
	Label *tail=head;
	while(tail->next!=NULL)
	{
		tail=tail->next;
		if(!strcmp(tail->LabelName,str))
		{
			return tail->LabelAddress;
		}
	}
	return 0;
}
