#include <stdio.h>
#include <graphics.h>

#define STR_SIZE 20
#define STR_HEIGHT 15
#define STR_NUM 100

// =======================
struct Rain
{
	char str[STR_SIZE];	// �ַ�
	int  x, y;			// ����
	int  speed;			// �ٶ�
};
// ========================

// =========================
// ��������ַ���
char CreatCh();

// ���ƣ�����Ļ����ʾ�ַ�����
void DrawRain(struct Rain* r);

// ��ʼ��
void initRain(struct Rain* r, int width, int height);

// ��ʾ�ַ���
void ChangeStr(struct Rain* r);

// �ַ����ƶ�
void strMove(struct Rain* r, int height);
// ===========================

// �������
int main()
{
	// �����Ա���� width �� height ���ڼ�¼ϵͳ���ĸߺͿ�
	int width = GetSystemMetrics(SM_CXFULLSCREEN);
	int height = GetSystemMetrics(SM_CYFULLSCREEN) + 65;
	
	// ��ʾ���ڣ���װ������hWindows
	HWND hWindows = initgraph(width, height);
	
	// ��������
	SetWindowLong(hWindows, GWL_STYLE, GetWindowLong(hWindows, GWL_STYLE) - WS_CAPTION);
	SetWindowPos(hWindows, HWND_TOPMOST, 0, 0, width, height, NULL);
	
	// �����ṹ�����
	struct Rain r[STR_NUM];

	// ѭ������
	for (int i = 0; i < STR_NUM; i++) {
		initRain(&r[i], width, height);
		r[i].x = i * 20;
	}

	setbkmode(TRANSPARENT);
	
	DWORD t1, t2;
	// �ӳ�
	t1 = t2 = GetTickCount();

	// ��ѭ�������壩
	while (1)
	{
		BeginBatchDraw();	// ���ڷ�ֹ
		cleardevice();		// ����
		
		// ѭ������
		for (int i = 0; i < STR_NUM; i++)
			DrawRain(&r[i]);
		
		// �����begin�����������ֹ
		EndBatchDraw();
		
		// �ӳٲ���
		if (t2 - t1 > 25)
		{
			// ʹ�ַ����ƶ�
			for (int i = 0; i < STR_NUM; i++)
			{
				ChangeStr(&r[i]);
				strMove(&r[i], height);
			}
			t1 = t2;
		}
		// �ӳ�
		t2 = GetTickCount();
	}
	return 0;
}


// ==================================================
void initRain(struct Rain* r, int weight, int height)
{
	// ѭ�����ṹ�����������ַ�ֵ
	for (int i = 0; i < STR_SIZE; i++)
	{
		r->str[i] = CreatCh();
	}

	// ������ٶ�
	r->x = rand() % weight;
	r->y = rand() % height;

	r->speed = rand() % 5 + 5;
}

void DrawRain(struct Rain* r)
{
	// ѭ�����ýṹ����ʾ�ַ�
	for (int i = 0; i < STR_SIZE; i++)
	{
		settextcolor(RGB(0, 255 - i * 13, 0));
		outtextxy(r->x, r->y - STR_HEIGHT*i, r->str[i]);
	}
}

char CreatCh()
{
	// ���flag������ѡ��Сд�ַ�����д�ַ������֣�
	int flag = rand() % 3;


	/* ѡ�� */
	// Сд�ַ�
	if (0 == flag)
		return 'a' + rand() % 26;
	// ��д�ַ�
	else if (1 == flag)
		return 'A' + rand() % 26;
	// ����
	else
		return '0' + rand() % 26;
}

void ChangeStr(struct Rain* r)
{
	// ʹ�ַ����ϸ�������˸
	r->str[rand() % STR_SIZE] = CreatCh();
}

void strMove(struct Rain* r, int height)
{
	// ����ѭ����ʾ��ÿ��ˢ�����ַ���y�����½�
	r->y += r->speed;

	if (r->y - STR_SIZE * STR_HEIGHT >= height)
	{
		r->speed = rand() % 5 + 5;
		r->y = 0;
	}
}
// ==================================================
