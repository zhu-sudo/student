#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<getch.h>
#include"student.h"
#include"tool.h"

Student stu[S_COUNT];
Student s;

int s_position=0;
int s_count=0;

void sorce(void)
{
	//记录排名
	int ranking=1;
	int max=-1,min=101;
	for(int i=0;i<S_COUNT;i++)
	{
		if(stu[i].sex!=0)
		{
			//计算个人总分
	 	    stu[i].sum=stu[i].math+stu[i].chinese+stu[i].english;
			//查找最大 最小
			if(stu[i].sum>max) max=stu[i].sum;
			if(stu[i].sum<min) min=stu[i].sum;
			//计算排名
			if(s.sum<stu[i].sum) ranking++;
		}
	}	
	printf("1.排名 2.平均分 3.最高分 4.最低分\n");
        printf("请输入你需要查询的内容\n");
     //成绩查询功能
	switch(getch())
	{
		case '1':printf("\n你的排名为:%d",ranking);
		anykey_continue();
		break;
		case '2':printf("\n你的平均分为:%d",s.sum/3);
		anykey_continue();
		break;
		case '3':printf("\n最高分为:%d",max);
		anykey_continue();
		break;
		case '4':printf("\n最低分为:%d",min);
		anykey_continue();
		break;
		case '5':break;
	}
}


//更改密码
void Pass(void)
{
	char pass1[S_PASS],pass2[S_PASS],pass3[S_PASS];
	for(;;)
	{
		printf("输入原密码:\n");
                get_passwd(pass1,S_PASS,true);
		//判断密码是否和登入密码相同
		if(strcmp(pass1,s.password)==0)
		{
			//输入两个要修改的密码
			printf("输入要更改的密码(6~20位密码):\n");
			get_passwd(pass2,S_PASS,true);
			printf("\n确认要修改的密码:\n");
			get_passwd(pass3,S_PASS,true);
			//判断两个密码是否合法相等
			if(islegal_pass(pass2)&&islegal_pass(pass3)&&!strcmp(pass2,pass3))
			{
				//更新结构体内容，修改密码成功跳出循环
				strcpy(s.password,pass3);
                for(int i=0;i<S_COUNT;i++)
			    {
			    	if(s.number==stu[i].number)
				    {
					   stu[i]=s;
					   stu[i].landing=1;
				    }
			    }
			    printf("修改成功，请妥善保存密码\n");
				anykey_continue();
				return;
			}
			//返回循环，重新修改
			else
			{
				printf("密码不合法或者两次密码不相同\n");
				anykey_continue();
				continue;
			}
		}
		//返回循环，重新修改
		else
	    {
    	    printf("原密码错误重新输入:\n");
			continue;
        }
    }		
}

void Allmessage(void)
{
     for(int i=0;i<S_COUNT;i++)	        
     {
         if(s.number==stu[i].number)
         {
             printf("姓名:%s 性别:%c 学号:%d 语文:%d 数学:%d 英语:%d\n",stu[i].name,stu[i].sex,stu[i].number,stu[i].chinese,stu[i].math,stu[i].english);
			anykey_continue();
         }
      }
}
