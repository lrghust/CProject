#include <stdio.h>
#include <stdarg.h>
#include "mylibrary.h"

/**
 * 函数名称: mygets
 * 函数功能: 读入一行字符串.
 * 输入参数: 无
 * 输出参数: str 指向存储了读入字符串的字符数组的指针
 * 返 回 值: 函数成功执行时返回指针str；若遇到文件结束且数组中没有读入一个字符，数组保持不变，返回NULL；
 *
 * 调用说明: 无
 */
char *mygets(char *str)
{
    int i=0;
    //第一个字符的处理
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
 * 函数名称: myputs
 * 函数功能: 打印字符串.
 * 输入参数: str 指向存有要输出的字符串的字符数组的指针
 * 输出参数: 无
 * 返 回 值: 函数正常执行时返回非负数
 *
 * 调用说明: 无
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
 * 函数名称: myprintf
 * 函数功能: 格式输出.
 * 输入参数: str 包含了需要输出字符串与格式说明符的字符串；可变参数列表与格式说明符对应
 * 输出参数: 无
 * 返 回 值: 函数正常执行时返回输出的字符数
 *
 * 调用说明: 无
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
        if(str[i]=='%'&&str[i+1])//当前字符为%且下一个字符不为空
        {
            i++;
            switch(str[i])//判断是否是格式转换
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
 * 函数名称: myscanf
 * 函数功能: 格式输入.
 * 输入参数: str 包含了格式说明符的字符串；可变参数列表与格式转换符对应
 * 输出参数: 无
 * 返 回 值: 函数正常执行时返回输入的项的个数
 *
 * 调用说明: 无
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
        if(str[i]=='%'&&str[i+1])//当前字符为%且下一个字符不为空
        {
            i++;
            switch(str[i])//判断是否是格式转换
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
 * 函数名称: PrintInt
 * 函数功能: 打印整数.
 * 输入参数: n 要打印的整数
 * 输出参数: 无
 * 返 回 值: 返回打印的字符数
 *
 * 调用说明: 无
 */
int PrintInt(int n)
{
    int count=0;
    if(n<0)//处理负数，取绝对值，计数加1，输出负号
    {
        n=-n;
        count++;
        putchar('-');
    }
    if(n==0)//处理零
    {
        putchar('0');
        return 1;
    }
    if(n/10==0)//递归终止条件
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
 * 函数名称: PrintString
 * 函数功能: 打印字符串.
 * 输入参数: str 要打印的字符串
 * 输出参数: 无
 * 返 回 值: 返回打印的字符数
 *
 * 调用说明: 无
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
 * 函数名称: PrintDouble
 * 函数功能: 打印双精度浮点数.
 * 输入参数: n 要打印的浮点数
 * 输出参数: 无
 * 返 回 值: 返回打印的字符数
 *
 * 调用说明: 单精度浮点数强制转换为双精度浮点数
 */
int PrintDouble(double n)
{
    int count=1;
    count+=PrintInt(n);
    putchar('.');
    int i;
    if(((n*1e6)-(int)(n*1e6))>=0.5)//小数点后第六位受第七位影响四舍五入
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
 * 函数名称: ScanInt
 * 函数功能: 读入整数.
 * 输入参数: 无
 * 输出参数: n 读入的整数所存放的地址
 * 返 回 值: 返回0表示读入出错 1表示成功读入整型数据
 *
 * 调用说明: 无
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
 * 函数名称: ScanString
 * 函数功能: 读入字符串.
 * 输入参数: 无
 * 输出参数: str 指向读入的字符串首地址
 * 返 回 值: 返回0表示读入出错 1表示成功读入整型数据
 *
 * 调用说明: 无
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
 * 函数名称: ScanFloat
 * 函数功能: 读入单精度浮点数.
 * 输入参数: 无
 * 输出参数: n 读入的浮点数所存放的地址
 * 返 回 值: 返回0表示读入出错 1表示成功读入整型数据
 *
 * 调用说明: 无
 */
int ScanFloat(float *n)
{
    char c;
    float m=0;
    int flag=0;//标志是否读到数
    int flag1=0;//标志读到小数点
    float bar=1.0;
    while(1)
    {
        c=getchar();
        if(c>='0'&&c<='9'&&flag1==0)//整数部分
        {
            m=m*10+c-'0';
            flag=1;
        }
        else if(c=='.'&&flag1==0)//小数点
        {
            flag1=1;
        }
        else if(c>='0'&&c<='9'&&flag1==1)//小数部分
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
 * 函数名称: ScanDouble
 * 函数功能: 读入双精度浮点数.
 * 输入参数: 无
 * 输出参数: n 读入的浮点数所存放的地址
 * 返 回 值: 返回0表示读入出错 1表示成功读入整型数据
 *
 * 调用说明: 无
 */
int ScanDouble(double *n)
{
    char c;
    double m=0;
    int flag=0;//标志是否读到数
    int flag1=0;//标志读到小数点
    double bar=1.0;
    while(1)
    {
        c=getchar();
        if(c>='0'&&c<='9'&&flag1==0)//整数部分
        {
            m=m*10+c-'0';
            flag=1;
        }
        else if(c=='.'&&flag1==0)//小数点
        {
            flag1=1;
        }
        else if(c>='0'&&c<='9'&&flag1==1)//小数部分
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
 * 函数名称: DealSpace
 * 函数功能: 在读取数据项时跳过项前的空字符.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明: 无
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
