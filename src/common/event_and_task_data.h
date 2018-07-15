#ifndef _EVENT_AND_TASK_DATA_H_
#define _EVENT_AND_TASK_DATA_H_


typedef struct SYS_EVENT
{
  int evt_id;
  int task_id;
  int next_index; 
  int error_id;
  int xx_id;
  struct SYS_EVENT* next;  		
}EVENT_NOD;

typedef struct SYS_TASK
{
  int task_id;
  int index;
  int (* fun)();
  struct SYS_TASK* next;  		
}TASK_NOD;

typedef struct
{
	unsigned short hgb_bk_flg[10];
}SYS_HGB_BK_FLG;

typedef struct  
{
	unsigned  char table[50];
}SYS_FTABLE;

typedef struct  
{
	unsigned short ad_buf_1; 
	unsigned short ad_buf_2; 
	unsigned short ad_buf_3; 
	unsigned short ad_buf_4; 
	unsigned short ad_buf_5; 
	unsigned long  ad_buf[20];
}SYS_AD_BUF;

typedef struct  
{	
	unsigned  short int timer[20];
}SYS_TIMER;

typedef struct  
{
 int  Evt0190;
 int  Evt0192;
 int  Evt0196;
 int  Evt01da;
 int  Evt01f0;

 unsigned short int table[250];
}SYS_EVENT_BUF;

typedef struct
{
  unsigned short int 	ct_mail[50];
}SYS_CT_MAIL;

typedef struct
{
  unsigned short int  hgb_timer[10];
}SYS_HGB_TIMER;


typedef struct
{
	unsigned short*  sys_timer;
  unsigned char *  isa_map_addr ; 
}ISA_REMAP_ADDRESS;

typedef struct 
{
 int  Val03f2;
 int  Val0384; 
 int  Val047a; 
 int  Val0826;	//控制LED闪烁时间
 int  Val082a; 
 int  Val082c;
//继续补充中…
} SYS_RUNNING_DATA;


typedef struct
{	
	unsigned long int* s_time ;

  SYS_TIMER *        s_timer ;
  SYS_FTABLE *       s_f_tab ; 
  SYS_AD_BUF *       s_ad_buf ;
  SYS_CT_MAIL *      s_ct_mail;
  SYS_EVENT_BUF *    s_evt_buf;
  SYS_HGB_TIMER *    s_hgb_timer;
  SYS_HGB_BK_FLG*    s_hgb_bk_flg;
    
  ISA_REMAP_ADDRESS* s_base_addr;
  SYS_RUNNING_DATA*  s_running_data;
}SYS_DEV_DRV_DATA;


#endif // _EVENT_AND_TASK_DATA_H_
