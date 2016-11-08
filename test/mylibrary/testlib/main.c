#include "mylibrary.h"

int main()
{
    int d;
    char c;
    float f;
    double lf;
    char str[20];
    myputs("Your name:");
    mygets(str);
    myputs("Your Level:");
    myscanf("%c",&c);
    myputs("Your mark, your GPA and your rank:");
    myscanf("%f%lf%d",&f,&lf,&d);
    myprintf("\nHello %s!\nYour level is %c and you have got %f marks in your math test.\n",str,c,f);
    myprintf("And your GPA is %lf.\nYou rank %d in the class.\n",lf,d);
    return 0;
}
