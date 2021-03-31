/*
	��Ŀ���ƣ�����ˮ�ɹ���ϵͳ
	��Ա����׿��,������,��꿵ѣ��鳤��
*/

//ͷ�ļ� 
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<windows.h>
#include<string.h>
#pragma warning(disable:4996)
//�궨��
#define M  sizeof(struct User)//�û���Ĵ�С 
///////////////////////////////
#define Q  sizeof(struct Drink) //��Ʒ���С 
#define X  sizeof(struct Table)//�������С 
#define Y  sizeof(struct Form)//�������С 

//�ṹ��

struct User    //�û��� 
{
	char userName[10];//�û��� 
	char passWord[18];//���� 
	int isVIP;//��Ա��� 
	int isAdministrator;//����Ա��� 
	float money;//��� 
	struct User* next;//ָ���� 
};
typedef struct User user;
typedef user* pUser;

///////////////////////////////////////////

struct Drink  //��Ʒ 
{
	char name[20];
	float price;
	int origin[8];//0��ˮ(mL),1����ţ��(mL),2�ǲ��(g),3�Ǳ�(��),4����(g),5�Ǽ�β��(mL),6��Ҭ��(g),7��С��(g)
	struct Drink* next;
};
typedef struct Drink DRI;
typedef DRI* pDRI;

struct Table   //���� (�е�����)
{
	int ID;//�������
	int People;//��������
	int count;//����������
	char Username[10];//������ 
	struct Table* next;
};
typedef struct Table table;
typedef table* pTable;


struct Form    //���� 
{
	char name[20];
	float price;
	struct Form* next;
};
typedef struct Form orderForm;
typedef orderForm* pOrder;


//����

	//�û��ͻ��� 
void Welcome();//��ӭ���� 
void User_Login();//�û���¼����
void Logon();//ע����� 
pUser readUserFile();//���ļ��ж�ȡ�û���Ϣ������һ����ͷ��ַ 
void save_User(pUser p1);//���û���Ϣ���浽�ļ��� 
void User_Menu();//�û��˵�  
void User_Order();//��� 
void Order_DrinkBeverage();//��Ʒ
void Order_Form(int ID, int number);//���� 
void User_List_Table();//�����б� 
void Apply_VIP_Menu();//��Ա����˵� 
void Add_money(pUser head);//��ֵ 
void Updata_User(pUser head);//�����û��� 
void Apply_VIP(pUser head);//�����Ա 
void User_Wallet();//�ҵ�Ǯ�� 


	//����Ա�ͻ��� 
void Administrator_Menu();//����Ա�˵� 
void Administrator_Login();//����Ա��¼ 
void Check_User();//�鿴�û� 
void Find_User();//�����û�
void All_User();//�鿴�����û� 
void All_VIP();//�����Ա 
void Food();//��Ʒ��Ϣ 
void Add_Food();//��Ӳ˵� 
void save_drinkBeverage(pDRI p);//������Ʒ��Ϣ
pDRI readDrinkBeverageFile();//����Ʒ�ļ��ж�ȡ�û���Ϣ������һ����ͷ��ַ
void Table();//�������� 
void Add_Table();//��Ӳ��� 
void save_Table(pTable p);//���������Ϣ
pTable readTableFile(); //�Ӳ����ļ��ж�ȡ�û���Ϣ������һ����ͷ��ַ
void Clear_Table();//������� 
void Clear_oneTable();//����ָ������
void Clear_allTable();//�������в��� 
void Updata_Table(pTable head);//���²����ļ� 
void Administrator_List_Table();//�����б� 

void History_Main();//��ʷ����


	//��������
void toxy(int x, int y);//������ƶ���x��y���괦
void HideCursor(int x);//���ع�� 
char* HidePassword();//�������� 
void Exit();//�˳�ϵͳ  
void Change();//�л��˺� 
void Amend_passWord();//�޸����� 
void List_Food();//�˵��б� 

//ȫ�ֱ�����
char _userName[10];
char _passWord[18];//��¼��ǰ�û� 
pOrder orderHead = NULL, p2 = NULL;//��¼��ǰ�û��Ķ��� 
int num = 0;

//����ʵ����

void toxy(int x, int y)//������ƶ���x��y���괦
{
	COORD pos = { (short)x,(short)y };
	HANDLE Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(Out, pos);
}

void HideCursor(int x)//���ع�� ,��xΪ0ʱ�����أ�Ϊ1ʱ����ʾ 
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,x };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void Welcome()//��ӭ���� 
{
	char t;//����ѡ�� 
	do
	{
		HideCursor(0); //���ع�� 
		system("color 74");
		toxy(28, 8);
		printf("     ��ӭ��������ˮ�ɣ�    ");
		toxy(26, 9);
		printf("-----------------------------");
		toxy(27, 11);
		printf("1.��¼  2.ע��  3.����Ա��¼");
		while (1)    //��ѭ��Ϊ��ֹ������������ 
		{
			t = getch();//�����Ժ��� 
			if (t == '1')//�����1��������¼���� 
				User_Login();
			else if (t == '2')//�����2�������ע����� 
				Logon();
			else if (t == '3')
				Administrator_Login();
		}//����Ȳ���1Ҳ����2��3����ѭ������ 
	} while (1);//��ԶΪ�� 

}

void User_Menu()//�û��˵� 
{

	char t;//����ѡ��˵�ѡ�� 
	do
	{
		system("cls");
		HideCursor(0); //���ع�� 
		system("color 74");
		toxy(32, 3);
		printf("---�û���Ʒѡ��ϵͳ---");
		toxy(32, 4);
		printf("��ǰ�û���%s", _userName);
		toxy(30, 5);
		printf("*********************");
		toxy(32, 7);
		printf("|  1.��Ʒ�б�  |");
		toxy(32, 9);
		printf("|  2.�����б�  |");
		toxy(32, 11);
		printf("|  3.��Ա����  |");
		toxy(32, 13);
		printf("|  4.�޸�����  |");
		toxy(32, 15);
		printf("|  5.�ҵ�Ǯ��  |");
		toxy(32, 17);
		printf("|  6.�л��˺�  |");
		toxy(32, 19);
		printf("|  7.�˳�ϵͳ  |");
		t = getch();//�����Ժ���������һ��ֵ 
		switch (t)
		{
		case '1':User_Order(); break;
		case '2':User_List_Table(); break;
		case '3':Apply_VIP_Menu(); break;
		case '4':Amend_passWord(); break;
		case '5':User_Wallet(); break;
		case '6':Change(); break;
		case '7':Exit(); break;
		default:break;
		}
	} while (1);//��Զ Ϊ�� 
}

char* HidePassword()//�������� 
{
	char password[18];//���� 
	char* p;//ָ�������ָ�� 
	int i = 0;//��¼����λ�� 
	char t;//�������� 
	for (;;)              //�˴�Ϊ�������벻���Բ��� 
	{
		t = getch();       //����k 
		if (t == '\r')      //�������kΪ�س���������ѭ�� 
		{
			break;
		}
		else if (t == '\b')  //�������kΪɾ���� 
		{
			if (i > 0)       //�������뻹û��ȫɾ�� 
			{
				printf("\b");
				printf(" ");
				printf("\b");
				i--;
			}
		}
		else              //��������k�Ȳ���ɾ������Ҳ���ǻس��� 
		{
			password[i] = t;   //��k��ֵ����_password[i]; 
			printf("*");      //���*�ţ������û���˽ 
			i++;              //����λ����1 
		}
	}
	password[i] = '\0';//������ĩ�˼�һ�������� 
	p = password;//��pָ������� 
	return p; //����һ��ָ�������ָ�� 
}

pUser readUserFile()//���ļ��ж�ȡ�û���Ϣ������һ����ͷ��ַ 
{
	FILE* fp;       //�ļ�ָ�� 
	int n = 0;//��¼���� �Ľ���� 
	pUser head = NULL;//����ͷָ�� 
	pUser p2 = NULL, p = NULL, pre = NULL;
	fp = fopen("User.txt", "a+");     //��ֻ���ķ�ʽ���ļ� 
	if (fp == NULL)
	{
		printf("cannot open file\n");
	}
	else
	{
		while (!feof(fp))        //�ж��ļ�λ�ñ�־�Ƿ��ƶ����ļ�ĩβ 
		{
			n++;
			p = (pUser)malloc(M); //���ڴ�����һ�οռ� 
			fread(p, M, 1, fp);     //��fp��ָ����ļ��е����ݸ���p
			if (n == 1)
			{
				head = p;
				p2 = p;
			}
			else             //�������� 
			{
				pre = p2;
				p2->next = p;
				p2 = p;
			}
		}
		p2->next = NULL;
	}
	if (n <= 2)
		head->next = NULL;
	else
		pre->next = NULL;
	fclose(fp);    //�ر��ļ� 
	return head;   //����ͷָ�� 
}

void save_User(pUser p1)     //��p1��ָ������ݴ洢���ļ��� 
{
	FILE* fp;       //�ļ�ָ�� 
	fp = fopen("User.txt", "a+");    //��׷�ӵķ�ʽ���ļ� 
	if (fp == NULL)
	{
		printf("cannot open file\n");
	}
	if (fwrite(p1, M, 1, fp) != 1)    //��p1��ָ���1����СΪN�����ݽṹд��fp��ָ����ļ��� 
	{
		printf("file write error\n");
	}
	fclose(fp);        //�ر��ļ� 
}

void User_Login()//��¼ҳ�� 
{
	char* q, t, c;//qָ�����ڽ��� *HidePassword()�������ص�ָ�������ָ�룬t��c������ѡ�� 
	pUser p = readUserFile();//���ļ��ж�ȡ�û���Ϣ������һ����ͷ��ַ 
	do
	{
		HideCursor(1);//��ʾ�ܹ�� 
		system("cls");//���� 
		system("color 73");//������ɫ 
		toxy(28, 8);
		printf("����ˮ��ϵͳ��¼����");
		toxy(26, 9);
		printf("-----------------------------");
		toxy(32, 11);
		printf("�û���:");
		toxy(32, 13);
		printf("��  ��:");
		toxy(40, 11);
		scanf("%s", _userName);
		toxy(40, 13);
		q = HidePassword();//�������� 
		strcpy(_passWord, q);//����õ����븴�Ƹ�_passWord[]���� 
		while (p != NULL && strcmp(p->userName, _userName) != 0)   //��������Ѱ�ҵ�ǰ������˻����˺� 
		{
			p = p->next;
		}
		if (p != NULL)   //���p��Ϊ�� 
		{
			if (strcmp(p->passWord, _passWord) == 0)     //��������������ȷ 
			{
				toxy(32, 16);
				printf("���ڵ�½....");
				Sleep(500);      //��ͣ0.5��
				system("cls");
				toxy(32, 10);
				printf("��½�ɹ���");
				break;    //����ѭ��
			}
			else      //���������������
			{
				toxy(32, 16);
				printf("���ڵ�½....");
				Sleep(500);
				system("cls");
				toxy(30, 8);
				printf("-------------------------");
				toxy(30, 9);
				printf("|                       |");
				toxy(30, 10);
				printf("| ��������Ƿ������  |");
				toxy(30, 12);
				printf("| 1.��             2.�� |");
				toxy(30, 13);
				printf("|                       |");
				toxy(30, 14);
				printf("-------------------------");
				while (1)//����ѭ��Ϊ��ֹ������������ 
				{
					t = getch();  //����t    
					if (t == '1')
					{
						system("cls");  //���� 
						break;
					}
					else if (t == '2')     //�������tΪn�����뿪ʼ���� 
					{
						system("cls");  //����
						Welcome(); break;
					}
				}
			}
		}
		else              //���pΪ�գ���������˺Ų���ȷ 
		{
			toxy(32, 16);
			printf("���ڵ�½....");
			Sleep(500);
			system("cls");
			toxy(30, 8);
			printf("-------------------------");
			toxy(30, 9);
			printf("|                       |");
			toxy(30, 10);
			printf("|  �˺Ŵ����Ƿ������ |");
			toxy(30, 11);
			printf("|                       |");
			toxy(30, 12);
			printf("|  1.��            2.�� |");
			toxy(30, 13);
			printf("|                       |");
			toxy(30, 14);
			printf("-------------------------");
			while (1)      //��ѭ����ֹ������������ 
			{
				c = getch();
				if (c == '1')
				{
					system("cls");
					break;
				}
				else if (c == '2')
				{
					system("cls");  //����
					Welcome();
				}
			}
		}
	} while (1);
	Sleep(500);      //��ͣ0.5�� 
	User_Menu();         //�˺��������ȷ�������û����˵� 
}

void Logon()//ע�����
{
	pUser p1;
	pUser p = readUserFile();//���ļ��ж�ȡ�û���Ϣ������һ����ͷ��ַ 
	p1 = (pUser)malloc(M);     //���ڴ�����һ�οռ� 
	char* q1, * q2;//q1��q2�ֱ����ڽ��� *HidePassword()�������ص�ֵ 
	char userName[10], passWord[18], againPassword[18], c, t;//c��t������ѡ�� 
	do {
		system("cls");
		system("color 73");
		HideCursor(1);//��ʾ��� 
		int flag = 0;//�����Ϣ�����Ƿ����Ҫע���û��� 
		toxy(28, 8);
		printf("����ˮ�ɹ���ϵͳע�����");
		toxy(26, 9);
		printf("-----------------------------");
		toxy(32, 11);
		printf("�� �� ��:");
		toxy(32, 13);
		printf("��    ��:");
		toxy(32, 15);
		printf("ȷ������:");
		toxy(42, 11);
		scanf("%s", userName);//�����û��� 
		toxy(42, 13);
		q1 = HidePassword();//�������� 
		strcpy(passWord, q1);
		toxy(42, 15);
		q2 = HidePassword();//����ȷ������ 
		strcpy(againPassword, q2);
		while (p != NULL)   //��������Ѱ�ҵ�ǰ������˻����˺� 
		{
			if (strcmp(p->userName, userName) == 0)//�����Ϣ���д��ڸ��û��� 
			{
				toxy(32, 17);
				printf("�û����Ѵ��ڣ�������ע�ᣡ");
				flag = 1;//flagΪ1ʱ��ʾ�û����Ѵ��� 
				break;//����ѭ�� 
			}
			p = p->next;
		}
		if (flag)//����û����Ѵ��� 
		{
			HideCursor(0);//���ع�� 
			toxy(32, 19);
			printf("�Ƿ������");//ѯ���Ƿ���� 
			toxy(32, 21);
			printf("1.��\t2.��");
			while (1)
			{
				t = getch();
				if (t == '1')
					break;
				else if (t == '2')
					break;
			}
			if (t == '1')//���������������ע�� 
				continue;
			else if (t == '2')//�������������ص���ҳ 
			{
				system("cls");//���� 
				Welcome();//�ص���ҳ 
			}
		}

		if (strcmp(passWord, againPassword) == 0)        //�������������������ȷ 
		{
			strcpy(p1->userName, userName);
			strcpy(p1->passWord, passWord);
			strcpy(_userName, userName);
			strcpy(_passWord, passWord);
			p1->isVIP = 0;
			p1->money = 0;
			if (strcmp(userName, "root") == 0 && strcmp(passWord, "root") == 0)
				p1->isAdministrator = 1;
			else
				p1->isAdministrator = 0;
			toxy(32, 16);
			printf("����ע��....");
			Sleep(500);
			break;              //����ѭ�� 
		}
		else    //���������������벻ͬ 
		{
			toxy(32, 16);
			printf("����ע��....");
			Sleep(500);
			system("cls");
			toxy(30, 8);
			printf("------------------------------");
			toxy(30, 9);
			printf("|                            |");
			toxy(30, 10);
			printf("|�������벻һ��!�Ƿ����ע��?|");
			toxy(30, 11);
			printf("|                            |");
			toxy(30, 12);
			printf("|  1.��                2.��  |");
			toxy(30, 13);
			printf("|                            |");
			toxy(30, 14);
			printf("------------------------------");
			while (1)
			{
				c = getch();
				if (c == '1')
				{
					system("cls");
					break;
				}
				else if (c == '2')
				{
					system("cls");
					Welcome();
					break;
				}
			}
		}
	} while (1);
	save_User(p1);     //���ú�������p1��ָ������ݴ洢���ļ��� 
	system("cls");
	toxy(32, 10);
	printf("ע��ɹ���");
	Sleep(500);         //��ͣ0.5�� 
	toxy(32, 12);
	printf("�����Զ�Ϊ����½....");
	Sleep(500);
	User_Menu();    //ע��ɹ���������˵� 
}

void User_Order()//���
{
	char ch = '0';
	char t = '0';
	int ID;
	int number;
	do
	{
		while (1)
		{
			system("cls");
			HideCursor(1);
			int flag = 0;
			pTable T, Thead;
			Thead = readTableFile();
			T = Thead;
			int j = 11;
			toxy(12, 6);
			printf("�����б�(�����������)");
			toxy(2, 8);
			printf("������� | �������� | ��������");
			toxy(0, 9);
			printf("--------------------------------------");
			while (T != NULL)
			{
				toxy(6, j);
				printf("%-10d%-10d%d", T->ID, T->count, T->People);
				j++;
				T = T->next;
			}
			toxy(38, 12);
			printf("��ѡ������ţ�");
			scanf("%d", &ID);
			toxy(40, 14);
			printf("��ѡ��������");
			scanf("%d", &number);
			T = Thead;
			while (T != NULL)
			{
				if (T->ID == ID)
				{
					if ((T->count) - (T->People) >= number)
					{
						toxy(38, 16);
						printf("ռ���ɹ�����������������");
						flag = 1;
						break;
					}
					else
					{
						toxy(38, 16);
						printf("ռ��ʧ�ܣ��ò�����λ����");
						flag = 0;
						break;
					}
				}
				T = T->next;
			}
			if (T == NULL && flag == 0)
			{
				toxy(38, 16);
				printf("�ò�����Ų����ڣ�����������");
				Sleep(1000);
				continue;
			}
			else if (T != NULL && flag == 0)
			{
				toxy(38, 17);
				printf("�Ƿ����  1.��   2.��");
				while (1)
				{
					ch = getch();
					if (ch == '1' || ch == '2')
						break;
				}
				if (ch == '1')
					continue;
				else if (ch == '2')
					break;
			}
			else if (flag)
				break;
		}
		if (ch == '2')
			break;
		getch();
		do
		{

			system("cls");
			toxy(32, 6);
			printf("���");
			toxy(24, 8);
			printf("-----------------");
			/*toxy(28, 10);
			printf("1) ��  ʳ");
			toxy(28, 12);
			printf("2) ��  ʳ");
			toxy(28, 14);*/
			printf("1) ��  Ʒ");
			toxy(28, 16);
			printf("2����  ��");
			toxy(28, 18);
			printf("3����  ��");
			t = getch();
			switch (t)
			{
			/*case '1':Order_StapleFood(); break;*/
			/*case '2':Order_nonStapleFood(); break;*/
			case '1':Order_DrinkBeverage(); break;
			case '2':Order_Form(ID, number); break;
			case '3':break;
			default:break;
			}
			if (t == '5')
				break;
		} while (1);
		if (t == '5')
			break;
	} while (1);
}

void Order_DrinkBeverage()//��Ʒ
{
	char t;
	do
	{
		system("cls");
		pDRI p, head = readDrinkBeverageFile();
		pOrder p1;
		p = head;
		char foodName[20];
		int i = 8;
		toxy(10, 4);
		printf("��Ʒ�˵�");
		toxy(6, 6);
		printf("����\t\t\t�۸�");
		toxy(0, 7);
		printf("-----------------------------------");
		while (p != NULL)
		{
			toxy(6, i);
			printf("%-22s%.2f", p->name, p->price);
			i++;
			p = p->next;
		}
		toxy(40, 8);
		printf("��������Ҫ��Ĳ���:");
		scanf("%s", foodName);
		p = head;
		while (p != NULL && strcmp(p->name, foodName) != 0)
		{
			p = p->next;
		}
		if (p)
		{
			p1 = (pOrder)malloc(Y);
			strcpy(p1->name, foodName);
			p1->price = p->price;
			num++;
			if (num == 1)
			{
				orderHead = p1;
				p2 = p1;
			}
			else
			{
				p2->next = p1;
				p2 = p1;
			}
			p2->next = NULL;
			toxy(36, 10);
			printf("��ͳɹ����Ƿ������1.��   2.��");
			while (1)
			{
				t = getch();
				if (t == '1')
					break;
				else if (t == '2')
					break;
			}
			if (t == '2')
				break;
		}
		else
		{
			toxy(36, 10);
			printf("û���ҵ�����ˣ�����������Ĳ����Ƿ���ȷ��");
			Sleep(1500);
		}
	} while (1);
}

void Order_Form(int ID, int number)//����
{
	do
	{
		system("cls");
		int i = 10;
		char t;
		double totalPrice = 0;
		double actualPayment = 0;
		pOrder p = orderHead;
		pUser q, head = NULL;
		pTable T, Thead;
		q = head;
		if (orderHead == NULL)
		{
			toxy(26, 8);
			printf("����û�е��κζ������Ͻ�ȥ��ɣ�(�����������)");
			getch();
			break;
		}
		else
		{
			toxy(26, 6);
			printf("�ҵĶ���");
			toxy(22, 8);
			printf("��Ʒ����\t\t�۸�");
			toxy(20, 9);
			printf("***************************");
			while (p != NULL)
			{
				toxy(22, i);
				printf("%-18s%.2f", p->name, p->price);
				i++;
				totalPrice += p->price;
				p = p->next;
			}
			head = readUserFile();
			q = head;
			toxy(20, i);
			printf("***************************");
			while (q != NULL && strcmp(q->userName, _userName) != 0)
			{
				q = q->next;
			}
			if (q)
			{
				toxy(24, ++i);
				printf("�ܼۣ�  %.2f", totalPrice);
				if (q->isVIP)
					actualPayment = totalPrice * 0.85;
				else
					actualPayment = totalPrice;
				toxy(24, ++i);
				printf("ʵ����  %.2f", actualPayment);
			}
			toxy(22, ++i);
			printf("1.ȷ��֧��   2.ȡ������   3.����");
			while (1)
			{
				t = getch();
				if (t == '1' || t == '2' || t == '3')
					break;
			}
			if (t == '1')
			{
				Thead = readTableFile();
				T = Thead;
				while (T != NULL && T->ID != ID)
				{
					T = T->next;
				}
				toxy(24, ++i);
				printf("����֧��....");
				if (q->money >= actualPayment)
				{
					q->money -= actualPayment;
					T->People += number;
					Updata_User(head);
					Updata_Table(Thead);
					Sleep(1500);
					system("cls");
					toxy(24, 10);
					printf("֧���ɹ��������������");
					orderHead = NULL;
					getch();
					break;
				}
				else
				{
					Sleep(1500);
					system("cls");
					toxy(24, 10);
					printf("���㣡�����������");
					getch();
					break;
				}
			}
			else if (t == '2')
			{
				orderHead = NULL;
				break;
			}
			else if (t == '3')
				break;
		}
	} while (1);
}

void User_List_Table()//�����б�
{
	system("cls");
	pTable p, head;
	head = readTableFile();
	p = head;
	int i = 11;
	toxy(32, 6);
	printf("�����б�(�����������)");
	toxy(22, 8);
	printf("������� | �������� | ��������");
	toxy(20, 9);
	printf("--------------------------------------");
	while (p != NULL)
	{
		toxy(26, i);
		printf("%-10d%-10d%d", p->ID, p->count, p->People);
		i++;
		p = p->next;
	}
	getch();
}

void Apply_VIP_Menu()//�����Ա
{
	char t; //t����ѡ�� 
	do
	{
		system("cls");
		system("color 75");
		HideCursor(0);
		pUser head = readUserFile();//���ļ��ж�ȡ�û���Ϣ������һ����ͷ��ַ
		toxy(32, 6);
		printf("��Ա����");
		toxy(30, 8);
		printf("1)  ��ֵ ");
		toxy(30, 10);
		printf("2)  �����Ա");
		toxy(30, 12);
		printf("3)  ����");
		t = getch();
		switch (t)
		{
		case '1':Add_money(head); break;
		case '2':Apply_VIP(head); break;
		case '3':break;
		default:break;
		}
		if (t == '3')//�������3��������ѭ�����ú����������ڽ������ص���һ���˵� 
			break;
	} while (1);
}

void Add_money(pUser head)//��ֵ
{
	float money;//����Ҫ��ֵ��Ǯ 
	pUser p;
	p = head;//headΪ�� ��һ���˵��������Ĳ�����Ϊ�û���Ϣ�����ͷ��� 
	while (p != NULL && strcmp(p->userName, _userName) != 0)//��������Ѱ�ҵ�ǰ��¼�˻�����Ϣ 
	{
		p = p->next;
	}
	while (1)
	{
		system("cls");
		system("color 76");
		toxy(32, 6);
		printf("�Ϻ�������ֵ����");
		if (p != NULL)
		{
			if (p->isVIP == 0)//������ǻ�Ա 
			{
				toxy(20, 8);
				printf("�Բ����������ǻ�Ա�����Ȱ����Ա��������ֵ��");
				toxy(32, 10);
				printf("�밴���������!");
				break;
			}
			else if (p->isVIP == 1)//����ǻ�Ա 
			{
				HideCursor(1);
				toxy(32, 8);
				printf("�������ֵ��һ�β�����200����");
				scanf("%f", &money);
				if (money >= 200)//�����ֵ������200 
				{
					p->money += money;
					toxy(32, 10);
					printf("���ڳ�ֵ....");
					Updata_User(head);//�����û��� 
					toxy(32, 10);
					printf("��ֵ�ɹ�    ");
					toxy(32, 12);
					printf("�밴���������!");
					break;
				}
				else//�����ֵ���С��200
				{
					toxy(32, 10);
					printf("һ�����ٳ�ֵ200Ԫ��");
					Sleep(1500);
					continue;
				}
			}
		}
	}
	getch();
}

void Apply_VIP(pUser head)//�����Ա
{
	system("cls");
	system("color 76");
	pUser p = head;//headΪ�� ��һ���˵��������Ĳ�����Ϊ�û���Ϣ�����ͷ���
	char t;
	float money;
	toxy(32, 6);
	printf("�Ϻ�������Ա��������");
	while (p != NULL && strcmp(p->userName, _userName) != 0)//��������Ѱ�ҵ�ǰ��¼�˻�����Ϣ
	{
		p = p->next;
	}
	do
	{
		if (p != NULL)
		{
			if (p->isVIP == 1)//����Ѿ��ǻ�Ա 
			{
				toxy(20, 8);
				printf("�����Ǳ�������Ա�������ٴΰ���");
				toxy(32, 10);
				printf("�밴���������!");
				getch();
				break;
			}
			else if (p->isVIP == 0)//�����û�����Ա 
			{
				toxy(30, 8);
				printf("��ʾ��");
				toxy(30, 9);
				printf("1.�����Ա���ٳ�ֵ500");
				toxy(30, 10);
				printf("2.��500��200����1000��500");
				toxy(32, 12);
				printf("�Ƿ�ȷ�ϰ����Ա��");
				toxy(32, 13);
				printf("1.��\t2.��");
				while (1)
				{
					t = getch();
					if (t == '1')
						break;
					else if (t == '2')
						break;
				}
				if (t == '1')
				{
					while (1)
					{
						system("cls");
						HideCursor(1);
						toxy(32, 10);
						printf("�������ֵ��");
						scanf("%f", &money);
						if (money >= 500 && money < 1000)
						{
							money += 200;
							p->money += money;
							p->isVIP = 1;
							Updata_User(head);
							toxy(32, 12);
							printf("��ϲ�����ѳ�Ϊ��������Ա��");
							toxy(32, 14);
							printf("�밴������������˵�");
							getch();
							User_Menu();
						}
						else if (money >= 1000)
						{
							money += 500;
							p->money += money;
							p->isVIP = 1;
							Updata_User(head);
							toxy(32, 12);
							printf("��ϲ�����ѳ�Ϊ��������Ա��");
							toxy(32, 14);
							printf("�밴������������˵�");
							getch();
							User_Menu();
						}
						else
						{
							toxy(32, 12);
							printf("�����Ա���ٳ�ֵ500");
							Sleep(2000);
						}
					}
				}
				else if (t == '2')
					break;
			}
		}
	} while (1);
}

void Updata_User(pUser head)//�����ļ� 
{
	FILE* fp;
	pUser p = head->next;                           //ʹpָ��ڶ������ 
	fp = fopen("User.txt", "w");                  //�����ԭ�ļ������ٽ��޸ĺ����Ϣд���ļ� 
	if (fp == NULL)
	{
		printf("cannot open file\n");
	}
	if (fwrite(head, M, 1, fp) != 1)                 //��head��ָ�������д��fp��ָ����ļ� 
	{
		printf("file write error\n");
	}
	fclose(fp);                         //�ر��ļ� 
	fp = fopen("User.txt", "a");          // ��User.txt�ļ�����ʽΪ׷�� 
	while (p != NULL)                    //p��Ϊ�վ�ִ��ѭ���� 
	{
		if (fwrite(p, M, 1, fp) != 1)            //��p��ָ���1����СΪN�����ݽṹд��fp��ָ����ļ� 
		{
			printf("file write error\n");
		}
		p = p->next;                     //ʹpָ����һ����� 
	}
	fclose(fp);              //�ر��ļ� 
}

void Amend_passWord()//�޸�����
{
	system("cls");         //���� 
	HideCursor(0);  //���ع�꣬���Ÿ���� 
	pUser p, head;
	head = readUserFile();
	do
	{
		p = head;
		char password[18], newpassword[18], t, * q1, * q2;
		int i = 0;
		toxy(34, 5);          //������ƶ�������Ϊ��50��5����λ�� 
		printf("����ˮ�ɹ���ϵͳ");
		toxy(34, 8);
		printf("�޸�����");
		toxy(32, 10);
		printf("����������룺");
		q1 = HidePassword();
		strcpy(password, q1);
		toxy(32, 12);
		printf("�����������룺");
		q2 = HidePassword();
		strcpy(newpassword, q2);
		while (p != NULL && strcmp(p->userName, _userName) != 0)//��������Ѱ�ҵ�ǰ��½�˻����˺� 
		{
			p = p->next;
		}
		if (p != NULL)                   //���p��Ϊ�� 
		{
			if (strcmp(p->passWord, password) == 0)          //���������������ȷ 
			{
				strcpy(p->passWord, newpassword);         //���������Ϊ������ 
				break;                                   //����ѭ�� 
			}
			else                                         //���������������� 
			{
				system("cls");
				toxy(30, 8);
				printf("--------------------------");
				toxy(30, 9);
				printf("|                        |");
				toxy(30, 10);
				printf("|  ��������Ƿ������  |");
				toxy(30, 11);
				printf("|                        |");
				toxy(30, 12);
				printf("|  1.��           2.��   |");
				toxy(30, 13);
				printf("|                        |");
				toxy(30, 14);
				printf("--------------------------");
				while (1)
				{
					t = getch();                              //����t 
					if (t == '1')
					{
						system("cls");
						break;
					}
					else if (t == '2')
						User_Menu();
				}
			}
		}
	} while (1);                                //��ԶΪ�� 
	Updata_User(head);//�޸����� 
	toxy(32, 14);
	printf("�޸ĳɹ���������ת...");
	Sleep(500);       //��ͣ0.5�� 
}

void User_Wallet()//�ҵ�Ǯ��
{
	system("cls");
	system("color 78");
	pUser p, head;
	head = readUserFile();
	p = head;
	while (p != NULL && strcmp(p->userName, _userName) != 0)
	{
		p = p->next;
	}
	if (p != NULL)
	{
		toxy(32, 10);
		printf("�˻����Ϊ��%.2f", p->money);
		toxy(32, 12);
		printf("�밴���������");
	}
	getch();
}

void Change()//�л��˺� 
{
	system("cls");
	Welcome();
}

void Exit()//�˳����ϵͳ 
{
	char t;
	toxy(30, 10);
	printf("-----------------------");
	toxy(30, 11);
	printf("|   ��ȷ��Ҫ�˳���  |");
	toxy(30, 13);
	printf("| 1.ȷ��     2.ȡ��   |");
	toxy(30, 14);
	printf("-----------------------");
	while (1)
	{
		t = getch();         //����t
		switch (t)
		{
		case '1':
			system("cls");
			toxy(32, 10);
			printf("���ڰ�ȫ�˳�....");
			Sleep(1000);     //��ͣ1�� 
			system("cls");
			toxy(32, 10);
			printf("�Ѱ�ȫ�˳����");
			toxy(32, 12);
			printf("ллʹ�ã�");
			toxy(32, 14);
			printf("by-by^_^");
			exit(0);  break; //��ֹ���� 
		case '2':
			break;   //���ú���������˵� 
		default:break;
		}
		if (t == '2')
			break;
	}
}

void Administrator_Menu()//����Ա�˵�
{
	char t;//����ѡ��˵�ѡ�� 
	do
	{
		system("cls");
		HideCursor(0); //���ع�� 
		system("color 74");
		toxy(32, 3);
		printf("����ˮ�ɹ���ϵͳ��");
		toxy(32, 4);
		printf("��ǰ����Ա��%s", _userName);
		toxy(30, 5);
		printf("*********************");
		toxy(32, 7);
		printf("|  1.��Ʒ  ��Ϣ  |");
		toxy(32, 9);
		printf("|  2.����  ����  |");
		toxy(32, 11);
		printf("|  3.�鿴  �û�  |");
		toxy(32, 13);
		printf("|  4.����  ��Ա  |");
		/*toxy(32, 15);
		printf("|  5.���ù���Ա  |");*/
		toxy(32, 17);
		printf("|  6.�޸�  ����  |");
		toxy(32, 19);
		printf("|  7.�л�  �˺�  |");
		toxy(32, 21);
		printf("|  8.�˳�  ϵͳ  |");
		t = getch();//�����Ժ���������һ��ֵ 
		switch (t)
		{
		case '1':Food(); break;
		case '2':Table(); break;
		case '3':Check_User(); break;
		case '4':All_VIP(); break;
		/*case '5':Setup_administrator(); break;*/
		case '6':Amend_passWord(); break;
		case '7':Change(); break;
		case '8':Exit(); break;
		default:break;
		}
	} while (1);//��Զ Ϊ�� 
}

void Administrator_Login()//����Ա��¼ 
{
	//char* q, t, c;//qָ�����ڽ��� *HidePassword()�������ص�ָ�������ָ�룬t��c������ѡ�� 
	//pUser p = readUserFile();//���ļ��ж�ȡ�û���Ϣ������һ����ͷ��ַ 
	/*do
	{*/
		HideCursor(1);//��ʾ�ܹ�� 
		system("cls");//���� 
		system("color 73");//������ɫ 
		toxy(28, 8);
		printf("������......");
	Sleep(500);      //��ͣ0.5�� 
	Administrator_Menu();         //�˺��������ȷ���������Ա���˵� 
}

void Food()//��Ʒ��Ϣ
{
	system("color 74");
	char t;
	do
	{
		system("cls");
		toxy(32, 6);
		printf("��Ʒ��Ϣ");
		toxy(28, 7);
		printf("-----------------");
		toxy(30, 9);
		printf(" 1) ��Ӳ˵�");
		toxy(30, 11);
		printf(" 2) �˵��б�");
		toxy(30, 13);
		printf(" 3) ������һ��");
		t = getch();
		switch (t)
		{
		case '1':Add_Food(); break;
		case '2':List_Food(); break;
		case '3':break;
		default:break;
		}
		if (t == '3')
			break;
	} while (1);
}
/// ///////////////////////////////
void save_drinkBeverage(pDRI p)//������Ʒ��Ϣ
{
	FILE* fp;       //�ļ�ָ�� 
	fp = fopen("DrinkBeverage.txt", "a+");    //��׷�ӵķ�ʽ���ļ� 
	if (fp == NULL)
	{
		printf("cannot open file\n");
	}
	if (fwrite(p, Q, 1, fp) != 1)    //��p1��ָ���1����СΪN�Ľṹ��д��fp��ָ����ļ��� 
	{
		printf("file write error\n");
	}
	fclose(fp);        //�ر��ļ� 
}
/// /////////////////////////////////////
pDRI readDrinkBeverageFile()//����Ʒ�ļ��ж�ȡ�û���Ϣ������һ����ͷ��ַ
{
	FILE* fp;       //�ļ�ָ�� 
	int n = 0;//��¼���� �Ľ���� 
	pDRI head = NULL;//����ͷָ�� 
	pDRI p2 = NULL, p = NULL, pre = NULL;
	fp = fopen("DrinkBeverage.txt", "a+");     //��ֻ���ķ�ʽ���ļ� 
	if (fp == NULL)
	{
		printf("cannot open file\n");
	}
	else
	{
		while (!feof(fp))        //�ж��ļ�λ�ñ�־�Ƿ��ƶ����ļ�ĩβ 
		{
			n++;
			p = (pDRI)malloc(Q); //���ڴ�����һ�οռ� 
			fread(p, Q, 1, fp);     //��fp��ָ����ļ��е����ݸ���p
			if (n == 1)
			{
				head = p;
				p2 = p;
			}
			else             //�������� 
			{
				pre = p2;
				p2->next = p;
				p2 = p;
			}
		}
		p2->next = NULL;
	}
	if (n <= 2)
		head->next = NULL;
	else
		pre->next = NULL;
	fclose(fp);    //�ر��ļ� 
	return head;   //����ͷָ�� 
}

void Add_Food()  //��Ӳ˵�
{
	HideCursor(1);//��ʾ��� 
	pDRI p3;//��Ʒ 
	char name[20];
	float price = 0;
	int type = 1;
	char t;
	do
	{
		system("cls");
		p3 = (pDRI)malloc(Q);
		toxy(30, 6);
		printf("��������Ʒ��:");
		toxy(30, 8);
		printf("������۸�:");
		toxy(30, 10);
		printf("������ԭ����(û����0):");
		toxy(30, 12);
		printf("ˮ(mL):");
		toxy(30, 14);
		printf("��(mL):");
		toxy(30, 16);
		printf("���(mL):");
		toxy(30, 18);
		printf("��(mL):");
		toxy(30, 20);
		printf("��(mL):");
		toxy(30, 22);
		printf("��β��(mL):"); 
		toxy(30, 24);
		printf("Ҭ��(mL):");
		toxy(30, 26);
		printf("С��(mL):");
		
		toxy(50, 6);
		scanf("%s", name);
		toxy(50, 8);
		scanf("%f", &price);
		toxy(46, 12);
		scanf("%d", &p3->origin[0]);
		toxy(46, 14);
		scanf("%d", &p3->origin[1]);
		toxy(46, 16);
		scanf("%d", &p3->origin[2]);
		toxy(46, 18);
		scanf("%d", &p3->origin[3]);
		toxy(46, 20);
		scanf("%d", &p3->origin[4]);
		toxy(46, 22);
		scanf("%d", &p3->origin[5]);
		toxy(46, 24);
		scanf("%d", &p3->origin[6]);
		toxy(46, 26);
		scanf("%d", &p3->origin[7]);
		/*if (type == 1)
		{
			strcpy(p1->name, name);
			p1->price = price;
			save_stapleFood(p1);
		}
		else if (type == 2)
		{
			strcpy(p2->name, name);
			p2->price = price;
			save_non_stapleFood(p2);
		}*/
		if (type == 3)
		{
			strcpy(p3->name, name);
			p3->price = price;
			save_drinkBeverage(p3);
		}
		toxy(28, 14);
		printf("---------------------------------");
		toxy(28, 16);
		printf("��ӳɹ�!�Ƿ����?[(1)��(2)��]");
		toxy(28, 18);
		printf("---------------------------------");
		while (1)
		{
			t = getch();
			if (t == '1')
				break;
			else if (t == '2')
				break;
		}
		if (t == '2')
			break;
	} while (1);

}

void List_Food()  //�˵��б�
{
	system("cls");
	int i = 8;
	toxy(30, 4);
	printf("�˵��б�(�����������)");
	/// /////////////////////////////////
	pDRI p3;//��Ʒ 
	/// //////////////////////////////////////////////
	p3 = readDrinkBeverageFile();//����Ʒ�ļ��ж�ȡ�û���Ϣ������һ����ͷ��ַ 
	toxy(26, 6);
	printf("��Ʒ��\t\t\t�۸�");
	toxy(20, 7);
	printf("-----------------------------------");
	toxy(24, i);
	/*printf("��ʳ��");
	i++;*/
	/*while (p1 != NULL)
	{
		toxy(26, i);
		printf("%-22s%.2f", p1->name, p1->price);
		i++;
		p1 = p1->next;
	}
	toxy(24, i);
	printf("��ʳ��");
	i++;
	while (p2 != NULL)
	{
		toxy(26, i);
		printf("%-22s%.2f", p2->name, p2->price);
		i++;
		p2 = p2->next;
	}*/
	//toxy(24, i);
	printf("��Ʒ��");
	i++;
	while (p3 != NULL)
	{
		toxy(26, i);
		printf("%-22s%.2f", p3->name, p3->price);
		i++;
		p3 = p3->next;
	}
	getch();
}

void Table()//��������
{
	char t;
	do
	{
		system("cls");
		HideCursor(0);
		toxy(32, 4);
		printf("��������");
		toxy(26, 5);
		printf("-------------------");
		toxy(30, 7);
		printf("1) ��Ӳ���");
		toxy(30, 9);
		printf("2) �����б�");
		toxy(30, 11);
		printf("3) �������");
		toxy(30, 13);
		printf("4) ������һ��");
		t = getch();
		switch (t)
		{
		case '1':Add_Table(); break;
		case '2':Administrator_List_Table(); break;
		case '3':Clear_Table(); break;
		case '4':break;
		default:break;
		}
		if (t == '4')
			break;
	} while (1);
}

void save_Table(pTable p)//���������Ϣ
{
	FILE* fp;       //�ļ�ָ�� 
	fp = fopen("Table.txt", "a+");    //��׷�ӵķ�ʽ���ļ� 
	if (fp == NULL)
	{
		printf("cannot open file\n");
	}
	if (fwrite(p, X, 1, fp) != 1)    //��p1��ָ���1����СΪN�����ݽṹд��fp��ָ����ļ��� 
	{
		printf("file write error\n");
	}
	fclose(fp);        //�ر��ļ� 
}

pTable readTableFile()//�Ӳ����ļ��ж�ȡ�û���Ϣ������һ����ͷ��ַ
{
	FILE* fp;       //�ļ�ָ�� 
	int n = 0;//��¼���� �Ľ���� 
	pTable head = NULL;//����ͷָ�� 
	pTable p2 = NULL, p, pre = NULL;
	fp = fopen("Table.txt", "a+");     //��ֻ���ķ�ʽ���ļ� 
	if (fp == NULL)
	{
		printf("cannot open file\n");
	}
	else
	{
		while (!feof(fp))        //�ж��ļ�λ�ñ�־�Ƿ��ƶ����ļ�ĩβ 
		{
			n++;
			p = (pTable)malloc(X); //���ڴ�����һ�οռ� 
			fread(p, X, 1, fp);     //��fp��ָ����ļ��е����ݸ���p
			if (n == 1)
			{
				head = p;
				p2 = p;
			}
			else             //�������� 
			{
				pre = p2;
				p2->next = p;
				p2 = p;
			}
		}
		p2->next = NULL;
	}
	if (n <= 2)
		head->next = NULL;
	else
		pre->next = NULL;
	fclose(fp);    //�ر��ļ� 
	return head;   //����ͷָ�� 
}

void Add_Table()//��Ӳ��� 
{
	HideCursor(1);//��ʾ��� 
	pTable p, p1;
	p1 = readTableFile();
	char t;
	int ID;
	int count;
	do
	{
		system("cls");
		p = (pTable)malloc(X);
		toxy(26, 6);
		printf("������������:");
		toxy(26, 8);
		printf("�������������:");
		toxy(42, 6);
		scanf("%d", &ID);
		toxy(42, 8);
		scanf("%d", &count);
		while (p1 != NULL && p1->ID != ID)
		{
			p1 = p1->next;
		}
		if (p1 != NULL)
		{
			toxy(30, 10);
			printf("�ò�������Ѵ��ڣ����������룡");
			Sleep(2000);
			continue;
		}
		p->ID = ID;
		p->People = 0;
		p->count = count;
		strcpy(p->Username, "��");
		save_Table(p);
		toxy(24, 10);
		printf("��ӳɹ����Ƿ������(1.��   2.��)");
		while (1)
		{
			t = getch();
			if (t == '1')
				break;
			else if (t == '2')
				break;
		}
		if (t == '2')
			break;
	} while (1);
}

void Administrator_List_Table()//�����б�
{
	system("cls");
	pTable p, head;
	head = readTableFile();
	p = head;
	int i = 11;
	toxy(32, 6);
	printf("�����б�(�����������)");
	toxy(22, 8);
	printf("������� | �������� | �������� | ������");
	toxy(20, 9);
	printf("--------------------------------------------");
	while (p != NULL)
	{
		toxy(26, i);
		printf("%-10d%-10d%-10d%s", p->ID, p->count, p->People, p->Username);
		i++;
		p = p->next;
	}
	getch();
}

void History_Main()//��ʷ����
{

}

void Clear_Table()//�������
{
	char t;
	do
	{
		system("cls");
		toxy(32, 4);
		printf("�������");
		toxy(26, 5);
		printf("-------------------");
		toxy(30, 7);
		printf("1) ����ָ������");
		toxy(30, 9);
		printf("2) �������в���");
		toxy(30, 11);
		printf("3) ������һ��");
		t = getch();
		switch (t)
		{
		case '1':Clear_oneTable(); break;
		case '2':Clear_allTable(); break;
		case '3':break;
		default:break;
		}
		if (t == '3')
			break;
	} while (1);
}

void Updata_Table(pTable head)//���²����ļ�
{
	FILE* fp;
	pTable p = head->next;                           //ʹpָ��ڶ������ 
	fp = fopen("Table.txt", "w");                  //�����ԭ�ļ������ٽ��޸ĺ����Ϣд���ļ� 
	if (fp == NULL)
	{
		printf("cannot open file\n");
	}
	if (fwrite(head, X, 1, fp) != 1)                 //��head��ָ�������д��fp��ָ����ļ� 
	{
		printf("file write error\n");
	}
	fclose(fp);                         //�ر��ļ� 
	fp = fopen("Table.txt", "a");          // ��User.txt�ļ�����ʽΪ׷�� 
	while (p != NULL)                    //p��Ϊ�վ�ִ��ѭ���� 
	{
		if (fwrite(p, X, 1, fp) != 1)            //��p��ָ���1����СΪN�����ݽṹд��fp��ָ����ļ� 
		{
			printf("file write error\n");
		}
		p = p->next;                     //ʹpָ����һ����� 
	}
	fclose(fp);              //�ر��ļ� 
}

void Clear_oneTable()//����ָ������
{
	int ID;
	pTable p, head;
	char t;
	do
	{
		system("cls");
		head = readTableFile();
		p = head;
		toxy(28, 8);
		printf("��������Ҫ����Ĳ������:");
		scanf("%d", &ID);
		while (p != NULL && p->ID != ID)
		{
			p = p->next;
		}
		if (p)
		{
			toxy(32, 10);
			printf("��������....");
			p->People = 0;
			strcpy(p->Username, "��");
			Updata_Table(head);
			Sleep(2000);
			toxy(24, 10);
			printf("����ɹ����Ƿ������1.��   2.��");
			while (1)
			{
				t = getch();
				if (t == '1')
					break;
				else if (t == '2')
					break;
			}
			if (t == '2')
				break;
		}
		else
		{
			toxy(32, 10);
			printf("�ò��������ڣ�����������");
			Sleep(1500);
		}
	} while (1);
}

void Clear_allTable()//�������в���
{
	system("cls");
	toxy(32, 10);
	printf("��������....");
	pTable p, head;
	head = readTableFile();
	p = head;
	while (p != NULL)
	{
		p->People = 0;
		strcpy(p->Username, "��");
		p = p->next;
	}
	Updata_Table(head);
	Sleep(2000);
	toxy(32, 10);
	printf("����ɹ��������������");
	getch();
}

void Check_User()//�鿴�û�
{
	char t;
	do
	{
		system("cls");
		system("color 79");
		toxy(32, 6);
		printf("  �鿴�û�  ");
		toxy(32, 7);
		printf("----------------");
		toxy(32, 9);
		printf(" 1) �����û� ");
		toxy(32, 11);
		printf(" 2) �����û� ");
		toxy(32, 13);
		printf(" 3��������һ��");
		t = getch();
		switch (t)
		{
		case '1':Find_User(); break;
		case '2':All_User(); break;
		case '3':break;
		default:break;
		}
		if (t == '3')
			break;
	} while (1);
}

void Find_User()//�����û�
{
	system("cls");
	char username[10];
	pUser p, head = readUserFile();
	p = head;
	toxy(32, 10);
	printf("��������Ҫ���ҵ��û�����");
	scanf("%s", username);
	toxy(24, 12);
	printf("�û���\t\t���\t\t��Ա״̬");
	while (p != NULL && strcmp(p->userName, username) != 0)
		p = p->next;
	if (p != NULL)
	{
		toxy(24, 14);
		printf("%s\t\t%.2f\t\t%d", p->userName, p->money, p->isVIP);
	}
	else
	{
		toxy(28, 14);
		printf("û���ҵ������Ϣ");
	}
	toxy(30, 16);
	printf("�밴���������");
	getch();
}

void All_User()//��ӡ�����û���Ϣ
{
	system("cls");
	pUser p, head;
	head = readUserFile();
	p = head;
	int i = 9;
	toxy(32, 4);
	printf("�����û�");
	toxy(20, 5);
	printf("--------------------------------------------------");
	toxy(30, 6);
	printf("�����������");
	toxy(24, 7);
	printf("�û���\t\t���\t\t��Ա״̬");
	while (p != NULL)
	{
		toxy(24, i);
		printf("%s\t\t%.2f\t\t%d", p->userName, p->money, p->isVIP);
		p = p->next;
		i += 2;
	}
	getch();
}

void All_VIP()//�鿴����VIP 
{
	system("cls");
	system("color 79");
	pUser p, head;
	head = readUserFile();
	p = head;
	int i = 11;
	toxy(32, 6);
	printf("�����Ա");
	toxy(26, 8);
	printf("�û���\t\t���");
	toxy(24, 9);
	printf("--------------------------------");
	while (p != NULL)
	{
		if (p->isVIP)
		{
			toxy(26, i);
			printf("%s\t\t\t%.2f", p->userName, p->money);
			i += 2;
		}
		p = p->next;
	}
	toxy(30, i);
	printf("�����������");
	getch();
}
int main()
{
	Welcome();//���뻶ӭ���� 
	return 0;
}

