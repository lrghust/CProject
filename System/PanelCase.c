#include"head.h"
/**
 * 函数名称: PanelInputCaseInfo
 * 函数功能: 显示录入案件信息的窗口.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void PanelInputCaseInfo(void)//用于录入案件信息的窗口
{
    char *plabel_name[] = {"案件编号",
                           "            ",//12
                           "立案日期",
						   "          ",//10
						   "所属省份",
						   "        ",//8
                           "被告人姓名",
                           "               ",//15
                           "行政级别",
"副科级","正科级","副处级","正处级","副厅级","正厅级","副部级","正部级及以上",
                           "主要罪名",
"受贿","贪污","挪用公款","渎职","滥用职权","其他",
                           "涉案金额(万)",
                           "          ",//10
                           "刑事处罚",
"有期徒刑(年)","   "/*3*/,"无期徒刑","死刑",
                           "确定"
                          };
    char **pString=plabel_name;
	int n=32;
	LABEL_BUNDLE labels;
    HOT_AREA areas;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int iHot = 1;
    int i, maxlen, str_len;

    for (i=0,maxlen=0; i<n; i++) {
        str_len = strlen(pString[i]);
        if (maxlen < str_len) {
            maxlen = str_len;
        }
    }

    pos.X = maxlen*5;
    pos.Y = n - 12;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X ;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y;

    att =  BACKGROUND_GREEN ;  /*绿底黑字*/
    labels.num = n;
    labels.ppLabel = pString;
    COORD aLoc[n];

    for (i=0; i<=8; i+=2) {
        aLoc[i].X = rcPop.Left + 3;
        aLoc[i].Y = rcPop.Top + 1 + i;

        aLoc[i+1].X = aLoc[i].X+10;
        aLoc[i+1].Y = aLoc[i].Y;
    }
    for(i=10;i<=16;i++)
    {
        aLoc[i].X=aLoc[i-1].X+7;
        aLoc[i].Y=aLoc[i-1].Y;
    }
    aLoc[i].X = rcPop.Left + 3;
    aLoc[i].Y = rcPop.Top + 1 + 10;
    for(i=18;i<=23;i++)
    {
        aLoc[i].X = aLoc[i-1].X+10;
        aLoc[i].Y = aLoc[i-1].Y;
    }
    for(i=24;i<=26;i+=2)
    {
        aLoc[i].X = rcPop.Left + 3;
        aLoc[i].Y = rcPop.Top + 1 + 12+i-24;

        aLoc[i+1].X = aLoc[i].X+12;
        aLoc[i+1].Y = aLoc[i].Y;
    }
    for(i=28;i<=30;i++)
    {
        aLoc[i].X = aLoc[i-1].X+12;
        aLoc[i].Y = aLoc[i-1].Y;
    }
    str_len = strlen(pString[n-1]);
    aLoc[n-1].X = (rcPop.Right+rcPop.Left)/2-1;
    aLoc[n-1].Y = aLoc[n-2].Y + 4;

    labels.pLoc = aLoc;

    areas.num = 23;
    SMALL_RECT aArea[] = { {aLoc[1].X, aLoc[1].Y,aLoc[1].X + 12, aLoc[1].Y},
						   {aLoc[3].X, aLoc[3].Y,aLoc[3].X + 10, aLoc[3].Y},
						   {aLoc[5].X, aLoc[5].Y,aLoc[5].X + 8, aLoc[5].Y},
						   {aLoc[7].X, aLoc[7].Y,aLoc[7].X + 15, aLoc[7].Y},
                           {aLoc[9].X, aLoc[9].Y,aLoc[9].X + 6, aLoc[9].Y},
                           {aLoc[10].X, aLoc[10].Y,aLoc[10].X + 6, aLoc[10].Y},
                           {aLoc[11].X, aLoc[11].Y,aLoc[11].X + 6, aLoc[11].Y},
                           {aLoc[12].X, aLoc[12].Y,aLoc[12].X + 6, aLoc[12].Y},
                           {aLoc[13].X, aLoc[13].Y,aLoc[13].X + 6, aLoc[13].Y},
                           {aLoc[14].X, aLoc[14].Y,aLoc[14].X + 6, aLoc[14].Y},
                           {aLoc[15].X, aLoc[15].Y,aLoc[15].X + 6, aLoc[15].Y},
                           {aLoc[16].X, aLoc[16].Y,aLoc[16].X + 12, aLoc[16].Y},
                           {aLoc[18].X, aLoc[18].Y,aLoc[18].X + 4, aLoc[18].Y},
                           {aLoc[19].X, aLoc[19].Y,aLoc[19].X + 4, aLoc[19].Y},
                           {aLoc[20].X, aLoc[20].Y,aLoc[20].X + 8, aLoc[20].Y},
                           {aLoc[21].X, aLoc[21].Y,aLoc[21].X + 4, aLoc[21].Y},
                           {aLoc[22].X, aLoc[22].Y,aLoc[22].X + 8, aLoc[22].Y},
                           {aLoc[23].X, aLoc[23].Y,aLoc[23].X + 4, aLoc[23].Y},
                           {aLoc[25].X, aLoc[25].Y,aLoc[25].X + 10, aLoc[25].Y},
                           {aLoc[28].X, aLoc[28].Y,aLoc[28].X + 3, aLoc[28].Y},
                           {aLoc[29].X, aLoc[29].Y,aLoc[29].X + 8, aLoc[29].Y},
                           {aLoc[30].X, aLoc[30].Y,aLoc[30].X + 4, aLoc[30].Y},
                           {aLoc[31].X, aLoc[31].Y,aLoc[31].X + 4, aLoc[31].Y}
                         };

    char aSort[] = {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0};
    char aTag[23];
    int k;
    for(k=0;k<23;k++)
        aTag[k]=k+1;

    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = aLoc[n-1].Y-1;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);

    HOT_AREA *pHotArea=&areas;
    int *piHot=&iHot;
    INPUT_RECORD inRec;
    DWORD res;
    pos.X=0;
    pos.Y=0;
    int num, arrow;
    //int iRet = 0;
    int cNo, cTag, cSort;/*cNo:层号, cTag:热区编号, cSort: 热区类型*/
    char vkc, asc;       /*vkc:虚拟键代码, asc:字符的ASCII码值*/
    COORD record1={0,0};//用于记录单选项加星号的位置
    int flag1=0;//用于判断是否已经做过选择了
    COORD record2={0,0};
    int flag2=0;
    COORD record3={0,0};
    int flag3=0;
    char *input[8];
    char level,charge,judge;
    input[4]=&level;
    input[5]=&charge;
    input[7]=&judge;

    SetHotPoint(pHotArea, *piHot);
    while (TRUE)
    {    /*循环*/
        ReadConsoleInput(gh_std_in, &inRec, 1, &res);
        if ((inRec.EventType == MOUSE_EVENT) &&(inRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED))
        {
            pos = inRec.Event.MouseEvent.dwMousePosition;
            cNo = gp_scr_att[pos.Y * SCR_COL + pos.X] & 3;
            cTag = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 2) & 15;
            cSort = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 6) & 3;

            if ((cNo == gp_top_layer->LayerNo) && cTag > 0)
            {
                *piHot = cTag;
                SetHotPoint(pHotArea, *piHot);
                if (cSort == 0)
                {
                    //iRet = 13;
                    break;
                }
            }
        }
        else if (inRec.EventType == KEY_EVENT && inRec.Event.KeyEvent.bKeyDown)
        {
            vkc = inRec.Event.KeyEvent.wVirtualKeyCode;
            asc = inRec.Event.KeyEvent.uChar.AsciiChar;
            if (asc == 0)
            {
                arrow = 0;
                switch (vkc)
                {  /*方向键(左、上、右、下)的处理*/
                    case 37: arrow = 1; break;
                    case 38: arrow = 2; break;
                    case 39: arrow = 3; break;
                    case 40: arrow = 4; break;
                }
                if (arrow > 0)
                {
                    num = *piHot;
                    while (TRUE)
                    {
                        if (arrow < 3)
                        {
                            num--;
                        }
                        else
                        {
                            num++;
                        }
                        if ((num < 1) || (num > pHotArea->num) ||
                            ((arrow % 2) && (pHotArea->pArea[num-1].Top
                            == pHotArea->pArea[*piHot-1].Top)) || ((!(arrow % 2))
                            && (pHotArea->pArea[num-1].Top
                            != pHotArea->pArea[*piHot-1].Top)))
                        {
                            break;
                        }
                    }
                    if (num > 0 && num <= pHotArea->num)
                    {
                        *piHot = num;
                        SetHotPoint(pHotArea, *piHot);
                    }
                }
            }
            else if (vkc == 27)
            {  /*ESC键*/
                //iRet = 27;
                break;
            }
            else if(vkc==13&&(*piHot>=5&&*piHot<=12))//4 行政级别
            {
                if(flag1)//如果此次操作前已经选择过
                {
                    FillConsoleOutputCharacter(gh_std_out,' ',1,record1,&ul);//将上次加星号的位置置空格
                }
                COORD pos1={pHotArea->pArea[*piHot-1].Left-1,pHotArea->pArea[*piHot-1].Top};//此次需要加星号的位置，当前热区的左边
                FillConsoleOutputCharacter(gh_std_out,'*',1,pos1,&ul);//加星号
                record1=pos1;//记录当前星号位置
                flag1=1;//判断标志置为已做过选择
                level=*piHot-5+'A';//存储当前选择对应的级别

                num=13;
                if (num > 0 && num <= pHotArea->num)
                {
                    *piHot = num;
                    SetHotPoint(pHotArea, *piHot);
                }
            }
            else if(vkc==13&&(*piHot>=13&&*piHot<=18))//5 主要罪名
            {
                if(flag2)
                {
                    FillConsoleOutputCharacter(gh_std_out,' ',1,record2,&ul);
                }
                COORD pos2={pHotArea->pArea[*piHot-1].Left-1,pHotArea->pArea[*piHot-1].Top};
                FillConsoleOutputCharacter(gh_std_out,'*',1,pos2,&ul);
                record2=pos2;
                flag2=1;
                charge=*piHot-13+'1';

                num=19;
                if (num > 0 && num <= pHotArea->num)
                {
                    *piHot = num;
                    SetHotPoint(pHotArea, *piHot);
                }
            }
            else if(vkc==13&&(*piHot>=20&&*piHot<=22))//7 刑事处罚
            {
                if(*piHot==20)//如果当前热区是文本框
                {
                    if(flag3)//且之前做过选择
                    {
                        FillConsoleOutputCharacter(gh_std_out,' ',1,record3,&ul);//将之前的选择置空
                        flag3=0;//置空标志
                    }
                }
                else if(vkc==13&&(*piHot>=21&&*piHot<=22))//如果是选项
                {
                    FillConsoleOutputCharacter(gh_std_out,' ',4,aLoc[28],&ul);//清除文本框原有内容
                    if(flag3)
                    {
                        FillConsoleOutputCharacter(gh_std_out,' ',1,record3,&ul);//将之前的选择置空
                    }
                    COORD pos3={pHotArea->pArea[*piHot-1].Left-1,pHotArea->pArea[*piHot-1].Top};
                    FillConsoleOutputCharacter(gh_std_out,'*',1,pos3,&ul);
                    record3=pos3;
                    flag3=1;
                    if(*piHot==21)
                        judge=100;
                    else if(*piHot==22)
                        judge=-1;
                }
                num=23;
                if (num > 0 && num <= pHotArea->num)
                {
                    *piHot = num;
                    SetHotPoint(pHotArea, *piHot);
                }
            }
            else if ((vkc == 13 || vkc == 32)&&*piHot==23)
            {  /*回车键或空格表示按下确定*/
                //iRet = 13;

                if(!flag3)
                {
                    char temp[3];
                    ReadConsoleOutputCharacter(gh_std_out,temp,3,aLoc[28],&ul);
                    DealString(temp);
                    judge=atoi(temp);
                }

                char id[13],date[11],prov[9],name[16],money[11];
                input[0]=id;
                input[1]=date;
                input[2]=prov;
                input[3]=name;
                input[6]=money;
                ReadConsoleOutputCharacter(gh_std_out,id,13,aLoc[1],&ul);
                ReadConsoleOutputCharacter(gh_std_out,date,11,aLoc[3],&ul);
                ReadConsoleOutputCharacter(gh_std_out,prov,9,aLoc[5],&ul);
                ReadConsoleOutputCharacter(gh_std_out,name,16,aLoc[7],&ul);
                ReadConsoleOutputCharacter(gh_std_out,money,11,aLoc[25],&ul);
                DealString(id);
                DealString(date);
                DealString(prov);
                DealString(name);
                DealString(money);
                PopOff();
                if(input[0][0]=='\0'||input[1][0]=='\0'||input[2][0]=='\0'||input[3][0]=='\0'||!flag1||!flag2||(input[6][0]=='\0'&&!flag3))
                {
                    char *plabel_name[] = {"输入信息不完整或有误！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else if(TestCase(id))
                {
                    char *plabel_name[] = {"案件信息已存在！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else if(!TestProv(prov))
                {
                    char *plabel_name[] = {"省份信息不存在！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else
                {
                    InputCaseInfo(head,input);
                    char *plabel_name[] = {"录入成功！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 2);
                }
                break;
            }
            else if (vkc == 13&&pHotArea->pSort[*piHot-1]==1)
            {  /*文本框回车键表示到下一热区*/
                num=*piHot;
                num++;

                if (num > 0 && num <= pHotArea->num)
                    {
                        *piHot = num;
                        SetHotPoint(pHotArea, *piHot);
                    }
            }
            else
            {
                CONSOLE_SCREEN_BUFFER_INFO bInfo;
                GetConsoleScreenBufferInfo(gh_std_out,&bInfo);
                if(vkc==8)//退格
                {
                    if(bInfo.dwCursorPosition.X>pHotArea->pArea[*piHot-1].Left)
                    {
                        bInfo.dwCursorPosition.X--;//改变光标位置
                        SetConsoleCursorPosition(gh_std_out, bInfo.dwCursorPosition);//设置光标位置
                        FillConsoleOutputCharacter(gh_std_out,' ',1,bInfo.dwCursorPosition,&ul);//字符置为空格
                    }

                }
                else if(bInfo.dwCursorPosition.X<pHotArea->pArea[*piHot-1].Right)
                {
                    FillConsoleOutputCharacter(gh_std_out,asc,1,bInfo.dwCursorPosition,&ul);//显示字符
                    bInfo.dwCursorPosition.X++;//改变光标位置
                    SetConsoleCursorPosition(gh_std_out, bInfo.dwCursorPosition);
                    //WriteConsole(gh_std_out,stdin,20,&ul,NULL);
                }
            }
        }
    }
    PopOff();
}

/**
 * 函数名称: PanelChangeCaseInfo
 * 函数功能: 显示修改案件信息的窗口，输入案件编号.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void PanelChangeCaseInfo(void)//用于修改案件信息的窗口
{
    //BOOL bRet = TRUE;
    char *plabel_name[] = {"案件编号",
                           "            ",
                           "确认"
                          };
    char **pString=plabel_name;
	int n=3;
	LABEL_BUNDLE labels;
    HOT_AREA areas;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int iHot = 1;
    int i, maxlen, str_len;

    for (i=0,maxlen=0; i<n; i++) {
        str_len = strlen(pString[i]);
        if (maxlen < str_len) {
            maxlen = str_len;
        }
    }

    pos.X = maxlen + 6;
    pos.Y = n + 5;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X - 1;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y - 1;

    att =  BACKGROUND_GREEN ;  /*绿底黑字*/
    labels.num = n;
    labels.ppLabel = pString;
    COORD aLoc[n];

    for (i=0; i<n; i++) {
        aLoc[i].X = rcPop.Left + 3;
        aLoc[i].Y = rcPop.Top + 2 + i;

    }
    str_len = strlen(pString[n-1]);
    aLoc[n-1].X = rcPop.Left + 3 + (maxlen-str_len)/2;
    aLoc[n-1].Y = aLoc[n-1].Y + 2;

    labels.pLoc = aLoc;

    areas.num = 2;
    SMALL_RECT aArea[] = {{aLoc[1].X, aLoc[1].Y,
                           aLoc[1].X + 12, aLoc[1].Y},
						   {aLoc[2].X, aLoc[2].Y,
                           aLoc[2].X + 3, aLoc[2].Y}
                           };

    char aSort[] = {1,0};
    char aTag[] = {1,2};

    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 2 + n;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);

    HOT_AREA *pHotArea=&areas;
    int *piHot=&iHot;
    INPUT_RECORD inRec;
    DWORD res;
    pos.X=0;
    pos.Y=0;
    int num, arrow;
    //int iRet = 0;
    int cNo, cTag, cSort;/*cNo:层号, cTag:热区编号, cSort: 热区类型*/
    char vkc, asc;       /*vkc:虚拟键代码, asc:字符的ASCII码值*/

    SetHotPoint(pHotArea, *piHot);
    while (TRUE)
    {    /*循环*/
        ReadConsoleInput(gh_std_in, &inRec, 1, &res);
        if ((inRec.EventType == MOUSE_EVENT) &&(inRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED))
        {
            pos = inRec.Event.MouseEvent.dwMousePosition;
            cNo = gp_scr_att[pos.Y * SCR_COL + pos.X] & 3;
            cTag = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 2) & 15;
            cSort = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 6) & 3;

            if ((cNo == gp_top_layer->LayerNo) && cTag > 0)
            {
                *piHot = cTag;
                SetHotPoint(pHotArea, *piHot);
                if (cSort == 0)
                {
                    //iRet = 13;
                    break;
                }
            }
        }
        else if (inRec.EventType == KEY_EVENT && inRec.Event.KeyEvent.bKeyDown)
        {
            vkc = inRec.Event.KeyEvent.wVirtualKeyCode;
            asc = inRec.Event.KeyEvent.uChar.AsciiChar;
            if (asc == 0)
            {
                arrow = 0;
                switch (vkc)
                {  /*方向键(左、上、右、下)的处理*/
                    case 37: arrow = 1; break;
                    case 38: arrow = 2; break;
                    case 39: arrow = 3; break;
                    case 40: arrow = 4; break;
                }
                if (arrow > 0)
                {
                    num = *piHot;
                    while (TRUE)
                    {
                        if (arrow < 3)
                        {
                            num--;
                        }
                        else
                        {
                            num++;
                        }
                        if ((num < 1) || (num > pHotArea->num) ||
                            ((arrow % 2) && (pHotArea->pArea[num-1].Top
                            == pHotArea->pArea[*piHot-1].Top)) || ((!(arrow % 2))
                            && (pHotArea->pArea[num-1].Top
                            != pHotArea->pArea[*piHot-1].Top)))
                        {
                            break;
                        }
                    }
                    if (num > 0 && num <= pHotArea->num)
                    {
                        *piHot = num;
                        SetHotPoint(pHotArea, *piHot);
                    }
                }
            }
            else if (vkc == 27)
            {  /*ESC键*/
                //iRet = 27;
                break;
            }
            else if ((vkc == 13 || vkc == 32)&&pHotArea->pSort[*piHot-1]==0)
            {  /*回车键或空格表示按下确定*/
                //iRet = 13;
                char caseid[13],prov[9],date[11],name[16],level,charge,money[20],judge[4];
                char *output[]={prov,caseid,date,name,&level,&charge,money,judge};
                ReadConsoleOutputCharacter(gh_std_out,caseid,13,aLoc[1],&ul);
                DealString(caseid);
                if(!TestCaseForChange(caseid,output))//不存在这个案件
                {
                    PopOff();
                    char *plabel_name[] = {"案件信息不存在！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else//存在这个案件
                {
                    PopOff();
                    PanelChangeCaseInfo1(output);
                }
                break;
            }
            else if (vkc == 13&&pHotArea->pSort[*piHot-1]==1)
            {  /*文本框回车键表示到下一热区*/
                num=*piHot;
                num++;

                if (num > 0 && num <= pHotArea->num)
                    {
                        *piHot = num;
                        SetHotPoint(pHotArea, *piHot);
                    }
            }
            else
            {
                CONSOLE_SCREEN_BUFFER_INFO bInfo;
                GetConsoleScreenBufferInfo(gh_std_out,&bInfo);
                if(vkc==8)//退格
                {
                    if(bInfo.dwCursorPosition.X>pHotArea->pArea[*piHot-1].Left)
                    {
                        bInfo.dwCursorPosition.X--;//改变光标位置
                        SetConsoleCursorPosition(gh_std_out, bInfo.dwCursorPosition);//设置光标位置
                        FillConsoleOutputCharacter(gh_std_out,' ',1,bInfo.dwCursorPosition,&ul);//字符置为空格
                    }

                }
                else if(bInfo.dwCursorPosition.X<pHotArea->pArea[*piHot-1].Right)
                {
                    FillConsoleOutputCharacter(gh_std_out,asc,1,bInfo.dwCursorPosition,&ul);//显示字符
                    bInfo.dwCursorPosition.X++;//改变光标位置
                    SetConsoleCursorPosition(gh_std_out, bInfo.dwCursorPosition);
                }
            }
        }
    }
    //PopOff();
}

/**
 * 函数名称: PanelChangeCaseInfo1
 * 函数功能: 显示用于用户输入案件修改信息的窗口.
 * 输入参数: str 用户输入的按键编号
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void PanelChangeCaseInfo1(char **str)//用于输入修改案件信息的窗口
{
    //BOOL bRet = TRUE;
    char *plabel_name[] = {"案件编号",
                           str[1],//12
                           "立案日期",
						   str[2],//10
						   "所属省份",
						   str[0],//8
                           "被告人姓名",
                           str[3],//15
                           "行政级别",
"副科级","正科级","副处级","正处级","副厅级","正厅级","副部级","正部级及以上",
                           "主要罪名",
"受贿","贪污","挪用公款","渎职","滥用职权","其他",
                           "涉案金额(万)",
                           str[6],//10
                           "刑事处罚",
"有期徒刑(年)",str[7]/*3*/,"无期徒刑","死刑",
                           "确定"
                          };
    char **pString=plabel_name;
	int n=32;
	LABEL_BUNDLE labels;
    HOT_AREA areas;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int iHot = 1;
    int i, maxlen, str_len;

    for (i=0,maxlen=0; i<n; i++) {
        str_len = strlen(pString[i]);
        if (maxlen < str_len) {
            maxlen = str_len;
        }
    }

    pos.X = maxlen*7;
    pos.Y = n - 12;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X ;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y;

    att =  BACKGROUND_GREEN ;  /*绿底黑字*/
    labels.num = n;
    labels.ppLabel = pString;
    COORD aLoc[n];

    for (i=0; i<=8; i+=2) {
        aLoc[i].X = rcPop.Left + 3;
        aLoc[i].Y = rcPop.Top + 1 + i;

        aLoc[i+1].X = aLoc[i].X+10;
        aLoc[i+1].Y = aLoc[i].Y;
    }
    for(i=10;i<=16;i++)
    {
        aLoc[i].X=aLoc[i-1].X+7;
        aLoc[i].Y=aLoc[i-1].Y;
    }
    aLoc[i].X = rcPop.Left + 3;
    aLoc[i].Y = rcPop.Top + 1 + 10;
    for(i=18;i<=23;i++)
    {
        aLoc[i].X = aLoc[i-1].X+10;
        aLoc[i].Y = aLoc[i-1].Y;
    }
    for(i=24;i<=26;i+=2)
    {
        aLoc[i].X = rcPop.Left + 3;
        aLoc[i].Y = rcPop.Top + 1 + 12+i-24;

        aLoc[i+1].X = aLoc[i].X+12;
        aLoc[i+1].Y = aLoc[i].Y;
    }
    for(i=28;i<=30;i++)
    {
        aLoc[i].X = aLoc[i-1].X+12;
        aLoc[i].Y = aLoc[i-1].Y;
    }
    str_len = strlen(pString[n-1]);
    aLoc[n-1].X = (rcPop.Left + rcPop.Right)/2-1 ;//+ (maxlen-str_len)/2;
    aLoc[n-1].Y = aLoc[n-2].Y + 4;

    labels.pLoc = aLoc;

    areas.num = 23;
    SMALL_RECT aArea[] = { {aLoc[1].X, aLoc[1].Y,aLoc[1].X + 12, aLoc[1].Y},
						   {aLoc[3].X, aLoc[3].Y,aLoc[3].X + 10, aLoc[3].Y},
						   {aLoc[5].X, aLoc[5].Y,aLoc[5].X + 8, aLoc[5].Y},
						   {aLoc[7].X, aLoc[7].Y,aLoc[7].X + 15, aLoc[7].Y},
                           {aLoc[9].X, aLoc[9].Y,aLoc[9].X + 6, aLoc[9].Y},
                           {aLoc[10].X, aLoc[10].Y,aLoc[10].X + 6, aLoc[10].Y},
                           {aLoc[11].X, aLoc[11].Y,aLoc[11].X + 6, aLoc[11].Y},
                           {aLoc[12].X, aLoc[12].Y,aLoc[12].X + 6, aLoc[12].Y},
                           {aLoc[13].X, aLoc[13].Y,aLoc[13].X + 6, aLoc[13].Y},
                           {aLoc[14].X, aLoc[14].Y,aLoc[14].X + 6, aLoc[14].Y},
                           {aLoc[15].X, aLoc[15].Y,aLoc[15].X + 6, aLoc[15].Y},
                           {aLoc[16].X, aLoc[16].Y,aLoc[16].X + 12, aLoc[16].Y},
                           {aLoc[18].X, aLoc[18].Y,aLoc[18].X + 4, aLoc[18].Y},
                           {aLoc[19].X, aLoc[19].Y,aLoc[19].X + 4, aLoc[19].Y},
                           {aLoc[20].X, aLoc[20].Y,aLoc[20].X + 8, aLoc[20].Y},
                           {aLoc[21].X, aLoc[21].Y,aLoc[21].X + 4, aLoc[21].Y},
                           {aLoc[22].X, aLoc[22].Y,aLoc[22].X + 8, aLoc[22].Y},
                           {aLoc[23].X, aLoc[23].Y,aLoc[23].X + 4, aLoc[23].Y},
                           {aLoc[25].X, aLoc[25].Y,aLoc[25].X + 10, aLoc[25].Y},
                           {aLoc[28].X, aLoc[28].Y,aLoc[28].X + 3, aLoc[28].Y},
                           {aLoc[29].X, aLoc[29].Y,aLoc[29].X + 8, aLoc[29].Y},
                           {aLoc[30].X, aLoc[30].Y,aLoc[30].X + 4, aLoc[30].Y},
                           {aLoc[31].X, aLoc[31].Y,aLoc[31].X + 4, aLoc[31].Y}
                         };

    char aSort[] = {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0};
    char aTag[23];
    int k;
    for(k=0;k<23;k++)
        aTag[k]=k+1;

    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = aLoc[n-1].Y-1;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);

    HOT_AREA *pHotArea=&areas;
    int *piHot=&iHot;
    INPUT_RECORD inRec;
    DWORD res;
    pos.X=0;
    pos.Y=0;
    int num, arrow;
    //int iRet = 0;
    int cNo, cTag, cSort;/*cNo:层号, cTag:热区编号, cSort: 热区类型*/
    char vkc, asc;       /*vkc:虚拟键代码, asc:字符的ASCII码值*/
    COORD record1={0,0};
    int flag1=1;
    COORD record2={0,0};
    int flag2=1;
    COORD record3={0,0};
    int flag3=0;
    char *input[8];
    char level=*str[4],charge=*str[5],judge=atoi(str[7]);
    input[4]=&level;
    input[5]=&charge;
    input[7]=&judge;
    //显示修改前的信息内容到界面上
    record1=aLoc[9+*str[4]-'A'];
    record1.X--;
    FillConsoleOutputCharacter(gh_std_out, '*', 1, record1 , &ul);//行政级别标记
    record2=aLoc[18+*str[5]-'1'];
    record2.X--;
    FillConsoleOutputCharacter(gh_std_out, '*', 1, record2, &ul);//主要罪名标记
    if(atoi(str[7])<0)//死刑标记
    {
        flag3=1;
        record3=aLoc[30];
        record3.X--;
        FillConsoleOutputCharacter(gh_std_out, '*', 1, record3, &ul);
        FillConsoleOutputCharacter(gh_std_out, ' ', 4, aLoc[28], &ul);
    }
    else if(atoi(str[7])>=100)//无期徒刑标记
    {
        flag3=1;
        record3=aLoc[29];
        record3.X--;
        FillConsoleOutputCharacter(gh_std_out, '*', 1, record3, &ul);
        FillConsoleOutputCharacter(gh_std_out, ' ', 4, aLoc[28], &ul);
    }


    SetHotPoint(pHotArea, *piHot);
    while (TRUE)
    {    /*循环*/
        ReadConsoleInput(gh_std_in, &inRec, 1, &res);
        if ((inRec.EventType == MOUSE_EVENT) &&(inRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED))
        {
            pos = inRec.Event.MouseEvent.dwMousePosition;
            cNo = gp_scr_att[pos.Y * SCR_COL + pos.X] & 3;
            cTag = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 2) & 15;
            cSort = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 6) & 3;

            if ((cNo == gp_top_layer->LayerNo) && cTag > 0)
            {
                *piHot = cTag;
                SetHotPoint(pHotArea, *piHot);
                if (cSort == 0)
                {
                    //iRet = 13;
                    break;
                }
            }
        }
        else if (inRec.EventType == KEY_EVENT && inRec.Event.KeyEvent.bKeyDown)
        {
            vkc = inRec.Event.KeyEvent.wVirtualKeyCode;
            asc = inRec.Event.KeyEvent.uChar.AsciiChar;
            if (asc == 0)
            {
                arrow = 0;
                switch (vkc)
                {  /*方向键(左、上、右、下)的处理*/
                    case 37: arrow = 1; break;
                    case 38: arrow = 2; break;
                    case 39: arrow = 3; break;
                    case 40: arrow = 4; break;
                }
                if (arrow > 0)
                {
                    num = *piHot;
                    while (TRUE)
                    {
                        if (arrow < 3)
                        {
                            num--;
                        }
                        else
                        {
                            num++;
                        }
                        if ((num < 1) || (num > pHotArea->num) ||
                            ((arrow % 2) && (pHotArea->pArea[num-1].Top
                            == pHotArea->pArea[*piHot-1].Top)) || ((!(arrow % 2))
                            && (pHotArea->pArea[num-1].Top
                            != pHotArea->pArea[*piHot-1].Top)))
                        {
                            break;
                        }
                    }
                    if (num > 0 && num <= pHotArea->num)
                    {
                        *piHot = num;
                        SetHotPoint(pHotArea, *piHot);
                    }
                }
            }
            else if (vkc == 27)
            {  /*ESC键*/
                //iRet = 27;
                break;
            }
            else if(vkc==13&&(*piHot>=5&&*piHot<=12))//4
            {
                if(flag1)
                {
                    FillConsoleOutputCharacter(gh_std_out,' ',1,record1,&ul);
                }
                COORD pos1={pHotArea->pArea[*piHot-1].Left-1,pHotArea->pArea[*piHot-1].Top};
                FillConsoleOutputCharacter(gh_std_out,'*',1,pos1,&ul);
                record1=pos1;
                flag1=1;
                level=*piHot-5+'A';

                num=13;
                if (num > 0 && num <= pHotArea->num)
                {
                    *piHot = num;
                    SetHotPoint(pHotArea, *piHot);
                }
            }
            else if(vkc==13&&(*piHot>=13&&*piHot<=18))//5
            {
                if(flag2)
                {
                    FillConsoleOutputCharacter(gh_std_out,' ',1,record2,&ul);
                }
                COORD pos2={pHotArea->pArea[*piHot-1].Left-1,pHotArea->pArea[*piHot-1].Top};
                FillConsoleOutputCharacter(gh_std_out,'*',1,pos2,&ul);
                record2=pos2;
                flag2=1;
                charge=*piHot-13+'1';

                num=19;
                if (num > 0 && num <= pHotArea->num)
                {
                    *piHot = num;
                    SetHotPoint(pHotArea, *piHot);
                }
            }
            else if(vkc==13&&(*piHot>=20&&*piHot<=22))//7 刑事处罚
            {
                if(*piHot==20)
                {
                    if(flag3)
                    {
                        FillConsoleOutputCharacter(gh_std_out,' ',1,record3,&ul);
                        judge=0;
                        flag3=0;
                    }
                }
                else if(vkc==13&&(*piHot>=21&&*piHot<=22))
                {
                    FillConsoleOutputCharacter(gh_std_out,' ',4,aLoc[28],&ul);//清除文本框原有内容
                    if(flag3)
                    {
                        FillConsoleOutputCharacter(gh_std_out,' ',1,record3,&ul);
                    }
                    COORD pos3={pHotArea->pArea[*piHot-1].Left-1,pHotArea->pArea[*piHot-1].Top};
                    FillConsoleOutputCharacter(gh_std_out,'*',1,pos3,&ul);
                    record3=pos3;
                    flag3=1;
                    if(*piHot==21)
                        judge=100;
                    else if(*piHot==22)
                        judge=-1;
                }
                num=23;
                if (num > 0 && num <= pHotArea->num)
                {
                    *piHot = num;
                    SetHotPoint(pHotArea, *piHot);
                }
            }
            else if ((vkc == 13 || vkc == 32)&&*piHot==23)
            {  /*回车键或空格表示按下确定*/
                //iRet = 13;

                if(!flag3)
                {
                    char temp[4];
                    ReadConsoleOutputCharacter(gh_std_out,temp,4,aLoc[28],&ul);
                    DealString(temp);
                    judge=atoi(temp);
                }

                char id[13],date[11],prov[9],name[16],money[11];
                input[0]=id;
                input[1]=date;
                input[2]=prov;
                input[3]=name;
                input[6]=money;
                ReadConsoleOutputCharacter(gh_std_out,id,13,aLoc[1],&ul);
                ReadConsoleOutputCharacter(gh_std_out,date,11,aLoc[3],&ul);
                ReadConsoleOutputCharacter(gh_std_out,prov,9,aLoc[5],&ul);
                ReadConsoleOutputCharacter(gh_std_out,name,16,aLoc[7],&ul);
                ReadConsoleOutputCharacter(gh_std_out,money,11,aLoc[25],&ul);
                DealString(id);
                DealString(date);
                DealString(prov);
                DealString(name);
                DealString(money);
                PopOff();
                if(id[0]=='\0'||prov[0]=='\0'||date[0]=='\0'||name[0]=='\0'||money[0]=='\0'||level==0||charge==0||judge==0)
                {
                    char *plabel_name[] = {"信息不完整或有误！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 2);
                    break;
                }
                else if(!TestProv(prov))
                {
                    char *plabel_name[] = {"省份信息不存在！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 2);
                    break;
                }
                else if(ChangeCaseInfo(head,str[1],input)==1)
                {
                    char *plabel_name[] = {"修改成功！",
                                           "原案件信息下的媒体信息将丢失！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 3);
                }
                else
                {
                    char *plabel_name[] = {"修改成功！",
                                            "确定"
                                            };
                    ShowModule(plabel_name, 2);
                }
                break;
            }
            else if (vkc == 13&&pHotArea->pSort[*piHot-1]==1)
            {  /*文本框回车键表示到下一热区*/
                num=*piHot;
                num++;

                if (num > 0 && num <= pHotArea->num)
                    {
                        *piHot = num;
                        SetHotPoint(pHotArea, *piHot);
                    }
            }
            else
            {
                CONSOLE_SCREEN_BUFFER_INFO bInfo;
                GetConsoleScreenBufferInfo(gh_std_out,&bInfo);
                if(vkc==8)//退格
                {
                    if(bInfo.dwCursorPosition.X>pHotArea->pArea[*piHot-1].Left)
                    {
                        bInfo.dwCursorPosition.X--;//改变光标位置
                        SetConsoleCursorPosition(gh_std_out, bInfo.dwCursorPosition);//设置光标位置
                        FillConsoleOutputCharacter(gh_std_out,' ',1,bInfo.dwCursorPosition,&ul);//字符置为空格
                    }

                }
                else if(bInfo.dwCursorPosition.X<pHotArea->pArea[*piHot-1].Right)
                {
                    FillConsoleOutputCharacter(gh_std_out,asc,1,bInfo.dwCursorPosition,&ul);//显示字符
                    bInfo.dwCursorPosition.X++;//改变光标位置
                    SetConsoleCursorPosition(gh_std_out, bInfo.dwCursorPosition);
                    //WriteConsole(gh_std_out,stdin,20,&ul,NULL);
                }
            }
        }
    }
    PopOff();
}

/**
 * 函数名称: PanelDeleteCaseInfo
 * 函数功能: 显示删除案件信息的窗口.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void PanelDeleteCaseInfo(void)//用于删除案件信息的窗口
{
    //BOOL bRet = TRUE;
    char *plabel_name[] = {"案件编号",
                           "            ",//12
                           "确认"
                          };
    char **pString=plabel_name;
	int n=3;
	LABEL_BUNDLE labels;
    HOT_AREA areas;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int iHot = 1;
    int i, maxlen, str_len;

    for (i=0,maxlen=0; i<n; i++) {
        str_len = strlen(pString[i]);
        if (maxlen < str_len) {
            maxlen = str_len;
        }
    }

    pos.X = maxlen + 6;
    pos.Y = n + 5;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X - 1;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y - 1;

    att =  BACKGROUND_GREEN ;  /*绿底黑字*/
    labels.num = n;
    labels.ppLabel = pString;
    COORD aLoc[n];

    for (i=0; i<n; i++) {
        aLoc[i].X = rcPop.Left + 3;
        aLoc[i].Y = rcPop.Top + 2 + i;

    }
    str_len = strlen(pString[n-1]);
    aLoc[n-1].X = rcPop.Left + 3 + (maxlen-str_len)/2;
    aLoc[n-1].Y = aLoc[n-1].Y + 2;

    labels.pLoc = aLoc;

    areas.num = 2;
    SMALL_RECT aArea[] = {{aLoc[1].X, aLoc[1].Y,
                           aLoc[1].X + 12, aLoc[1].Y},
						   {aLoc[2].X, aLoc[2].Y,
                           aLoc[2].X + 3, aLoc[2].Y}
                           };

    char aSort[] = {1,0};
    char aTag[] = {1,2};

    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 2 + n;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);

    HOT_AREA *pHotArea=&areas;
    int *piHot=&iHot;
    INPUT_RECORD inRec;
    DWORD res;
    pos.X=0;
    pos.Y=0;
    int num, arrow;
    //int iRet = 0;
    int cNo, cTag, cSort;/*cNo:层号, cTag:热区编号, cSort: 热区类型*/
    char vkc, asc;       /*vkc:虚拟键代码, asc:字符的ASCII码值*/

    SetHotPoint(pHotArea, *piHot);
    while (TRUE)
    {    /*循环*/
        ReadConsoleInput(gh_std_in, &inRec, 1, &res);
        if ((inRec.EventType == MOUSE_EVENT) &&(inRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED))
        {
            pos = inRec.Event.MouseEvent.dwMousePosition;
            cNo = gp_scr_att[pos.Y * SCR_COL + pos.X] & 3;
            cTag = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 2) & 15;
            cSort = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 6) & 3;

            if ((cNo == gp_top_layer->LayerNo) && cTag > 0)
            {
                *piHot = cTag;
                SetHotPoint(pHotArea, *piHot);
                if (cSort == 0)
                {
                    //iRet = 13;
                    break;
                }
            }
        }
        else if (inRec.EventType == KEY_EVENT && inRec.Event.KeyEvent.bKeyDown)
        {
            vkc = inRec.Event.KeyEvent.wVirtualKeyCode;
            asc = inRec.Event.KeyEvent.uChar.AsciiChar;
            if (asc == 0)
            {
                arrow = 0;
                switch (vkc)
                {  /*方向键(左、上、右、下)的处理*/
                    case 37: arrow = 1; break;
                    case 38: arrow = 2; break;
                    case 39: arrow = 3; break;
                    case 40: arrow = 4; break;
                }
                if (arrow > 0)
                {
                    num = *piHot;
                    while (TRUE)
                    {
                        if (arrow < 3)
                        {
                            num--;
                        }
                        else
                        {
                            num++;
                        }
                        if ((num < 1) || (num > pHotArea->num) ||
                            ((arrow % 2) && (pHotArea->pArea[num-1].Top
                            == pHotArea->pArea[*piHot-1].Top)) || ((!(arrow % 2))
                            && (pHotArea->pArea[num-1].Top
                            != pHotArea->pArea[*piHot-1].Top)))
                        {
                            break;
                        }
                    }
                    if (num > 0 && num <= pHotArea->num)
                    {
                        *piHot = num;
                        SetHotPoint(pHotArea, *piHot);
                    }
                }
            }
            else if (vkc == 27)
            {  /*ESC键*/
                //iRet = 27;
                break;
            }
            else if ((vkc == 13 || vkc == 32)&&pHotArea->pSort[*piHot-1]==0)
            {  /*回车键或空格表示按下确定*/
                //iRet = 13;
                char id[13];
                ReadConsoleOutputCharacter(gh_std_out,id,13,aLoc[1],&ul);
                DealString(id);
                PopOff();
                if(!TestCase(id))
                {
                    char *plabel_name[] = {"案件信息不存在！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else
                {
                    DeleteCaseInfo(head,id);
                    char *plabel_name[] = {"删除成功！",
                                           "原案件信息下媒体信息将丢失！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 3);
                }
                break;
            }
            else if (vkc == 13&&pHotArea->pSort[*piHot-1]==1)
            {  /*文本框回车键表示到下一热区*/
                num=*piHot;
                num++;

                if (num > 0 && num <= pHotArea->num)
                    {
                        *piHot = num;
                        SetHotPoint(pHotArea, *piHot);
                    }
            }
            else
            {
                CONSOLE_SCREEN_BUFFER_INFO bInfo;
                GetConsoleScreenBufferInfo(gh_std_out,&bInfo);
                if(vkc==8)//退格
                {
                    if(bInfo.dwCursorPosition.X>pHotArea->pArea[*piHot-1].Left)
                    {
                        bInfo.dwCursorPosition.X--;//改变光标位置
                        SetConsoleCursorPosition(gh_std_out, bInfo.dwCursorPosition);//设置光标位置
                        FillConsoleOutputCharacter(gh_std_out,' ',1,bInfo.dwCursorPosition,&ul);//字符置为空格
                    }

                }
                else if(bInfo.dwCursorPosition.X<pHotArea->pArea[*piHot-1].Right)
                {
                    FillConsoleOutputCharacter(gh_std_out,asc,1,bInfo.dwCursorPosition,&ul);//显示字符
                    bInfo.dwCursorPosition.X++;//改变光标位置
                    SetConsoleCursorPosition(gh_std_out, bInfo.dwCursorPosition);
                }
            }
        }
    }
    //PopOff();
}
