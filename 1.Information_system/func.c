#include "./func.h"
void sw_ch(struct infor *list, FILE *fd);

void inter_head()				//顶层界面
{
	printf("\n\n\t\t\tWelcome\n\n");
	printf("=======================================");
	printf("=================================\n");
	printf(" Numer\t   From\t\tTo\t    Stay\t  Arrive\tPrince\n");

}

void inter_tail()					//底层界面
{
	printf("==================================");
	printf("======================================\n");
	printf("   [i]Insert [p]Print [f]Find ");
	printf("[s]Sort [d]Delete [S]Save [H]Help [q]Quit\n");
	printf("======================================");
	printf("==================================\n");
	printf("Please enter the function you need\n");

}

int jud_fd(FILE *fd)
{
	if(fd == NULL)
	{
		printf("File open error!\n");
		return 1;
	}
}

int jud_list(struct infor *list)		//为头节点赋值
{
	if(list != NULL)
	{
		list->next = list;
		list->prev = list;

		return 0;
	}

	printf("\nERROR!\n");

	return 1;
}

struct infor *new_node()			//为新节点分配内存
{
	struct infor *node =(struct infor *)malloc(sizeof(struct infor));

	if(node != NULL)
	{
		node->next = NULL;
		node->prev = NULL;

		return node;
	}
	else
	{
		printf("\nNode is NULL!!!!!\n");
	}
}

void input(struct infor *list)			//输入插入节点的信息
{
	printf("Please enter number of flight\n");
	scanf("%s", list->prev->num);
	printf("Please enter the place of departure\n");
	scanf("%s", list->prev->from);
	printf("Please enter the destination\n");
	scanf("%s", list->prev->to);
	printf("Please enter departure time\n");
	scanf("%s", list->prev->date);
	printf("Please enter arrival time\n");
	scanf("%s", list->prev->arr);
	printf("Please enter prince\n");
	scanf("%d", &list->prev->pri);
	printf("\nInput Complete\n");
}

int insert_tail(struct infor *list)		//从尾部插入新节点
{
	struct infor *node = new_node();
	
	if(node != NULL)
	{
		node->next = list;
		node->prev = list->prev;
		list->prev->next = node;
		list->prev = node;
		input(list);

		return 0;
	}
	else
	{
		printf("Inser is error\n");

		return 1;
	}
}

void output(struct infor *list)			//显示各节点的信息
{
	inter_head();
	struct infor *p = list;
	
	while(p->prev != list)
	{
		printf(" %-10s %-12s %-11s %-13s %-13s %-6d\n", 
				p->prev->num,
				p->prev->from,
				p->prev->to,
				p->prev->date,
				p->prev->arr,
				p->prev->pri);

		p = p->prev;
	}

	inter_tail();
}

void input_file(struct infor *list, FILE *fd)		//读取文件信息
{
	fgetc(fd);
	while(feof(fd) ==0)
	{
		struct infor *list1 =(struct infor *)malloc(sizeof(struct infor));
		struct infor *tmp = list;
		fscanf(fd, "%s", list1->num);
		fscanf(fd, "%s", list1->from);
		fscanf(fd, "%s", list1->to);
		fscanf(fd, "%s", list1->date);
		fscanf(fd, "%s", list1->arr);
		fscanf(fd, "%d", &list1->pri);
	
		if(NULL != list1 )
		{
			list1->next = tmp;
			list1->prev = tmp->prev;
			tmp->prev->next = list1;
			tmp->prev = list1;
		}

		fgetc(fd);
	}
}


void save(struct infor *list)
{
	FILE *fd1 = fopen(PATH, "w+");
	struct infor *p = list;
	while(p->prev != list)
	{
		fprintf(fd1, " %-10s %-12s %-11s %-13s %-13s %-6d\n", 
					p->prev->num,
					p->prev->from,
					p->prev->to,
					p->prev->date,
					p->prev->arr,
					p->prev->pri);

		p =	p->prev;
	}
	fflush(fd1);
}

int delete_node(struct infor *list)	//删除节点
{
	struct infor *p = list;
	char number[10];

	printf("Enter the number you want to delete\n");
	scanf("%s", number);

	if(list->prev == list)			//判断是否有节点
	{
		printf("ERROR_DELETE\n");
		 return 1;
	}

	while(p->prev != list)
	{
		if(strcmp(p->prev->num, number) == 0)
		{
			printf("OK\n");
			struct infor *del = p->prev;
			p->prev->prev->next = p;
			p->prev = p->prev->prev;
			
			free(del);
		}
		else
		{
			p = p->prev;
		}
	}

	return 0;
	
}

void find(struct infor *list)	//查找
{
	struct infor *temp = list;
	char ch[10];
	
	printf("Please enter the search flight number\n");
	scanf("%s", ch);

	while(temp->prev != list)
	{
		if(strcmp(temp->prev->num, ch) == 0)
		{
			printf("\nNumer\t   From\t\tTo\t    Stay\t  Arrive\tPrince\n");
			printf(" %-10s %-12s %-11s %-13s %-13s %-6d\n", 
					temp->prev->num,
					temp->prev->from,
					temp->prev->to,
					temp->prev->date,
					temp->prev->arr,
					temp->prev->pri);
			break;
		}
		else 
		{
			temp = temp->prev;
		}
	}
}

int sort(struct infor *list)		//排序
{
	struct infor *p;
	struct infor *q;
	struct infor *temp;
	int number;

	printf("\n\t\tWelcome to the layout function\t\n");
sw_sort:
	printf("[1]Prices from big to small\n");
	printf("[2]Number from big to small\n");
	printf("[3]Return interface\n");
	scanf("%d", &number);

	if(number == 1)		//按数字从大到小排列
	{
		for(p=list; p->prev != list; p=p->prev)
		{
			for(q=p->prev; q->prev != list;)
			{
				if((q->prev->pri) > (p->prev->pri))
				{
					temp = p->prev;
					p->prev = q->prev;
					q->prev = q->prev->prev;
					q->prev->next = q;
					p->prev->prev = temp;
					temp->next = p->prev;
					temp->next->next = p;
				}
				else
				{
					q = q->prev;
				}
			}
		}
	}
	else if(number == 2)	//编号从大到小排列
	{
		for(q=list; p->prev != list; p=p->prev)
		{
			for(q=p->prev; q->prev != list;)
			{
				if(strcmp(q->prev->num, p->prev->num) > 0)
				{
					temp = p->prev;
					p->prev = q->prev;
					q->prev = q->prev->prev;
					q->prev->next = q;
					p->prev->prev = temp;
					temp->next = p->prev;
					temp->next->next = p;
				}
				else if(strcmp(q->prev->num, p->prev->num) == 0)
				{
					q = q->prev;
				}
				else
				{
					q = q->prev;
				}
			}	
		}
	}
	else if(number == 3)		//退出排序
	{
		return 0;
	}
	else
	{
		printf("Input error!!\n");
		printf("Please enter one more time\n");
		goto sw_sort;
	}

	return 0;

}

void quit(struct infor *list, FILE *fd)	//退出界面
{
	struct infor *p = list;

	while(p->prev != list)
	{
		p = p->prev;
		free(p->next);
	}
	free(p);
	fclose(fd);
	exit(0);

}

void sw_num()			//暂停
{
	printf("功能完成");
	printf("暂停一下！\n");
	while(getchar() != '\n');
	
	sleep(1);
}

void sw_ch(struct infor *list, FILE *fd)		//判断
{
	char ch;
	output(list);
	scanf("%c", &ch);

	switch(ch)
	{
		case 'i':insert_tail(list);
				 sw_num();
				 sw_ch(list, fd);

		case 'p':sw_num();
				 sw_ch(list, fd);
		
		case 'f':find(list);
				 sw_num();
				 sw_ch(list, fd);

		case 's':sort(list);
				 sw_num();
				 sw_ch(list, fd);

		case 'd':delete_node(list);
				 sw_num();
				 sw_ch(list, fd);

		case 'S':save(list);
				 sw_num();
				 sw_ch(list, fd);

		case 'H':printf("木有\n");
				 sw_num();
				 sw_ch(list, fd);

		case 'q':quit(list, fd);

		default	:printf("input ERROR!\n");
				 sw_num();
				 sw_ch(list, fd);
				 break;
	}
}

