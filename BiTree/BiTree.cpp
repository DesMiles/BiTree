#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

//二叉树结构体
typedef struct TNode {
	int data;				//数据域
	struct TNode *lchild;	//左孩子节点
	struct TNode *rchild;	//右孩子节点
}BiTree; BiTree *T, *TreeNode;

//定义一个链队结构体
typedef struct LNode {
	BiTree *ptr;			//指向二叉树结点的指针
	struct LNode *next;		//指向下一个节点
}Queue; Queue *Q, *front, *rear, *ListNode;

//链队初始化操作
void InitQueue(Queue *Q) {
	Q = (Queue *)malloc(sizeof(Queue));
	Q->next = NULL;
	front = Q;
	rear = Q;
}

//链队进队操作
void EnQueue(Queue *Q, BiTree *Node) {
	ListNode = (Queue *)malloc(sizeof(Queue));
	ListNode->ptr = Node;
	ListNode->next = NULL;
	rear->next = ListNode;
	rear = rear->next;
}

//链队出队操作
void DeQueue(Queue *Q, BiTree *&Node) {
	if (front->next == rear) {
		rear = front;
	}
	ListNode = front->next;
	front->next = ListNode->next;
	Node = ListNode->ptr;
	free(ListNode);
}

//链队判空操作
bool IsEmpty(Queue *Q) {
	if (front == rear)
		return true;
	else
		return false;
}

//创建一颗高为level的满二叉树
void BuildFullBiTree(BiTree *T, int level) {
	if (level == 0) return;
	else{
		level--;
		T->data = rand() % 100;
		if (level != 0) {
			TreeNode = (BiTree *)malloc(sizeof(BiTree));
			TreeNode->lchild = NULL;
			TreeNode->rchild = NULL;
			T->lchild = TreeNode;
			BuildFullBiTree(T->lchild, level);
			TreeNode = (BiTree *)malloc(sizeof(BiTree));
			TreeNode->lchild = NULL;
			TreeNode->rchild = NULL;
			T->rchild = TreeNode;
			BuildFullBiTree(T->rchild, level);
		}	
	}
}

//二叉树先序遍历
void PSearchTree(BiTree *T, int level) {
	if (T == NULL) return;
	else {
		level++;
		printf("第 %d 层: %d\n\n", level, T->data);
		PSearchTree(T->lchild, level);
		PSearchTree(T->rchild, level);
	}
}

//二叉树层次遍历
void LevelSearchTree(BiTree *T, int level) {
	if (T == NULL) return;
	else {
		level++;
		int count = 0, upgrade = 0, i;
		printf("第 %d 层: %d\n\n", level, T->data);
		if (T->lchild != NULL) {
			EnQueue(Q, T->lchild);
			count++;
		}
		if (T->rchild != NULL) {
			EnQueue(Q, T->rchild);
			count++;
		}
		while (!IsEmpty(Q)) {
			level++;
			for (i = count; i > 0; i--) {
				DeQueue(Q, TreeNode);
				printf("第 %d 层: %d\n\n", level, TreeNode->data);
				if (TreeNode->lchild != NULL) {
					EnQueue(Q, TreeNode->lchild);
					upgrade++;
				}
				if (TreeNode->rchild != NULL) {
					EnQueue(Q, TreeNode->rchild);
					upgrade++;
				}
			}
			count = upgrade;
			upgrade = 0;
		}
	}
}

//隐藏光标
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };	//第二位0代表光标不可见
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//光标移动(从左上角开始，x表示横轴，y表示数轴)
void Gotoxy(int x, int y)
{
	HANDLE hout; //定义句柄变量hout
	COORD coord; //定义结构体coord
	coord.X = x;
	coord.Y = y;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);		//获得标准输出（屏幕）句柄
	SetConsoleCursorPosition(hout, coord);		//移动光标
}

//二级菜单
void SecondTierList(BiTree *T) {
	int level = 0;
	int option = -1;
	printf("---%s---\n%s\n%s\n%s\n",
		"创建二叉树",
		"1.创建一棵满二叉树（自动）",
		"2.创建一棵自定义二叉树（手动）",
		"0.返回上一级");
	printf("选择一个功能函数< >\b\b");
	scanf_s("%d", &option);
	getchar();
	switch (option) {
		case 1: {
			printf("\n输入想要创建的满二叉树高度（h）:");
			scanf_s("%d", &level);
			getchar();
			BuildFullBiTree(T, level);
			system("cls");
			printf("二叉树创建中......\n");
			HideCursor();//进度条初始化
			for (int i = 1; i <= 25; i++) {
				Gotoxy(2 * i, 1);
				printf("█");				
				printf("\n已完成%d%%", 4 * i);
				Sleep(100);
			}
			printf("\n创建完毕\n\n");
			system("pause");
			break;
		}
		case 2: {
			break;
		}
		case 0: {
			break;
		}
		default: {
			printf("\n该功能尚未开发，请重新输入功能函数序号\n");
			system("pause");
			break;
		}
	}
}

int main()
{
	srand((unsigned)time(NULL));
	const int level = 0;

	int option = 0;
	InitQueue(Q);

	T = (BiTree *)malloc(sizeof(BiTree));	//初始化一颗二叉树
	T->data = 0;
	T->lchild = NULL;
	T->rchild = NULL;

	while (option >= 0) {
		printf("---%s---\n%s\n%s\n%s\n%s\n",
			"二叉树程序",
			"1.创建二叉树",
			"2.先序遍历",
			"3.层次遍历",
			"0.结束程序");
		printf("选择一个功能函数< >\b\b");
		scanf_s("%d", &option);
		getchar();
		switch (option) {
			case 1: {
				system("cls");
				SecondTierList(T);
				system("cls");
				break;
			}			
			case 2: {
				putchar('\n');
				PSearchTree(T, 0); 
				system("pause");
				system("cls");
				break;
			}
			case 3: {
				putchar('\n');
				LevelSearchTree(T, 0);
				system("pause");
				system("cls");
				break;
			}				
			case 0: {
				option = -1;
				break;
			}
			default: {
				printf("\n该功能尚未开发，请重新输入功能函数序号\n");
				system("pause");
				break;
			}
		}
	}
	return 0;
}