#include"head.h"
/**
 * ��������: PanelInputCaseInfo
 * ��������: ��ʾ¼�밸����Ϣ�Ĵ���.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void PanelInputCaseInfo(void)//����¼�밸����Ϣ�Ĵ���
{
    char *plabel_name[] = {"�������",
                           "            ",//12
                           "��������",
						   "          ",//10
						   "����ʡ��",
						   "        ",//8
                           "����������",
                           "               ",//15
                           "��������",
"���Ƽ�","���Ƽ�","������","������","������","������","������","������������",
                           "��Ҫ����",
"�ܻ�","̰��","Ų�ù���","��ְ","����ְȨ","����",
                           "�永���(��)",
                           "          ",//10
                           "���´���",
"����ͽ��(��)","   "/*3*/,"����ͽ��","����",
                           "ȷ��"
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

    att =  BACKGROUND_GREEN ;  /*�̵׺���*/
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
    int cNo, cTag, cSort;/*cNo:���, cTag:�������, cSort: ��������*/
    char vkc, asc;       /*vkc:���������, asc:�ַ���ASCII��ֵ*/
    COORD record1={0,0};//���ڼ�¼��ѡ����Ǻŵ�λ��
    int flag1=0;//�����ж��Ƿ��Ѿ�����ѡ����
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
    {    /*ѭ��*/
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
                {  /*�����(���ϡ��ҡ���)�Ĵ���*/
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
            {  /*ESC��*/
                //iRet = 27;
                break;
            }
            else if(vkc==13&&(*piHot>=5&&*piHot<=12))//4 ��������
            {
                if(flag1)//����˴β���ǰ�Ѿ�ѡ���
                {
                    FillConsoleOutputCharacter(gh_std_out,' ',1,record1,&ul);//���ϴμ��Ǻŵ�λ���ÿո�
                }
                COORD pos1={pHotArea->pArea[*piHot-1].Left-1,pHotArea->pArea[*piHot-1].Top};//�˴���Ҫ���Ǻŵ�λ�ã���ǰ���������
                FillConsoleOutputCharacter(gh_std_out,'*',1,pos1,&ul);//���Ǻ�
                record1=pos1;//��¼��ǰ�Ǻ�λ��
                flag1=1;//�жϱ�־��Ϊ������ѡ��
                level=*piHot-5+'A';//�洢��ǰѡ���Ӧ�ļ���

                num=13;
                if (num > 0 && num <= pHotArea->num)
                {
                    *piHot = num;
                    SetHotPoint(pHotArea, *piHot);
                }
            }
            else if(vkc==13&&(*piHot>=13&&*piHot<=18))//5 ��Ҫ����
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
            else if(vkc==13&&(*piHot>=20&&*piHot<=22))//7 ���´���
            {
                if(*piHot==20)//�����ǰ�������ı���
                {
                    if(flag3)//��֮ǰ����ѡ��
                    {
                        FillConsoleOutputCharacter(gh_std_out,' ',1,record3,&ul);//��֮ǰ��ѡ���ÿ�
                        flag3=0;//�ÿձ�־
                    }
                }
                else if(vkc==13&&(*piHot>=21&&*piHot<=22))//�����ѡ��
                {
                    FillConsoleOutputCharacter(gh_std_out,' ',4,aLoc[28],&ul);//����ı���ԭ������
                    if(flag3)
                    {
                        FillConsoleOutputCharacter(gh_std_out,' ',1,record3,&ul);//��֮ǰ��ѡ���ÿ�
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
            {  /*�س�����ո��ʾ����ȷ��*/
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
                    char *plabel_name[] = {"������Ϣ������������",
                                           "ȷ��"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else if(TestCase(id))
                {
                    char *plabel_name[] = {"������Ϣ�Ѵ��ڣ�",
                                           "ȷ��"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else if(!TestProv(prov))
                {
                    char *plabel_name[] = {"ʡ����Ϣ�����ڣ�",
                                           "ȷ��"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else
                {
                    InputCaseInfo(head,input);
                    char *plabel_name[] = {"¼��ɹ���",
                                           "ȷ��"
                                          };
                    ShowModule(plabel_name, 2);
                }
                break;
            }
            else if (vkc == 13&&pHotArea->pSort[*piHot-1]==1)
            {  /*�ı���س�����ʾ����һ����*/
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
                if(vkc==8)//�˸�
                {
                    if(bInfo.dwCursorPosition.X>pHotArea->pArea[*piHot-1].Left)
                    {
                        bInfo.dwCursorPosition.X--;//�ı���λ��
                        SetConsoleCursorPosition(gh_std_out, bInfo.dwCursorPosition);//���ù��λ��
                        FillConsoleOutputCharacter(gh_std_out,' ',1,bInfo.dwCursorPosition,&ul);//�ַ���Ϊ�ո�
                    }

                }
                else if(bInfo.dwCursorPosition.X<pHotArea->pArea[*piHot-1].Right)
                {
                    FillConsoleOutputCharacter(gh_std_out,asc,1,bInfo.dwCursorPosition,&ul);//��ʾ�ַ�
                    bInfo.dwCursorPosition.X++;//�ı���λ��
                    SetConsoleCursorPosition(gh_std_out, bInfo.dwCursorPosition);
                    //WriteConsole(gh_std_out,stdin,20,&ul,NULL);
                }
            }
        }
    }
    PopOff();
}

/**
 * ��������: PanelChangeCaseInfo
 * ��������: ��ʾ�޸İ�����Ϣ�Ĵ��ڣ����밸�����.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void PanelChangeCaseInfo(void)//�����޸İ�����Ϣ�Ĵ���
{
    //BOOL bRet = TRUE;
    char *plabel_name[] = {"�������",
                           "            ",
                           "ȷ��"
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

    att =  BACKGROUND_GREEN ;  /*�̵׺���*/
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
    int cNo, cTag, cSort;/*cNo:���, cTag:�������, cSort: ��������*/
    char vkc, asc;       /*vkc:���������, asc:�ַ���ASCII��ֵ*/

    SetHotPoint(pHotArea, *piHot);
    while (TRUE)
    {    /*ѭ��*/
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
                {  /*�����(���ϡ��ҡ���)�Ĵ���*/
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
            {  /*ESC��*/
                //iRet = 27;
                break;
            }
            else if ((vkc == 13 || vkc == 32)&&pHotArea->pSort[*piHot-1]==0)
            {  /*�س�����ո��ʾ����ȷ��*/
                //iRet = 13;
                char caseid[13],prov[9],date[11],name[16],level,charge,money[20],judge[4];
                char *output[]={prov,caseid,date,name,&level,&charge,money,judge};
                ReadConsoleOutputCharacter(gh_std_out,caseid,13,aLoc[1],&ul);
                DealString(caseid);
                if(!TestCaseForChange(caseid,output))//�������������
                {
                    PopOff();
                    char *plabel_name[] = {"������Ϣ�����ڣ�",
                                           "ȷ��"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else//�����������
                {
                    PopOff();
                    PanelChangeCaseInfo1(output);
                }
                break;
            }
            else if (vkc == 13&&pHotArea->pSort[*piHot-1]==1)
            {  /*�ı���س�����ʾ����һ����*/
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
                if(vkc==8)//�˸�
                {
                    if(bInfo.dwCursorPosition.X>pHotArea->pArea[*piHot-1].Left)
                    {
                        bInfo.dwCursorPosition.X--;//�ı���λ��
                        SetConsoleCursorPosition(gh_std_out, bInfo.dwCursorPosition);//���ù��λ��
                        FillConsoleOutputCharacter(gh_std_out,' ',1,bInfo.dwCursorPosition,&ul);//�ַ���Ϊ�ո�
                    }

                }
                else if(bInfo.dwCursorPosition.X<pHotArea->pArea[*piHot-1].Right)
                {
                    FillConsoleOutputCharacter(gh_std_out,asc,1,bInfo.dwCursorPosition,&ul);//��ʾ�ַ�
                    bInfo.dwCursorPosition.X++;//�ı���λ��
                    SetConsoleCursorPosition(gh_std_out, bInfo.dwCursorPosition);
                }
            }
        }
    }
    //PopOff();
}

/**
 * ��������: PanelChangeCaseInfo1
 * ��������: ��ʾ�����û����밸���޸���Ϣ�Ĵ���.
 * �������: str �û�����İ������
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void PanelChangeCaseInfo1(char **str)//���������޸İ�����Ϣ�Ĵ���
{
    //BOOL bRet = TRUE;
    char *plabel_name[] = {"�������",
                           str[1],//12
                           "��������",
						   str[2],//10
						   "����ʡ��",
						   str[0],//8
                           "����������",
                           str[3],//15
                           "��������",
"���Ƽ�","���Ƽ�","������","������","������","������","������","������������",
                           "��Ҫ����",
"�ܻ�","̰��","Ų�ù���","��ְ","����ְȨ","����",
                           "�永���(��)",
                           str[6],//10
                           "���´���",
"����ͽ��(��)",str[7]/*3*/,"����ͽ��","����",
                           "ȷ��"
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

    att =  BACKGROUND_GREEN ;  /*�̵׺���*/
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
    int cNo, cTag, cSort;/*cNo:���, cTag:�������, cSort: ��������*/
    char vkc, asc;       /*vkc:���������, asc:�ַ���ASCII��ֵ*/
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
    //��ʾ�޸�ǰ����Ϣ���ݵ�������
    record1=aLoc[9+*str[4]-'A'];
    record1.X--;
    FillConsoleOutputCharacter(gh_std_out, '*', 1, record1 , &ul);//����������
    record2=aLoc[18+*str[5]-'1'];
    record2.X--;
    FillConsoleOutputCharacter(gh_std_out, '*', 1, record2, &ul);//��Ҫ�������
    if(atoi(str[7])<0)//���̱��
    {
        flag3=1;
        record3=aLoc[30];
        record3.X--;
        FillConsoleOutputCharacter(gh_std_out, '*', 1, record3, &ul);
        FillConsoleOutputCharacter(gh_std_out, ' ', 4, aLoc[28], &ul);
    }
    else if(atoi(str[7])>=100)//����ͽ�̱��
    {
        flag3=1;
        record3=aLoc[29];
        record3.X--;
        FillConsoleOutputCharacter(gh_std_out, '*', 1, record3, &ul);
        FillConsoleOutputCharacter(gh_std_out, ' ', 4, aLoc[28], &ul);
    }


    SetHotPoint(pHotArea, *piHot);
    while (TRUE)
    {    /*ѭ��*/
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
                {  /*�����(���ϡ��ҡ���)�Ĵ���*/
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
            {  /*ESC��*/
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
            else if(vkc==13&&(*piHot>=20&&*piHot<=22))//7 ���´���
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
                    FillConsoleOutputCharacter(gh_std_out,' ',4,aLoc[28],&ul);//����ı���ԭ������
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
            {  /*�س�����ո��ʾ����ȷ��*/
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
                    char *plabel_name[] = {"��Ϣ������������",
                                           "ȷ��"
                                          };
                    ShowModule(plabel_name, 2);
                    break;
                }
                else if(!TestProv(prov))
                {
                    char *plabel_name[] = {"ʡ����Ϣ�����ڣ�",
                                           "ȷ��"
                                          };
                    ShowModule(plabel_name, 2);
                    break;
                }
                else if(ChangeCaseInfo(head,str[1],input)==1)
                {
                    char *plabel_name[] = {"�޸ĳɹ���",
                                           "ԭ������Ϣ�µ�ý����Ϣ����ʧ��",
                                           "ȷ��"
                                          };
                    ShowModule(plabel_name, 3);
                }
                else
                {
                    char *plabel_name[] = {"�޸ĳɹ���",
                                            "ȷ��"
                                            };
                    ShowModule(plabel_name, 2);
                }
                break;
            }
            else if (vkc == 13&&pHotArea->pSort[*piHot-1]==1)
            {  /*�ı���س�����ʾ����һ����*/
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
                if(vkc==8)//�˸�
                {
                    if(bInfo.dwCursorPosition.X>pHotArea->pArea[*piHot-1].Left)
                    {
                        bInfo.dwCursorPosition.X--;//�ı���λ��
                        SetConsoleCursorPosition(gh_std_out, bInfo.dwCursorPosition);//���ù��λ��
                        FillConsoleOutputCharacter(gh_std_out,' ',1,bInfo.dwCursorPosition,&ul);//�ַ���Ϊ�ո�
                    }

                }
                else if(bInfo.dwCursorPosition.X<pHotArea->pArea[*piHot-1].Right)
                {
                    FillConsoleOutputCharacter(gh_std_out,asc,1,bInfo.dwCursorPosition,&ul);//��ʾ�ַ�
                    bInfo.dwCursorPosition.X++;//�ı���λ��
                    SetConsoleCursorPosition(gh_std_out, bInfo.dwCursorPosition);
                    //WriteConsole(gh_std_out,stdin,20,&ul,NULL);
                }
            }
        }
    }
    PopOff();
}

/**
 * ��������: PanelDeleteCaseInfo
 * ��������: ��ʾɾ��������Ϣ�Ĵ���.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void PanelDeleteCaseInfo(void)//����ɾ��������Ϣ�Ĵ���
{
    //BOOL bRet = TRUE;
    char *plabel_name[] = {"�������",
                           "            ",//12
                           "ȷ��"
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

    att =  BACKGROUND_GREEN ;  /*�̵׺���*/
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
    int cNo, cTag, cSort;/*cNo:���, cTag:�������, cSort: ��������*/
    char vkc, asc;       /*vkc:���������, asc:�ַ���ASCII��ֵ*/

    SetHotPoint(pHotArea, *piHot);
    while (TRUE)
    {    /*ѭ��*/
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
                {  /*�����(���ϡ��ҡ���)�Ĵ���*/
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
            {  /*ESC��*/
                //iRet = 27;
                break;
            }
            else if ((vkc == 13 || vkc == 32)&&pHotArea->pSort[*piHot-1]==0)
            {  /*�س�����ո��ʾ����ȷ��*/
                //iRet = 13;
                char id[13];
                ReadConsoleOutputCharacter(gh_std_out,id,13,aLoc[1],&ul);
                DealString(id);
                PopOff();
                if(!TestCase(id))
                {
                    char *plabel_name[] = {"������Ϣ�����ڣ�",
                                           "ȷ��"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else
                {
                    DeleteCaseInfo(head,id);
                    char *plabel_name[] = {"ɾ���ɹ���",
                                           "ԭ������Ϣ��ý����Ϣ����ʧ��",
                                           "ȷ��"
                                          };
                    ShowModule(plabel_name, 3);
                }
                break;
            }
            else if (vkc == 13&&pHotArea->pSort[*piHot-1]==1)
            {  /*�ı���س�����ʾ����һ����*/
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
                if(vkc==8)//�˸�
                {
                    if(bInfo.dwCursorPosition.X>pHotArea->pArea[*piHot-1].Left)
                    {
                        bInfo.dwCursorPosition.X--;//�ı���λ��
                        SetConsoleCursorPosition(gh_std_out, bInfo.dwCursorPosition);//���ù��λ��
                        FillConsoleOutputCharacter(gh_std_out,' ',1,bInfo.dwCursorPosition,&ul);//�ַ���Ϊ�ո�
                    }

                }
                else if(bInfo.dwCursorPosition.X<pHotArea->pArea[*piHot-1].Right)
                {
                    FillConsoleOutputCharacter(gh_std_out,asc,1,bInfo.dwCursorPosition,&ul);//��ʾ�ַ�
                    bInfo.dwCursorPosition.X++;//�ı���λ��
                    SetConsoleCursorPosition(gh_std_out, bInfo.dwCursorPosition);
                }
            }
        }
    }
    //PopOff();
}
