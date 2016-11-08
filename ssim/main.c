#include<stdio.h>
#include<string.h>
#include<io.h>

#define VOLUME 16//每段内存大小
#define KB 1024
#define MEM_SIZE 4*VOLUME*KB//内存大小

//指令中不同字段的含义
#define OP ((IR>>27)&0x1f)
#define REG0 ((IR>>24)&0x7)
#define REG1 ((IR>>20)&0xf)
#define REG2 ((IR>>16)&0xf)
#define ADDR (IR&0xffffff)
#define PORT (IR&0xff)//端口

unsigned long *PC;//程序计数器
unsigned long IR;//指令寄存器
unsigned char MEM[MEM_SIZE+1];//声明一个数组模拟内存
short IMME;//立即数
short REG[8];//通用寄存器

//专用寄存器
#define CS 0//代码段
#define DS VOLUME*KB//数据段
#define SS VOLUME*KB*2//堆栈段寄存器
#define ES VOLUME*KB-1//附加段寄存器
unsigned short *PSS=(unsigned short *)(MEM+SS);
unsigned short *PES=(unsigned short *)(MEM+ES);

//程序状态字
typedef struct S_PROG_STATE_WORD{
    unsigned short of:1;//溢出标志
    unsigned short cf:1;//比较标志
    unsigned short pad:14;
}S_PROG_STATE_WORD;

typedef union U_PROG_STATE_WORD{
	S_PROG_STATE_WORD S_PSW;
	unsigned short PSW;
}U_PROG_STATE_WORD;

U_PROG_STATE_WORD U_PSW;

//端口
const unsigned short INPUT=0;//Port#0
const unsigned short OUTPUT=15;//Port#15

//指令对应函数
int HLT(void);
int JMP(void);
int CJMP(void);
int OJMP(void);
int CALL(void);
int RET(void);
int PUSH(void);
int POP(void);
int LOADB(void);
int LOADW(void);
int STOREB(void);
int STOREW(void);
int LOADI(void);
int NOP(void);
int IN(void);
int OUT(void);
int ADD(void);
int ADDI(void);
int SUB(void);
int SUBI(void);
int MUL(void);
int DIV(void);
int AND(void);
int OR(void);
int NOR(void);
int NOTB(void);
int SAL(void);
int SAR(void);
int EQU(void);
int LT(void);
int LTE(void);
int NOTC(void);

//函数指针数组
int (*OP_FUN[])(void)={
	HLT,JMP,CJMP,OJMP,CALL,RET,
	PUSH,POP,
	LOADB,LOADW,STOREB,STOREW,LOADI,NOP,
	IN,OUT,
	ADD,ADDI,SUB,SUBI,MUL,DIV,
	AND,OR,NOR,NOTB,SAL,SAR,
	EQU,LT,LTE,NOTC
};


int main(int argc,char *argv[])
{
    FILE *in=fopen(argv[1],"rb");
    unsigned long codenum;//代码段指令数
    unsigned long datanum;//数据段字节数
	memset(MEM,'\0',sizeof(MEM));//将内存全部置为空字符
    fread(&datanum,4,1,in);//读取数据段字节数
    fread(&codenum,4,1,in);//读取指令数
    fread(MEM+DS,1,datanum,in);//读取数据到内存数据段中
    fread(MEM+CS,4,codenum,in);//读取指令到代码段中
    //printf("%d %d",codenum,datanum);
	PC=(unsigned long *)(MEM+CS);//指向代码段开头
	while(1)//取一条指令
	{
	    IR=*PC;
		PC++;//指令计数器指向下一条指令
		if(!((*OP_FUN[OP])()))//执行对应的函数
			break;
	}
	fclose(in);
	return 0;
}

//指令对应函数
int HLT(void)
{
	return 0;
}
int JMP(void)
{
	PC=(unsigned long *)(MEM+ADDR);
	return 1;
}
int CJMP(void)
{
	if(U_PSW.S_PSW.cf)
	{
	    PC=(unsigned long *)(MEM+ADDR);
	}
	return 1;
}
int OJMP(void)
{
    if(U_PSW.S_PSW.of)
    {
        PC=(unsigned long *)(MEM+ADDR);
    }
    return 1;
}
int CALL(void)
{
    int i;
	for(i=1;i<8;i++)//保存通用寄存器A-G
	{
		*PES--=REG[i];
	}
	*PES--=U_PSW.PSW;//保存程序状态字
	unsigned long *temp=(unsigned long *)--PES;
	*temp=PC;//保存程序计数器
	PES--;
	PC=(unsigned long *)(MEM+ADDR);
	return 1;
}
int RET(void)
{

    PES++;
    unsigned long *temp=(unsigned long *)PES;
	PC=*temp;
	PES+=2;
	U_PSW.PSW=*PES++;
	int i;
	for(i=7;i>0;i--)
	{
		REG[i]=*PES++;
	}
	PES--;//最后一组循环时指针到达ES段外，减一回到ES段底端
	return 1;
}
int PUSH(void)
{
	*PSS++=REG[REG0];
	return 1;
}
int POP(void)
{
	REG[REG0]=*--PSS;
	return 1;
}
int LOADB(void)
{
    char *p=(char *)(MEM+ADDR);
    REG[REG0]=*(p+REG[7]);
    //printf("%d",REG[REG0]);
    return 1;
}
int LOADW(void)
{
    short *p=(short *)(MEM+ADDR);
    REG[REG0]=*(p+REG[7]);
    //printf("%d",REG[REG0]);
    return 1;
}
int STOREB(void)
{
    char *p=(char *)(MEM+ADDR);
    *(p+REG[7])=REG[REG0];
    return 1;
}
int STOREW(void)
{
    short *p=(short *)(MEM+ADDR);
    *(p+REG[7])=REG[REG0];
    return 1;
}
int LOADI(void)
{
    IMME=IR&0xffff;
    REG[REG0]=IMME;
    //printf("%d",REG[REG0]);
    return 1;
}
int NOP(void)
{
    return 1;
}
int IN(void)
{
    char input;
    read(0,&input,1);
    REG[REG0]=input;
    return 1;
}
int OUT(void)
{
    char output=(char)REG[REG0];
    write(1,&output,1);
    return 1;
}
int ADD(void)
{
    int temp=REG[REG1]+REG[REG2];
    if(temp>32767||temp<-32768)
    {
        U_PSW.S_PSW.of=1;
    }
    else
    {
        U_PSW.S_PSW.of=0;
    }
    REG[REG0]=REG[REG1]+REG[REG2];
    return 1;
}
int ADDI(void)
{
    IMME=IR&0xffff;
    int temp=REG[REG0]+IMME;
    if(temp>32767||temp<-32768)
    {
        U_PSW.S_PSW.of=1;
    }
    else
    {
        U_PSW.S_PSW.of=0;
    }
    REG[REG0]=REG[REG0]+IMME;
    return 1;
}
int SUB(void)
{
    int temp=REG[REG1]-REG[REG2];
    if(temp>32767||temp<-32768)
    {
        U_PSW.S_PSW.of=1;
    }
    else
    {
        U_PSW.S_PSW.of=0;
    }
    REG[REG0]=REG[REG1]-REG[REG2];
    return 1;
}
int SUBI(void)
{
    IMME=IR&0xffff;
    int temp=REG[REG0]-IMME;
    if(temp>32767||temp<-32768)
    {
        U_PSW.S_PSW.of=1;
    }
    else
    {
        U_PSW.S_PSW.of=0;
    }
    REG[REG0]=REG[REG0]-IMME;
    return 1;
}
int MUL(void)
{
    int temp=REG[REG1]*REG[REG2];
    if(temp>32767||temp<-32768)
    {
        U_PSW.S_PSW.of=1;
    }
    else
    {
        U_PSW.S_PSW.of=0;
    }
    REG[REG0]=REG[REG1]*REG[REG2];
    return 1;
}
int DIV(void)
{
    if(REG[REG2]==0)
    {
        printf("ERROR!\n");
        return 0;
    }
    else
    {
        REG[REG0]=REG[REG1]/REG[REG2];
        return 1;
    }
}
int AND(void)
{
    REG[REG0]=REG[REG1]&REG[REG2];
    return 1;
}
int OR(void)
{
    REG[REG0]=REG[REG1]|REG[REG2];
    return 1;
}
int NOR(void)
{
    REG[REG0]=REG[REG1]^REG[REG2];
    return 1;
}
int NOTB(void)
{
    REG[REG0]=~REG[REG1];
    return 1;
}
int SAL(void)
{
    REG[REG0]=REG[REG1]<<REG[REG2];
    return 1;
}
int SAR(void)
{
    REG[REG0]=REG[REG1]>>REG[REG2];
    return 1;
}
int EQU(void)
{
    U_PSW.S_PSW.cf=(REG[REG0]==REG[REG1]);
    return 1;
}
int LT(void)
{
    //printf("%hd %hd",REG[REG0],REG[REG1]);
    U_PSW.S_PSW.cf=(REG[REG0]<REG[REG1]);
    //printf("%hd %hd",REG[2],REG[REG1]);
    return 1;
}
int LTE(void)
{
    U_PSW.S_PSW.cf=(REG[REG0]<=REG[REG1]);
    return 1;
}
int NOTC(void)
{
    U_PSW.S_PSW.cf=!U_PSW.S_PSW.cf;
    return 1;
}
