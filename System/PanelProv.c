#include"head.h"
/**
 * 函数名称: PanelInputProvInfo
 * 函数功能: 显示录入省份信息的窗口.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void PanelInputProvInfo(void)//用于录入省份信息的窗口
{
    char *plabel_name[] = {"省份名称",       //供用户输入信息的窗口上的标签
                           "         ",
                           "负责人姓名",
						   "               ",
						   "联系电话",
						   "               ",
                           "确认"
                          };
    char **pString=plabel_name;
	int n=7;//7个标签
	LABEL_BUNDLE labels;
    HOT_AREA areas;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int iHot = 1;
    int i, maxlen, str_len;

    for (i=0,maxlen=0; i<n; i++) {//获取最长标签长度用于设置窗体大小
        str_len = strlen(pString[i]);
        if (maxlen < str_len) {
            maxlen = str_len;
        }
    }
    //设置窗口位置与大小
    pos.X = maxlen + 6;
    pos.Y = n + 5;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X - 1;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y - 1;

    att =  BACKGROUND_GREEN ;  //绿底黑字
    labels.num = n;
    labels.ppLabel = pString;
    COORD aLoc[n];//所有标签的位置

    for (i=0; i<n; i++) {
        aLoc[i].X = rcPop.Left + 3;
        aLoc[i].Y = rcPop.Top + 2 + i;

    }
    str_len = strlen(pString[n-1]);//最后一个确定的位置
    aLoc[n-1].X = rcPop.Left + 3 + (maxlen-str_len)/2;
    aLoc[n-1].Y = aLoc[n-1].Y + 2;

    labels.pLoc = aLoc;

    areas.num = 4;//热区数
    //设置热区位置与热区四个顶点的位置
    SMALL_RECT aArea[] = {{aLoc[1].X, aLoc[1].Y,
                           aLoc[1].X + 9, aLoc[1].Y},
						   {aLoc[3].X, aLoc[3].Y,
                           aLoc[3].X + 15, aLoc[3].Y},
						   {aLoc[5].X, aLoc[5].Y,
                           aLoc[5].X + 15, aLoc[5].Y},
						   {aLoc[6].X, aLoc[6].Y,
                           aLoc[6].X + 3, aLoc[6].Y}
                           };

    char aSort[] = {1,1,1,0};//热区类型 1为文本框 0为按钮
    char aTag[] = {1,2,3,4};//热区编号

    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);//显示窗口

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 2 + n;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);//用横线把确定和其他项隔开

    HOT_AREA *pHotArea=&areas;
    int *piHot=&iHot;//用于指示当前被激活热区
    INPUT_RECORD inRec;
    DWORD res;
    pos.X=0;
    pos.Y=0;
    int num, arrow;
    int cNo, cTag, cSort;//cNo:层号, cTag:热区编号, cSort: 热区类型
    char vkc, asc;       //vkc:虚拟键代码, asc:字符的ASCII码值

    SetHotPoint(pHotArea, *piHot);
    while (TRUE)
    {    //循环，每次从键盘获取一个按键
        ReadConsoleInput(gh_std_in, &inRec, 1, &res);
        if ((inRec.EventType == MOUSE_EVENT) &&(inRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED))
        {//如果是鼠标事件
            pos = inRec.Event.MouseEvent.dwMousePosition;
            cNo = gp_scr_att[pos.Y * SCR_COL + pos.X] & 3;
            cTag = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 2) & 15;
            cSort = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 6) & 3;

            if ((cNo == gp_top_layer->LayerNo) && cTag > 0)
            {
                *piHot = cTag;
                SetHotPoint(pHotArea, *piHot);
                if (cSort == 0)
                {//点击按钮表示按下确定，结束
                    break;
                }
            }
        }
        else if (inRec.EventType == KEY_EVENT && inRec.Event.KeyEvent.bKeyDown)
        {//如果是键盘事件
            vkc = inRec.Event.KeyEvent.wVirtualKeyCode;
            asc = inRec.Event.KeyEvent.uChar.AsciiChar;
            if (asc == 0)
            {
                arrow = 0;
                switch (vkc)
                {  //方向键(左、上、右、下)的处理
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
                        *piHot = num;//根据方向键转向其他热区
                        SetHotPoint(pHotArea, *piHot);
                    }
                }
            }
            else if (vkc == 27)
            {  //ESC键，结束
                break;
            }
            else if ((vkc == 13 || vkc == 32)&&pHotArea->pSort[*piHot-1]==0)
            {  //回车键或空格表示按下确定
                char *input[3],prov[9],leader[16],tel[16];
                input[0]=prov;
                input[1]=leader;
                input[2]=tel;
                //从文本框获取用户输入
                ReadConsoleOutputCharacter(gh_std_out,prov,9,aLoc[1],&ul);
                ReadConsoleOutputCharacter(gh_std_out,leader,16,aLoc[3],&ul);
                ReadConsoleOutputCharacter(gh_std_out,tel,16,aLoc[5],&ul);
                //处理字符串，加\0
                DealString(prov);
                DealString(leader);
                DealString(tel);
                PopOff();
                if(input[0][0]=='\0'||input[1][0]=='\0'||input[2][0]=='\0')//如果用户输入不全留空或输入前有空格导致格式错误
                {
                    char *plabel_name[] = {"输入信息不完整或有误！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else if(TestProv(prov))//测重
                {
                    char *plabel_name[] = {"省份信息已存在！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else
                {
                    InputProvInfo(head,input);
                    char *plabel_name[] = {"录入成功！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 2);
                }
                break;
            }
            else if (vkc == 13&&pHotArea->pSort[*piHot-1]==1)
            {  //文本框回车键表示到下一热区
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
}
/**
 * 函数名称: PanelChangeProvInfo
 * 函数功能: 显示修改省份信息的窗口，输入省份名称.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void PanelChangeProvInfo(void)//用于修改省份信息的窗口
{
    char *plabel_name[] = {"省份名称",
                           "        ",
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
                           aLoc[1].X + 8, aLoc[1].Y},
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
    int num, arrow; //iRet = 0;
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
                char prov[9],leader[16],tel[16];
                char *output[3]={prov,leader,tel};
                ReadConsoleOutputCharacter(gh_std_out,prov,9,aLoc[1],&ul);
                DealString(prov);
                if(!TestProvForChange(prov,output))//不存在这个省份
                {
                    PopOff();
                    char *plabel_name[] = {"省份信息不存在！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else//存在这个省份
                {
                    PopOff();
                    PanelChangeProvInfo1(output);
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
    //PopOff();
}

/**
 * 函数名称: PanelChangeProvInfo1
 * 函数功能: 显示供用户输入省份修改信息的窗口.
 * 输入参数: match 用户输入的省份名称
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void PanelChangeProvInfo1(char **match)//用于修改省份信息中输入信息的窗口
{
    //BOOL bRet = TRUE;
    char *plabel_name[] = {"省份名称",
                           match[0],//8
                           "负责人姓名",
						   match[1],//15
						   "联系电话",
						   match[2],//15
                           "确认"
                          };
    char **pString=plabel_name;
	int n=7;
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
    maxlen+=6;
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

    areas.num = 4;
    SMALL_RECT aArea[] = {{aLoc[1].X, aLoc[1].Y,
                           aLoc[1].X + 8, aLoc[1].Y},
						   {aLoc[3].X, aLoc[3].Y,
                           aLoc[3].X + 15, aLoc[3].Y},
						   {aLoc[5].X, aLoc[5].Y,
                           aLoc[5].X + 15, aLoc[5].Y},
						   {aLoc[6].X, aLoc[6].Y,
                           aLoc[6].X + 3, aLoc[6].Y}
                           };

    char aSort[] = {1,1,1,0};
    char aTag[] = {1,2,3,4};

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
    int num, arrow;// iRet = 0;
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
                char *input[3],prov[9],leader[16],tel[16];
                input[0]=prov;
                input[1]=leader;
                input[2]=tel;
                ReadConsoleOutputCharacter(gh_std_out,prov,9,aLoc[1],&ul);
                ReadConsoleOutputCharacter(gh_std_out,leader,16,aLoc[3],&ul);
                ReadConsoleOutputCharacter(gh_std_out,tel,16,aLoc[5],&ul);
                DealString(prov);
                DealString(leader);
                DealString(tel);
                PopOff();
                if(prov[0]=='\0'||leader[0]=='\0'||tel[0]=='\0')
                {
                    char *plabel_name[] = {"信息不完整或有误!",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else if(ChangeProvInfo(head,match[0],input)==1)
                {
                    char *plabel_name[] = {"修改成功!",
                                           "原省份下案件及媒体信息将丢失！",
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
    //PopOff();
}

/**
 * 函数名称: PanelDeleteProvInfo
 * 函数功能: 显示删除省份信息的窗口.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void PanelDeleteProvInfo(void)//用于删除省份信息的窗口
{
    //BOOL bRet = TRUE;
    char *plabel_name[] = {"省份名称",
                           "        ",
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
                           aLoc[1].X + 8, aLoc[1].Y},
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
    int num, arrow; //iRet = 0;
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
                char prov[9];
                ReadConsoleOutputCharacter(gh_std_out,prov,8,aLoc[1],&ul);
                DealString(prov);
                PopOff();
                if(!TestProv(prov))
                {
                    char *plabel_name[] = {"省份信息不存在！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else
                {
                    DeleteProvInfo(head,prov);
                    char *plabel_name[] = {"删除成功！",
                                           "原省份下案件及媒体信息将丢失！",
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
