#include<stdint.h>
#include<string.h>
#include<stdio.h>
#include"tool.h"
#include"student.h"
#include"teacher.h"


extern uint32_t id_a[2];
//按任意键继续
void anykey_continue(void)
{
	stdin->_IO_read_ptr=stdin->_IO_read_end;
	printf("\n请按任意键继续...");
	getch();
}


//判断密码长度是否大于6或者小于20
//判断密码是否只包含数字和字母
//密码是否合法
bool islegal_pass(const char*pass)
{
	if (6 > strlen(pass) || strlen(pass) > 19)
	{
		return  false;
	}

	for (; *pass != '\0'; pass++)
	{
		if (!isalnum(*pass))
		return false;
	}

	return true;
}
bool islegal_id(number)                       //判断学生的学号，合法的学号就返回true
{
      if(number>=id_a[1])
      {
        printf("学号不存在\n");
        return false;
	  }
      return true;

}
bool islegal_tecid(number)                       //判断老师的工号，合法的工号就返回true
{
      if(number>=id_a[1])
      {
        printf("工号不存在\n");
        return false;
	  }
      return true;
}


																	
bool is_legalstu(Student s)                      //学生信息是否合法 合法返回true
{
	if(0==strlen(s.name)||strlen(s.name)>=20)
	{
	  printf("!!!名字格式错误,请重新输入!!!\n\n");
	  return false;
	}
	if(s.sex!='w'&&s.sex!='m')
	{
	   printf("!!!性别格式错误，请重新输入!!!\n\n");
	   return false;
	}
	return true;
	
}

//清空缓存区
void clear_stdin(void)
{
	stdin->_IO_read_ptr = stdin->_IO_read_end;
}

//从键盘获取账号
char* get_number(char* pd,size_t hope_len)
{
	clear_stdin();
    if(NULL == pd) return NULL;

    size_t index = 0;
    while(index < hope_len-1)
    {
        int32_t key_val = getch();
        if(KEY_BACKSPACE == key_val)
        {
            if(index > 0)
            {
                index--;
                printf("\b \b");
            }
        }
        else if('\n' == key_val) break;
        else
        {
            pd[index++] = key_val;
            printf("%c",key_val);
        }
    }
    pd[index] = '\0';
    printf("\n");
    clear_stdin();
    return pd;
}

//从键盘获取密码
char* get_passwd(char* pd,size_t hope_len,bool is_show)
{
	clear_stdin();
    if(NULL == pd) return NULL;

    size_t index = 0;
    while(index < hope_len-1)
    {
        int32_t key_val = getch();
        if(KEY_BACKSPACE == key_val)
        {
            if(index > 0)
            {
                index--;
                is_show ? printf("\b \b") : nil;
            }
        }
        else if('\n' == key_val) break;
        else
        {
            pd[index++] = key_val;
            is_show ? printf("*") : nil;
        }
    }
    pd[index] = '\0';
    printf("\n");
    clear_stdin();
    return pd;
}


//判断成绩是否合法,合法就输出 true,不合法输出false  ,(2020.8.8 修改 王浩波)
static bool _judge_score(int score)
{  
    
      return     LOWGRADE<=score&&score<=HIGHTGRADE;
}

//初始化密码，登陆状态，成绩等信息
void init_stu( Student *stu)
{
		sscanf("123456","%s",stu->password);
		stu->chinese=0;
		stu->math=0;
		stu->english=0;
		stu->landing=0;
		stu->Account_status=1;
}

void full_capcity()
{
			
	printf("              您添加的数量超出您所预定的系统容量！！！！\n");
	printf("              如果需要升级系统容量请拨打118-118-18-18-18\n");
	printf("              指针国际欢迎您的到来\n");
}

     //以下三个判断语文英语数学成绩是否合法
bool legal_chinese_score(int chi_score)
{
	if(!_judge_score(chi_score))
	{
		printf("语文成绩非法!!!\n\n");
		return false;
	}
	return true;
}                  

bool legal_english_score(int eng_score)
{
	if(!_judge_score(eng_score))
	{
		printf("英语成绩非法!!!\n\n");
		return false;
	}
	return true;
}

bool legal_math_score(int mat_score)
{
	if(!_judge_score(mat_score))
	{
		printf("数学成绩非法!!!\n\n");
		return false;
	}
	return true;
}
void init_storage()                //必要时刻清除数据库
{
	FILE *ftw=fopen("teacher.txt","w");
	FILE *fsw=fopen("student.txt","w");
	FILE *fstw=fopen("str_tec.txt","w");
	//memset(s)
	fprintf(fstw,"%d %d",200000,300000);
	
	fclose(ftw);
	fclose(fsw);
	fclose(fstw);
	
	printf("-------------------老师和学生的数据以被清空,请重新导入信息!!!\n\n");
	printf("-------------------老师和学生的工号已经被初始化！！！\n\n");
	printf("-------------------如果有任何问题，请联系我们指针国际的工作人员\n\n");
	printf("-------------------电话：18-18-1818-18\n\n");
}

