#include"os_obj4.h"

//输入文档，并初始化作业信息
void in(queue *q,work *w, int q_num,int work_num)
{
	const char* filename = "work.txt";
	ifstream ism;
	ism.open(filename);
	if (!ism.is_open())
	{
		cout << "hhhhhhhhh" << endl;
	}
	for (int i = 0; i < work_num; i++)
	{
		ism >> w[i].name;
	}
	for (int i = 0; i < work_num; i++)
	{
		ism >> w[i].size;
	}
	for (int i = 0; i < q_num; i++)
	{
		ism >> q[i].size;
	}
}

//输出函数，输出内存最终分配情况
void out(queue* q, work* w, int q_num, int work_num)
{
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "作业名:" << "\t" << "\t";
	for (int i = 0; i < work_num; i++)
	{
		cout << w[i].name << "\t";
	}
	cout << endl;
	cout << "作业大小：" << "\t";
	for (int i = 0; i < work_num; i++)
	{
		cout << w[i].size << "\t";
	}
	cout << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	/*
	cout << "队列情况为：" << endl;
	for (int i = 0; i < q_num; i++)
	{
		if (q[i].n != 0)
		{
			for (int j = 0; j < q[i].n; j++)
			{
				cout << "位置" << i << "存放的第" << j << "个作业为：" << q[i].name[j]<<endl;
			}
			cout << "位置" << i << "所剩大小为：" << q[i].size<<endl;
		}
		else
		{
			cout << "位置" << i << "没有放作业" << endl;
		}
	}*/
	cout << "位置序号：" << "\t";
	for (int i = 0; i < q_num; i++)
	{
		cout << i << "\t";
	}
	cout << endl;
	cout << "作业名称：" << "\t";
	for (int i = 0; i < q_num; i++)
	{
		if (q[i].n != 0)
		{
			for (int j = 0; j < q[i].n; j++)
			{
				cout << q[i].name[j] << " ";
			}
			cout << "\t";
		}
		else
		{
			cout <<" " << "\t";
		}
	}
	cout << endl;
	cout << "剩余大小：" << "\t";
	for (int i = 0; i < q_num; i++)
	{
		cout << q[i].size << "\t" ;
	}
	cout << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
}

//按照内存剩余空间最小，排序存储作业下标的数组
void sort_size_Best(int *a , queue *q, int q_num)
{
	for (int i = 0; i < q_num; i++)
	{
		for (int j = q_num - 1; j > i; j--)
		{
			if (q[a[j - 1]].size > q[a[j]].size)
			{
				int temp = 0;
				temp = a[j - 1];
				a[j - 1] = a[j];
				a[j] = temp;
			}
		}
	}
}

//按照内存剩余空间最大，排序存储作业下标的数组
void sort_size_Worst(int* a, queue* q, int q_num)
{
	for (int i = 0; i < q_num; i++)
	{
		for (int j = q_num - 1; j > i; j--)
		{
			if (q[a[j - 1]].size < q[a[j]].size)
			{
				int temp = 0;
				temp = a[j - 1];
				a[j - 1] = a[j];
				a[j] = temp;
			}
		}
	}
}

//首次适应算法
void FirstAdapt(queue *q,work* w,int q_num, int work_num)
{
	for (int i = 0; i < work_num; i++)
	{
		for (int j = 0; j < q_num; j++)
		{
			if (q[j].size >= w[i].size)
			{
				q[j].name[q[j].n] = w[i].name;
				q[j].size -= w[i].size;
				q[j].n = q[j].n + 1;
				j = -1;
				break;
			}
			else {
				continue;
			}
		}
	}
}

//循环首次适应算法
void FirstAdapt_cycle(queue* q, work* w, int q_num, int work_num)
{
	int j = 0;
	for (int i = 0; i < work_num; i++)
	{
		for (j; j < q_num; j++)
		{
			if (q[j].size >= w[i].size)
			{
				q[j].name[q[j].n] = w[i].name;
				q[j].size -= w[i].size;
				q[j].n = q[j].n + 1;
				break;
			}
			else {
				continue;
			}
		}
		if (j < q_num-1)
		{
			j++;
		}
		else
		{
			j = 0;
		}
	}
}

//最佳适应算法
void BestFit(queue* q, work* w, int q_num, int work_num)
{
	int temp[10] = { 0 };
	for (int x = 0; x < 10; x++)
	{
		temp[x] = x;
	}
	sort_size_Best(temp, q, q_num);
	for (int i = 0; i < work_num; i++)
	{
		for (int j = 0; j < q_num; j++)
		{
			if (q[temp[j]].size >= w[i].size)
			{
				q[temp[j]].name[q[temp[j]].n] = w[i].name;
				q[temp[j]].size -= w[i].size;
				q[temp[j]].n = q[temp[j]].n + 1;
				sort_size_Best(temp, q, q_num);
				break;
			}
			else {
				continue;
			}
		}
	}
}

//最坏适应算法
void WorstFit(queue* q, work* w, int q_num, int work_num)
{
	int temp[10] = { 0 };
	for (int x = 0; x < 10; x++)
	{
		temp[x] = x;
	}
	sort_size_Worst(temp, q, q_num);
	for (int i = 0; i < work_num; i++)
	{
		for (int j = 0; j < q_num; j++)
		{
			if (q[temp[j]].size >= w[i].size)
			{
				q[temp[j]].name[q[temp[j]].n] = w[i].name;
				q[temp[j]].size -= w[i].size;
				q[temp[j]].n = q[temp[j]].n + 1;
				sort_size_Worst(temp, q, q_num);
				break;
			}
			else {
				continue;
			}
		}
	}
}

//初始化内存空间
void ini(queue* q, int q_num)
{
	for (int i = 0; i < q_num; i++)
	{
		for (int j = 0; j < q[i].n; j++)
		{
			q[i].name[j] = NULL;
			q[i].size = 0;
		}
		q[i].n = 0;
	}
}

int main()
{
	work w[10];
	queue q[10];
	int work_num = 6;
	int q_num = 9;
	int a = 0;
	while (1)
	{
		cout << endl;
		cout << "pls input a number to select a function" << endl;
		cout << "1.FirstAdapt" << endl;
		cout << "2.FirstAdapt_cycle" << endl;
		cout << "3.BestFit" << endl;
		cout << "4.WorstFit" << endl;
		cout << "5.quit" << endl;

		cin >> a;
		if (a == 1)
		{
			cout << "FirstAdapt" << endl;
			ini(q, q_num);
			in(q, w, q_num, work_num);
			FirstAdapt(q, w, q_num, work_num);
			out(q, w, q_num, work_num);
		}
		else if (a == 2)
		{
			cout << "FirstAdapt_cycle" << endl;
			ini(q, q_num);
			in(q, w, q_num, work_num);
			FirstAdapt_cycle(q, w, q_num, work_num);
			out(q, w, q_num, work_num);
		}
		else if (a == 3)
		{
			cout << "BestFit" << endl;
			ini(q, q_num);
			in(q, w, q_num, work_num);
			BestFit(q, w, q_num, work_num);
			out(q, w, q_num, work_num);
		}
		else if (a == 4)
		{
			cout << "WorstFit" << endl;
			ini(q, q_num);
			in(q, w, q_num, work_num);
			WorstFit(q, w, q_num, work_num);
			out(q, w, q_num, work_num);
		}
		else if (a == 5)
		{
			break;
		}
		else
		{
			cout << "pls intput a ture number" << endl;
		}
	}
	return 0;
}