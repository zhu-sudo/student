#include<stdio.h>
#include<stdbool.h>
#include"tool.h"
#include"teacher.h"
#include"student.h"
Teacher tea[T_COUNT];
Teacher t;
	
int t_position=0;
int t_count=0;
uint32_t id_a[2]={200000,300000};//教师和学生的初始工号
int index_stu=0;


//添加学生
bool t_add_stu(void)
{
		
	if (s_count >= S_COUNT)
	return false;
	printf("请选择你要添加的方式\n");
	printf("1、单个添加\n");
	printf("2、批量导入\n");
	printf("3、退出添加\n");
	char ch;
	do
	{
		scanf("%c", &ch);
		if (CHOOSE_ONE != ch && CHOOSE_TWO != ch && CHOOSE_THREE != ch)
		{
			printf("输入错误请重新输入\n\n");
		}
		
	} while (CHOOSE_ONE != ch && CHOOSE_TWO != ch && CHOOSE_THREE != ch);

	//单个添加
	if (CHOOSE_ONE == ch)
	{
		int i = 0;

		while (0 != stu[i].sex)i++;

		Student s;

		do
		{
			printf("请输入你要添加的学生的姓名\n\n");
			scanf("%s", s.name);
			
			printf("请输入你要添加的学生的性别\n\n");
			scanf(" %c", &s.sex);

		} while (!is_legalstu(s));
		printf("--------------\n");
		s.number=id_a[1]++;
		printf("学生：%s,性别:%c,学号:%d\n",s.name,s.sex,s.number);
		init_stu( &s);
		stu[i] = s;
	}
	//通过文件批量添加
	else if (CHOOSE_TWO == ch)
	{
		printf("请输入你要添加的文件的路径\n\n");
		char path[T_FILE];
		get_number(path,T_FILE);
		int cnt = 0;
		FILE* f = fopen(path, "a");
		if (NULL == f)
		{
			printf("文件路径错误!!!\n");
			return false;
		}
		int i = 0;
		while (!feof(f)) 
		{
			fscanf(f, "%s %c%d", stu[i].name,&stu[i].sex,&stu[i].number);//学生的姓名 性别和学号的批量录入
			
			if(!islegal_id(stu[i].number))
			{
				stu[i].number=id_a[1]++;
			}
				 
			init_stu(&s);
			i++;
			if (i >= s_count)
			{
			    s_count++;
			    //
			}
			if(s_count>=S_COUNT)
			{
				 full_capcity();
			}

		}
	}
	//退出
	else if (CHOOSE_THREE == ch)
	{
		printf("正在退出");
		fflush(stdout);
		usleep(1000);
		return false;
	}
	printf("添加成功----（^-^）\n\n");
	return true;
}

//查找学生
bool t_search_stu(void)
{
	printf("请选择你要查找的方式\n");
				printf("1、姓名查找\n");
				printf("2、学号查找\n");
				printf("3、退出查找\n");
				char  ch;
				do
				{
					scanf(" %c",&ch);
					if(CHOOSE_ONE!=ch&&CHOOSE_TWO!=ch&&CHOOSE_THREE!=ch)
					{
						printf("输入错误请重新输入\n\n");
					}
				}while(CHOOSE_ONE!=ch&&CHOOSE_TWO!=ch&&CHOOSE_THREE!=ch);

				//按照姓名查找
				if(CHOOSE_ONE==ch)
				{
					printf("请输入你要查找的学生的姓名\n\n");
					char name[S_NAME];
					scanf("%s",name);
					for(int i=0;i<S_COUNT;i++)
					{
						if(0==strcmp(name,stu[i].name)&&stu[i].sex!=0)
						{
							 index_stu=i; 
							 printf("查找成功----（^-^）\n\n");
							return true;
						}
					}
				}
				//按学号查找
				else if (CHOOSE_TWO==ch)
				{
					
					int number;
					do
					{
						printf("请输入你要查找的学生的学号\n\n");
						scanf("%d",&number);
						
					}while(!islegal_id(number));
					
					for(int i=0;i<S_COUNT;i++)
					{
						if(number==stu[i].number&&stu[i].sex!=0)
						{
							index_stu=i; 
							printf("查找成功----（^-^）\n\n");
							return true;
						}
					}
				}
				//退出
				else if(CHOOSE_THREE==ch)
				{
					printf("正在退出");
					fflush(stdout);
					usleep(1000);
					return false;
				}
				printf("查找失败---（'-'）!!!\n\n");
				return false;
		}


//显示查找到的学生
void t_psearch_stu(void)
{
	if(!t_search_stu()) return ;
    printf("姓名:%s ",stu[index_stu].name);
	printf("性别:%c ",stu[index_stu].sex);
	printf("学号:%d ",stu[index_stu].number);
	printf("语文:%3d ",stu[index_stu].chinese);
	printf("英语:%3d ",stu[index_stu].english);
	printf("数学:%3d\n",stu[index_stu].math);
}

//删除学生
bool t_delete_stu(void) 
{
	printf("查找你要删除的学生的信息\n");

	if (!t_search_stu())
	{
		printf("删除失败---（'-'）!!!\n\n");
		return false;
	}
    printf("您所要删除的学生信息：姓名：%s 学号:%d\n\n",stu[index_stu].name,stu[index_stu].number);
	int cnt = 1;
	int err_cnt=0;
    int numbers;

	while (cnt <= 2)
	{
		printf("请输入学号加以确认,第%d次: \n", cnt);
		scanf("%d",&numbers);
		cnt++;
		if (numbers!=stu[index_stu].number&&stu[index_stu].sex)
		{
			cnt--;
			err_cnt++;
		}
		if(err_cnt==3)
		{
			printf("学号输入错误超过三次，退出删除操作\n\n");
			return false;
		}
	}
	
	FILE* ds = fopen("downstudent.txt", "a");
	if (NULL == ds)
	{
		perror("fopen:");
		return false;
	}
  	//将失足学生打入到退学学生标表中
	fprintf(ds, "%s %c %d\n", stu[index_stu].name,
	stu[index_stu].sex, stu[index_stu].number);
	
	fclose(ds);
	stu[index_stu].sex =0;
	//更新两张表
	
	printf("删除成功----（^-^）\n\n");
	
	return true;
}

//重置学生密码
bool t_reset_stu_pass(void)
{
	printf("请选择你要重置密码的学生\n");
	if (!t_search_stu())
	{
		printf("重置密码失败!!!\n\n");
		return false;
	}
	strcpy(stu[index_stu].password, "123456");
	printf("重置为:%s\n\n","123456");
	printf("重置成功----（^-^）\n\n");
	return true;
}

//显示所有在校学生
void t_show_stu(void)
{
    int cnt=0;
	for ( int i = 0; i < S_COUNT; i++)
	{
		if (0 != stu[i].sex)
		{
			printf("姓名:%s ",stu[i].name);
			printf("性别:%s ",stu[i].sex == 'w' ? "女" : "男");
			printf("学号:%d ",stu[i].number);
			printf("语文:%d ",stu[i].chinese);
			printf("数学:%d ",stu[i].math);
			printf("英语:%d\n",stu[i].english);
			cnt++;
		}
	}
	if(!cnt)
	{
		printf("一大波学生正在赶来的路上，请老师准备接收----（^+^）\n\n");
	}
}


//录入学生成绩
bool t_import_stu_score()
{
	printf("请选择你要添加的方式\n");
	printf("1、单个录入\n");
	printf("2、退出录入\n");

	char  ch;

	do
	{
		scanf("%c", &ch);

		if (CHOOSE_ONE != ch && CHOOSE_TWO != ch)
		{
			printf("输入错误请重新输入\n");
		}
	} while (CHOOSE_ONE != ch && CHOOSE_TWO != ch);
	
	//单个录入
	if (CHOOSE_ONE == ch)
	{
		printf("请选择你要录入成绩的对象\n");

		if (!t_search_stu())
		{
			printf("录入失败\n");
			return false;
		}

		int flag = 1;

		do
		{
			flag = 0;

			printf("输入学生的语文成绩\n");
			scanf("%d", &stu[index_stu].chinese);
			if(!legal_chinese_score( stu[index_stu].chinese))
			{
			 	flag=1;
			 	continue;
			}

			printf("输入学生的英语成绩\n");
			scanf("%d", &stu[index_stu].english);
			if(!legal_english_score(stu[index_stu].english ))
			{
			 	flag=1;
			 	continue;
			}
	
			printf("输入学生的数学成绩\n");
			scanf("%d", &stu[index_stu].math);
			if(!legal_math_score( stu[index_stu].math))
			{
			 	flag=1;
			 	continue;
			}
		} while (flag);

		printf("录入成功----（^-^）\n\n");
		return true;
	}
	//退出录入
	else if (CHOOSE_TWO == ch)
	{
		printf("正在退出");
		fflush(stdout);
		usleep(1000);
		return false;
	}

	return false;
}

//显示退出学生
void t_show_drop_stu()
{
	Student s;
	FILE* f = fopen("downstudent.txt", "r");
	while (!feof(f))
	{
		fscanf(f, "%s %c %d\n", s.name,&s.sex, &s.number);
		printf("姓名:%s ",s.name);
		printf("性别:%s ",s.sex == 'w' ? "女" : "男");
		printf("学号:%d\n",s.number);
	}
	fclose(f);
}

//修改学生信息
bool t_modify_stu()
{
	printf("请输入你要修改的学生信息\n");
	if (!t_search_stu())
	{
		printf("修改失败\n");
		return false;
	}
	printf("请选择你要修改信息\n");
	printf("1、学生基础信息修改\n");
	printf("2、学生成绩修改\n");
	printf("3、退出修改\n");
	char  ch;
	do
	{
		scanf(" %c", &ch);                       //菜单界面选项的判断
		if (CHOOSE_ONE != ch && CHOOSE_TWO != ch && CHOOSE_THREE != ch)
		{
			printf("输入错误请重新输入\n");
		}
		
	} while (CHOOSE_ONE != ch && CHOOSE_TWO != ch && CHOOSE_THREE != ch);

	//学生基础信息修改
	if (CHOOSE_ONE == ch)
	{
		
		do
		{
			printf("请输入你要修改的学生的姓名\n");
			scanf("%s", stu[index_stu].name);
			
			printf("请输入你要修改的学生的性别\n");
			scanf(" %c", &stu[index_stu].sex);
			
			printf("请输入你要修改的学生的密码\n");
			get_passwd(stu[index_stu].password,S_PASS,true);
			if (!islegal_pass(stu[index_stu].password))
			{
				printf("学生密码错误\n");
				continue;
			}
					
		} while (!is_legalstu(stu[index_stu]));
		printf("修改成功----（^-^）\n\n");
	}
	//学生成绩修改
	else if (CHOOSE_TWO == ch)
	{
		int flag = 1;
		do
		{
			flag = 0;
			printf("输入学生的语文成绩\n");
			scanf("%d", &stu[index_stu].chinese);
			if(!legal_chinese_score( stu[index_stu].chinese))
			{
			 	flag=1;
			 	continue;
			}

			printf("输入学生的英语成绩\n");
			scanf("%d", &stu[index_stu].english);
			if(!legal_english_score(stu[index_stu].english ))
			{
			 	flag=1;
			 	continue;
			}
	
			printf("输入学生的数学成绩\n");
			scanf("%d", &stu[index_stu].math);
			if(!legal_math_score( stu[index_stu].math))
			{
			 	flag=1;
			 	continue;
			}
			
		} while (flag);
		printf("修改成功----（^-^）\n\n");
	}
	//退出
	else if (CHOOSE_THREE == ch)
	{
		printf("正在退出");
		fflush(stdout);
		usleep(1000);
		return false;
	}
	return false;

}

//给学生解锁
void t_unlock(void)
{
	int number;
	printf("请输入要解锁的学生学号:");
	scanf("%d",&number);
	while(true)
	{
		for(int i=0;i<S_COUNT;i++)
		{
			if(stu[i].number==number)              //改过
			{
				if(stu[i].Account_status==0)
				{
					stu[i].Account_status=1;
					printf("解锁成功----（^-^）");
					anykey_continue();
					return;
				}
				else
				{
					printf("你输入的学生状态为未锁定请重新确认！！");
					anykey_continue();
					return;
				}
			}
		}
		printf("你找到学号不存在----（*+*）");
		anykey_continue();
		return;
	}
}
