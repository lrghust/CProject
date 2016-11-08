#include <stdio.h>
#include <stdarg.h>
#include "mylibrary.h"

/**
 * ��������: mygets
 * ��������: ����һ���ַ���.
 * �������: ��
 * �������: str ָ��洢�˶����ַ������ַ������ָ��
 * �� �� ֵ: �����ɹ�ִ��ʱ����ָ��str���������ļ�������������û�ж���һ���ַ������鱣�ֲ��䣬����NULL��
 *
 * ����˵��: ��
 */
char *mygets(char *str)
{
    int i=0;
    //��һ���ַ��Ĵ���
    char c=getchar();
    if(c==EOF)return NULL;
    if(c=='\n')
    {
        str[i]='\0';
        return str;
    }
    while(1)
    {
        str[i]=c;
        i++;
        c=getchar();
        if(c=='\n'||c==EOF)
        {
            str[i]='\0';
            break;
        }
    }
    return str;
}

/**
 * ��������: myputs
 * ��������: ��ӡ�ַ���.
 * �������: str ָ�����Ҫ������ַ������ַ������ָ��
 * �������: ��
 * �� �� ֵ: ��������ִ��ʱ���طǸ���
 *
 * ����˵��: ��
 */
int myputs(const char *str)
{
    int i=0;
    while(str[i]!='\0')
    {
        putchar(str[i]);
        i++;
    }
    putchar('\n');
    return 0;
}

/**
 * ��������: myprintf
 * ��������: ��ʽ���.
 * �������: str ��������Ҫ����ַ������ʽ˵�������ַ������ɱ�����б����ʽ˵������Ӧ
 * �������: ��
 * �� �� ֵ: ��������ִ��ʱ����������ַ���
 *
 * ����˵��: ��
 */
int myprintf(const char *str, ...)
{
    va_list p;
    va_start(p,str);
    int i=0;
    int d;
    char c;
    char *s;
    float f;
    double lf;

    int count=0;

    while(str[i])
    {
        if(str[i]=='%'&&str[i+1])//��ǰ�ַ�Ϊ%����һ���ַ���Ϊ��
        {
            i++;
            switch(str[i])//�ж��Ƿ��Ǹ�ʽת��
            {
                case '%':
                    putchar('%');
                    count++;
                    break;
                case 'd':
                    d=va_arg(p,int);
                    count+=PrintInt(d);
                    break;
                case 'c':
                    c=va_arg(p,int);
                    putchar(c);
                    count++;
                    break;
                case 's':
                    s=va_arg(p,char *);
                    count+=PrintString(s);
                    break;
                case 'f':
                    f=va_arg(p,double);
                    count+=PrintDouble(f);
                    break;
                case 'l':
                    if(str[i+1]=='f')
                    {
                        i++;
                        lf=va_arg(p,double);
                        count+=PrintDouble(lf);
                        break;
                    }
                    else
                    {
                        putchar('%');
                        putchar('l');
                        count+=2;
                        break;
                    }
                default:
                    putchar('%');
                    putchar(str[i]);
                    count+=2;
                    break;
            }
        }
        else
        {
            putchar(str[i]);
            count++;
        }
        i++;
    }
    va_end(p);
    return count;
}

/**
 * ��������: myscanf
 * ��������: ��ʽ����.
 * �������: str �����˸�ʽ˵�������ַ������ɱ�����б����ʽת������Ӧ
 * �������: ��
 * �� �� ֵ: ��������ִ��ʱ�����������ĸ���
 *
 * ����˵��: ��
 */
int myscanf(const char *str, ...)
{
    va_list p;
    va_start(p,str);
    char temp;
    int i=0;
    int *d;
    char *c;
    char *s;
    float *f;
    double *lf;

    int count=0;

    while(str[i])
    {
        if(str[i]=='%'&&str[i+1])//��ǰ�ַ�Ϊ%����һ���ַ���Ϊ��
        {
            i++;
            switch(str[i])//�ж��Ƿ��Ǹ�ʽת��
            {
                case 'd':
                    d=va_arg(p,int *);
                    DealSpace();
                    if(ScanInt(d))
                        count++;
                    break;
                case 'c':
                    c=va_arg(p,char *);
                    if((*c=getchar())!=EOF)
                        count++;
                    break;
                case 's':
                    s=va_arg(p,char *);
                    DealSpace();
                    if(ScanString(s))
                        count++;
                    break;
                case 'f':
                    f=va_arg(p,float *);
                    DealSpace();
                    if(ScanFloat(f))
                        count++;
                    break;
                case 'l':
                    if(str[i+1]=='f')
                    {
                        i++;
                        lf=va_arg(p,double *);
                        DealSpace();
                        if(ScanDouble(lf))
                            count++;
                        break;
                    }
                default:
                    if((temp=getchar())!='%'||(temp=getchar())!=str[i])
                        va_end(p);
                    return count;
            }
        }
        else if(str[i]==' '||str[i]=='\n'||str[i]=='\t')
            ;
        else
        {
            temp=getchar();
            if(temp!=str[i])
                break;
        }
        i++;
    }
    va_end(p);
    return count;
}

/**
 * ��������: PrintInt
 * ��������: ��ӡ����.
 * �������: n Ҫ��ӡ������
 * �������: ��
 * �� �� ֵ: ���ش�ӡ���ַ���
 *
 * ����˵��: ��
 */
int PrintInt(int n)
{
    int count=0;
    if(n<0)//��������ȡ����ֵ��������1���������
    {
        n=-n;
        count++;
        putchar('-');
    }
    if(n==0)//������
    {
        putchar('0');
        return 1;
    }
    if(n/10==0)//�ݹ���ֹ����
    {
        putchar(n+'0');
        return 1;
    }
    count+=PrintInt(n/10);
    putchar(n%10+'0');
    count++;
    return count;
}

/**
 * ��������: PrintString
 * ��������: ��ӡ�ַ���.
 * �������: str Ҫ��ӡ���ַ���
 * �������: ��
 * �� �� ֵ: ���ش�ӡ���ַ���
 *
 * ����˵��: ��
 */
int PrintString(char *str)
{
    int i=0;
    while(str[i])
    {
        putchar(str[i]);
        i++;
    }
    return i;
}

/**
 * ��������: PrintDouble
 * ��������: ��ӡ˫���ȸ�����.
 * �������: n Ҫ��ӡ�ĸ�����
 * �������: ��
 * �� �� ֵ: ���ش�ӡ���ַ���
 *
 * ����˵��: �����ȸ�����ǿ��ת��Ϊ˫���ȸ�����
 */
int PrintDouble(double n)
{
    int count=1;
    count+=PrintInt(n);
    putchar('.');
    int i;
    if(((n*1e6)-(int)(n*1e6))>=0.5)//С��������λ�ܵ���λӰ����������
        n+=1e-6;
    for(i=1;i<=6;i++)
    {
        putchar(((int)(n*10)-(int)n*10)+'0');
        n=n*10;
        count++;
    }
    return count;
}

/**
 * ��������: ScanInt
 * ��������: ��������.
 * �������: ��
 * �������: n �������������ŵĵ�ַ
 * �� �� ֵ: ����0��ʾ������� 1��ʾ�ɹ�������������
 *
 * ����˵��: ��
 */
int ScanInt(int *n)
{
    int m=0;
    int flag=0;
    while(1)
    {
        char c=getchar();
        if(c>='0'&&c<='9')
        {
            m=m*10+c-'0';
            flag=1;
        }
        else
        {
            ungetc(c,stdin);
            *n=m;
            return flag;
        }
    }
}

/**
 * ��������: ScanString
 * ��������: �����ַ���.
 * �������: ��
 * �������: str ָ�������ַ����׵�ַ
 * �� �� ֵ: ����0��ʾ������� 1��ʾ�ɹ�������������
 *
 * ����˵��: ��
 */
int ScanString(char *str)
{
    char c;
    int i=0;
    while(1)
    {
        c=getchar();
        if(c==' '||c=='\n'||c=='\t'||c==EOF)
        {
            ungetc(c,stdin);
            str[i]='\0';
            return i;
        }
        str[i]=c;
        i++;
    }
}

/**
 * ��������: ScanFloat
 * ��������: ���뵥���ȸ�����.
 * �������: ��
 * �������: n ����ĸ���������ŵĵ�ַ
 * �� �� ֵ: ����0��ʾ������� 1��ʾ�ɹ�������������
 *
 * ����˵��: ��
 */
int ScanFloat(float *n)
{
    char c;
    float m=0;
    int flag=0;//��־�Ƿ������
    int flag1=0;//��־����С����
    float bar=1.0;
    while(1)
    {
        c=getchar();
        if(c>='0'&&c<='9'&&flag1==0)//��������
        {
            m=m*10+c-'0';
            flag=1;
        }
        else if(c=='.'&&flag1==0)//С����
        {
            flag1=1;
        }
        else if(c>='0'&&c<='9'&&flag1==1)//С������
        {
            bar*=0.1;
            m+=bar*(c-'0');
            flag=1;
        }
        else
        {
            ungetc(c,stdin);
            *n=m;
            return flag;
        }
    }
}

/**
 * ��������: ScanDouble
 * ��������: ����˫���ȸ�����.
 * �������: ��
 * �������: n ����ĸ���������ŵĵ�ַ
 * �� �� ֵ: ����0��ʾ������� 1��ʾ�ɹ�������������
 *
 * ����˵��: ��
 */
int ScanDouble(double *n)
{
    char c;
    double m=0;
    int flag=0;//��־�Ƿ������
    int flag1=0;//��־����С����
    double bar=1.0;
    while(1)
    {
        c=getchar();
        if(c>='0'&&c<='9'&&flag1==0)//��������
        {
            m=m*10+c-'0';
            flag=1;
        }
        else if(c=='.'&&flag1==0)//С����
        {
            flag1=1;
        }
        else if(c>='0'&&c<='9'&&flag1==1)//С������
        {
            bar*=0.1;
            m+=bar*(c-'0');
            flag=1;
        }
        else
        {
            ungetc(c,stdin);
            *n=m;
            return flag;
        }
    }
}

/**
 * ��������: DealSpace
 * ��������: �ڶ�ȡ������ʱ������ǰ�Ŀ��ַ�.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��: ��
 */
void DealSpace(void)
{
    while(1)
    {
        char c=getchar();
        if(c!=' '&&c!='\n'&&c!='\t')
        {
            ungetc(c,stdin);
            break;
        }
    }
}
