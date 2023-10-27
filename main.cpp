#include <stdio.h>
#include <graphics.h>

#define STR_SIZE 20
#define STR_HEIGHT 15
#define STR_NUM 100

// =======================
struct Rain
{
	char str[STR_SIZE];	// 字符
	int  x, y;			// 坐标
	int  speed;			// 速度
};
// ========================

// =========================
// 创建随机字符串
char CreatCh();

// 绘制（在屏幕上显示字符串）
void DrawRain(struct Rain* r);

// 初始化
void initRain(struct Rain* r, int width, int height);

// 显示字符串
void ChangeStr(struct Rain* r);

// 字符串移动
void strMove(struct Rain* r, int height);
// ===========================

// 程序入口
int main()
{
	// 定义成员变量 width 和 height 用于记录系统最大的高和宽
	int width = GetSystemMetrics(SM_CXFULLSCREEN);
	int height = GetSystemMetrics(SM_CYFULLSCREEN) + 65;
	
	// 显示窗口，封装进变量hWindows
	HWND hWindows = initgraph(width, height);
	
	// 进行设置
	SetWindowLong(hWindows, GWL_STYLE, GetWindowLong(hWindows, GWL_STYLE) - WS_CAPTION);
	SetWindowPos(hWindows, HWND_TOPMOST, 0, 0, width, height, NULL);
	
	// 声明结构体变量
	struct Rain r[STR_NUM];

	// 循环重置
	for (int i = 0; i < STR_NUM; i++) {
		initRain(&r[i], width, height);
		r[i].x = i * 20;
	}

	setbkmode(TRANSPARENT);
	
	DWORD t1, t2;
	// 延迟
	t1 = t2 = GetTickCount();

	// 死循环（窗体）
	while (1)
	{
		BeginBatchDraw();	// 用于防止
		cleardevice();		// 闪动
		
		// 循环绘制
		for (int i = 0; i < STR_NUM; i++)
			DrawRain(&r[i]);
		
		// 上面的begin操作于下面截止
		EndBatchDraw();
		
		// 延迟操作
		if (t2 - t1 > 25)
		{
			// 使字符串移动
			for (int i = 0; i < STR_NUM; i++)
			{
				ChangeStr(&r[i]);
				strMove(&r[i], height);
			}
			t1 = t2;
		}
		// 延迟
		t2 = GetTickCount();
	}
	return 0;
}


// ==================================================
void initRain(struct Rain* r, int weight, int height)
{
	// 循环给结构体变量赋随机字符值
	for (int i = 0; i < STR_SIZE; i++)
	{
		r->str[i] = CreatCh();
	}

	// 坐标和速度
	r->x = rand() % weight;
	r->y = rand() % height;

	r->speed = rand() % 5 + 5;
}

void DrawRain(struct Rain* r)
{
	// 循环调用结构体显示字符
	for (int i = 0; i < STR_SIZE; i++)
	{
		settextcolor(RGB(0, 255 - i * 13, 0));
		outtextxy(r->x, r->y - STR_HEIGHT*i, r->str[i]);
	}
}

char CreatCh()
{
	// 随机flag（用于选择小写字符、大写字符、数字）
	int flag = rand() % 3;


	/* 选择 */
	// 小写字符
	if (0 == flag)
		return 'a' + rand() % 26;
	// 大写字符
	else if (1 == flag)
		return 'A' + rand() % 26;
	// 数字
	else
		return '0' + rand() % 26;
}

void ChangeStr(struct Rain* r)
{
	// 使字符不断更换，闪烁
	r->str[rand() % STR_SIZE] = CreatCh();
}

void strMove(struct Rain* r, int height)
{
	// 由于循环显示，每次刷新让字符的y坐标下降
	r->y += r->speed;

	if (r->y - STR_SIZE * STR_HEIGHT >= height)
	{
		r->speed = rand() % 5 + 5;
		r->y = 0;
	}
}
// ==================================================
