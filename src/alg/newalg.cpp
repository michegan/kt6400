#include <math.h>
#include <QTime>
#include <QtDebug>

#include "dma.h"
#include "paras.h"
#include "newalg.h"
#include "paraname.h"


// 算法
namespace Alg
{
    //采样数据结构定义
    typedef struct
    { 
        unsigned char  graph_type;

        unsigned short graph_buf[256];
        unsigned char  buf[257];
        unsigned short point_sum;
        unsigned short ad_count_max;
        unsigned char  x;
        unsigned short samp_prc_flg[12]; 

        unsigned short xy333;
        unsigned short xy335;
        unsigned short xy337;
        unsigned short xy339;
        unsigned short xy33b;

        float          compare_flg;
        int            add_res;
    }DATA_SAMPLING;

    typedef struct _SYSRESDATA
    {
        char  abnormity;   //测试异常

        int   wr_graph_gene; //wbc,rbc图象因子

        int      wbc;
        int      plym;
        int      pmid;
        int      pgran;
        int      vlym;
        int      vmid;
        int      vgran;

        int      rbc;
        int      mcv;
        int      hct;
        int      rdw_cv;
        int      rdw_sd;

        int      plt;
        int      mpv;
        int      pdw;
        int      pct;
        int      plcr;

        int   hgb;
        int   mch;
        int   mchc;

        int   wbc_division_begin; //不为0的下标
        int   lym_division_begin;
        int   mid_division_begin;
        int   wbc_division_end;
        int   rbc_division_begin; //不为0的下标,rbc不存在划分，用来存储直方下标不为0的标值   
        int   rbc_division_end;
        int   plt_division_begin;
        int   plt_division_end;

    }SYSRESDATA;

    //added lzj   用来从人工校准数据库中读出当前样本类型的人工参数值和厂家参数值的结构体
    typedef struct _SYSCALVAL
    {
        float   cl_WBC;
        float   cl_RBC;
        float   cl_HGB;
        float   cl_MCV;
        float   cl_PLT;
    }SYSCALVAL;

    //数据库表KT6200_System_Info
    typedef struct _SETSYSINFO_DLG_HANDLE 
    {
        //int     diluent;
        //int     lyse;
        float        lym;
        float        mid;
        int        lym_line;
        int       mid_line;
    }SETSYSINFO_DLG_HANDLE;


    //数据缓冲区
    typedef struct _SYSSAMPLINGBUF
    {     
         unsigned char  WbcHisGraph[256];
         unsigned char  RbcHisGraph[256];
         unsigned char  PltHisGraph[256];
     
    }SYSSAMPLINGBUF;


    typedef struct _RESULTS_COEFFICIENT
    {
        float LYM_5; //LYM%
        float MID_5; //MID%
        float LYM_3; //LYM#
        float MID_3; //MID#
        float HCT;
        float MCH;
        float MCHC;
        float RDW_SD;
        float RDW_CV;
        float MPV;
        float PDW;
        float PCT;
        float PLCR;
    }RESULTS_COEFFICIENT;

    typedef struct _MAINWINDOWDATA
    {
        unsigned char          Point_WBC[256];
        unsigned char          Point_RBC[256];
        unsigned char          Point_PLT[128];
    }MAINWINDOWDATA;

    //维护界面的变量
    typedef struct _MAINTENANCE_VAL
    {
        // [L1HIGH] VARCHAR(10)
        // [G1LOW] VARCHAR(10)
        // [L2HIGH] VARCHAR(10)
        // [G2LOW] VARCHAR(10)
        // [R1] VARCHAR(10) UNIQUE
        // [R2] VARCHAR(10)
        // [R3] VARCHAR(10)
        // [R4] VARCHAR(10)
        // [WBC] VARCHAR(10)
        // [RBC] VARCHAR(10)
        // [STEPA1] VARCHAR(10)
        // [STEPA2] VARCHAR(10)
        // [STEPB] VARCHAR(10)
        // [STEPC1] VARCHAR(10)
        // [STEPC2] VARCHAR(10)
        // [STEPC3] VARCHAR(10)
        // [STEPC4] VARCHAR(10)
        // [STEPC5] VARCHAR(10)
        // [STEPC6] VARCHAR(10)
        // [STEPC7] VARCHAR(10)
        // [STEPD1] VARCHAR(10)
        // [STEPD2] VARCHAR(10)
        // [STEPD3] VARCHAR(10)
        // [STEPD4] VARCHAR(10)
        // [STEPD5] VARCHAR(10)
        // [STEPD6] VARCHAR(10)
        // [STEPD7] VARCHAR(10)
        // [STEPD8] VARCHAR(10)
        // [STEPD9] VARCHAR(10)
        // [STEPD10] VARCHAR(10)
        int   maintenanceVal[30];
    }MAINTENANCE_VAL;

    static Modes            s_modes;

    static DATA_SAMPLING    wbc_data;
    static DATA_SAMPLING    rbc_data;
    static DATA_SAMPLING    plt_data;

    static int WBC_err_id = 0; // WBC堵孔
    static int RBC_err_id = 0; // RBC堵孔
    static int PLT_err_id = 0; // RBC堵孔

    static SYSCALVAL   syscalval;
    static SYSRESDATA  SysTestResValBuf; // 算法参数结果

    static int conslt_array_1[11][2]; //静脉血参考区间
    static int conslt_array_2[11][2]; //静脉血参考区间

    static int conslt_array_3[11][2]; //末梢血参考区间
    static int conslt_array_4[11][2]; //末梢血参考区间

    static int conslt_array_5[11][2]; //预稀释参考区间
    static int conslt_array_6[11][2]; //预稀释参考区间

    static int val_2522 = 0;
    static int lym_division  = 0; 
    static int mid_division  = 0;

    static unsigned short t200 = 0;
    static unsigned short t204 = 0;

    static unsigned short int val_3564 = 0; // HGB通道故障 0 1 2
    static unsigned short int val_34ad = 0; // val_34ad = pEvtBuf->table[69];

    static SETSYSINFO_DLG_HANDLE SetSysInfoData;
    static SYSSAMPLINGBUF SysADBufData;
    static MAINWINDOWDATA   mainWindowData;
    static MAINTENANCE_VAL   maintenance_val;

    // 密码8857进行设置
    RESULTS_COEFFICIENT results_coefficient = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};



    void Copy_Sample_Data( char* pSrc,char* pDes,int len )
    {
        memcpy( pDes,pSrc,len );
    }

    void __SetBit(int flag ,int bit , char* value)
    {
        char temp ;
    
        temp = ~(0x01 << bit) ;
    
        if( flag == 0 )
        {
            *value = *value & temp ;
        }
        else
        {
            *value = *value | ~temp;
        }
    }

    void Init_SysInfo()
    {
        SetSysInfoData.lym = 1;
        SetSysInfoData.mid = 1;
        SetSysInfoData.lym_line = 90;
        SetSysInfoData.mid_line = 120;
    }

    void Init_SysCalVal()
    {
        syscalval.cl_WBC = 1;
        syscalval.cl_RBC = 1;
        syscalval.cl_HGB = 1;
        syscalval.cl_MCV = 1;
        syscalval.cl_PLT = 1;
    }

    void Init_Consultion_Template_Data()
    { 
        int iCount = 0;
        int jCount = 0;
        int max = 0x015e ;
        int hypo_max = 0x0154;

        for( iCount = 0;iCount < 0x000B;iCount++  )
        {
            for( jCount = 0;jCount < 0x0002;jCount++  )    
            {
                if( !jCount )
                {
                    conslt_array_1[iCount][jCount] = hypo_max - (iCount)*0x000A;
                    conslt_array_3[iCount][jCount] = hypo_max - (iCount)*0x000A;
                    conslt_array_5[iCount][jCount] = hypo_max - (iCount)*0x000A;
                }
                else
                {
                    conslt_array_1[iCount][jCount] = max - (iCount)*0x000A;
                    conslt_array_3[iCount][jCount] = max - (iCount)*0x000A;
                    conslt_array_5[iCount][jCount] = max - (iCount)*0x000A;
                }   
            }            
        }

        conslt_array_2[0][0]  = 0x0000;
        conslt_array_2[0][1]  = 0x0000;
        conslt_array_2[1][0]  = 0x0001;
        conslt_array_2[1][1]  = 0x0002;
        conslt_array_2[2][0]  = 0x0002;
        conslt_array_2[2][1]  = 0x0004;    
        conslt_array_2[3][0]  = 0x0003;
        conslt_array_2[3][1]  = 0x0006;
        conslt_array_2[4][0]  = 0x0003;
        conslt_array_2[4][1]  = 0x0008;
        conslt_array_2[5][0]  = 0x0004;
        conslt_array_2[5][1]  = 0x0009;
        conslt_array_2[6][0]  = 0x0004;
        conslt_array_2[6][1]  = 0x000B;
        conslt_array_2[7][0]  = 0x0004;
        conslt_array_2[7][1]  = 0x000C;
        conslt_array_2[8][0]  = 0x0005;
        conslt_array_2[8][1]  = 0x000E;  
        conslt_array_2[9][0]  = 0x0005;
        conslt_array_2[9][1]  = 0x000F; 
        conslt_array_2[10][0] = 0x0005;
        conslt_array_2[10][1] = 0x0010; 


        conslt_array_4[0][0]  = 0x0000;
        conslt_array_4[0][1]  = 0x0000;
        conslt_array_4[1][0]  = 0x0001;
        conslt_array_4[1][1]  = 0x0002;
        conslt_array_4[2][0]  = 0x0002;
        conslt_array_4[2][1]  = 0x0004;    
        conslt_array_4[3][0]  = 0x0003;
        conslt_array_4[3][1]  = 0x0006;
        conslt_array_4[4][0]  = 0x0003;
        conslt_array_4[4][1]  = 0x0008;
        conslt_array_4[5][0]  = 0x0004;
        conslt_array_4[5][1]  = 0x0009;
        conslt_array_4[6][0]  = 0x0004;
        conslt_array_4[6][1]  = 0x000B;
        conslt_array_4[7][0]  = 0x0004;
        conslt_array_4[7][1]  = 0x000C;
        conslt_array_4[8][0]  = 0x0005;
        conslt_array_4[8][1]  = 0x000E;  
        conslt_array_4[9][0]  = 0x0005;
        conslt_array_4[9][1]  = 0x000F; 
        conslt_array_4[10][0] = 0x0005;
        conslt_array_4[10][1] = 0x0010; 

        conslt_array_6[0][0]  = 0x0000;
        conslt_array_6[0][1]  = 0x0000;
        conslt_array_6[1][0]  = 0x0001;
        conslt_array_6[1][1]  = 0x0002;
        conslt_array_6[2][0]  = 0x0001;
        conslt_array_6[2][1]  = 0x0004;    
        conslt_array_6[3][0]  = 0x0002;
        conslt_array_6[3][1]  = 0x0006;
        conslt_array_6[4][0]  = 0x0002;
        conslt_array_6[4][1]  = 0x0008;
        conslt_array_6[5][0]  = 0x0003;
        conslt_array_6[5][1]  = 0x0009;
        conslt_array_6[6][0]  = 0x0003;
        conslt_array_6[6][1]  = 0x000B;
        conslt_array_6[7][0]  = 0x0003;
        conslt_array_6[7][1]  = 0x000C;
        conslt_array_6[8][0]  = 0x0004;
        conslt_array_6[8][1]  = 0x000E;  
        conslt_array_6[9][0]  = 0x0004;
        conslt_array_6[9][1]  = 0x000F; 
        conslt_array_6[10][0] = 0x0004;
        conslt_array_6[10][1] = 0x0010;
    }


    void init_SysresData()
    {
        SysTestResValBuf.abnormity = 0;   //测试异常

        SysTestResValBuf.wr_graph_gene = 0; //wbc,rbc图象因子

        SysTestResValBuf.wbc = 0;
        SysTestResValBuf.plym = 0;
        SysTestResValBuf.pmid = 0;
        SysTestResValBuf.pgran = 0;
        SysTestResValBuf.vlym = 0;
        SysTestResValBuf.vmid = 0;
        SysTestResValBuf.vgran = 0;

        SysTestResValBuf.rbc = 0;
        SysTestResValBuf.mcv = 0;
        SysTestResValBuf.hct = 0;
        SysTestResValBuf.rdw_cv = 0;
        SysTestResValBuf.rdw_sd = 0;

        SysTestResValBuf.plt = 0;
        SysTestResValBuf.mpv = 0;
        SysTestResValBuf.pdw = 0;
        SysTestResValBuf.pct = 0;
        SysTestResValBuf.plcr = 0;

        SysTestResValBuf.hgb = 0;
        SysTestResValBuf.mch = 0;
        SysTestResValBuf.mchc = 0;

        SysTestResValBuf.wbc_division_begin = 0; //不为0的下标
        SysTestResValBuf.lym_division_begin = 0;
        SysTestResValBuf.mid_division_begin = 0;
        SysTestResValBuf.wbc_division_end = 0;
        SysTestResValBuf.rbc_division_begin = 0; //不为0的下标,rbc不存在划分，用来存储直方下标不为0的标值   
        SysTestResValBuf.rbc_division_end = 0;
        SysTestResValBuf.plt_division_begin = 0;
        SysTestResValBuf.plt_division_end = 0;
    }

    void Init_Sys_Sampling_Data()
    {
        int iCount;

        for( iCount = 0;iCount < 12;iCount++ )
        {
            wbc_data.samp_prc_flg[iCount] = 0;
            rbc_data.samp_prc_flg[iCount] = 0;
            plt_data.samp_prc_flg[iCount] = 0;
        }

        SysTestResValBuf.abnormity = 0x00;

        rbc_data.graph_type = 0x00;
        rbc_data.point_sum  = 0x0100;
        rbc_data.x          = 0x08;

        rbc_data.samp_prc_flg[8] = 0x0034;     
        rbc_data.samp_prc_flg[9] = 0x0034;    
        rbc_data.samp_prc_flg[10] = 0x0034;
        rbc_data.xy335 = 0x0012;
        rbc_data.xy337 = 0x0012;
        rbc_data.xy339 = 0x0012;

        wbc_data.graph_type = 0x01;
        wbc_data.point_sum  = 0x0100;
        wbc_data.x          = 0x08;

        wbc_data.samp_prc_flg[8] = 0x0046;    //0x0046 
        wbc_data.samp_prc_flg[9] = 0x0046;    
        wbc_data.samp_prc_flg[10] = 0x0046;
        wbc_data.xy335 = 0x0014; //0x0014
        wbc_data.xy337 = 0x0014;
        wbc_data.xy339 = 0x0014; 


        plt_data.graph_type = 0x02;
        plt_data.point_sum  = 0x0080;
        plt_data.x          = 0x04;

        plt_data.samp_prc_flg[8] = 0x0030;     
        plt_data.samp_prc_flg[9] = 0x0030;    
        plt_data.samp_prc_flg[10] = 0x0030;
        plt_data.xy335 = 0x0014;
        plt_data.xy337 = 0x0014;
        plt_data.xy339 = 0x0014;

        wbc_data.add_res = 0;
        rbc_data.add_res = 0;
        plt_data.add_res = 0;

        wbc_data.xy333   = 0;
        rbc_data.xy333   = 0;   
        plt_data.xy333   = 0;

        wbc_data.xy33b   = 0;
        rbc_data.xy33b   = 0;   
        plt_data.xy33b   = 0; 

        for( iCount = 0;iCount < 256;iCount++ )
        {
            wbc_data.buf[iCount] = 0;    
            rbc_data.buf[iCount] = 0;
            plt_data.buf[iCount] = 0;

            wbc_data.graph_buf[iCount] = 0;
            rbc_data.graph_buf[iCount] = 0;
            plt_data.graph_buf[iCount] = 0; 
        }

        wbc_data.ad_count_max = 0;
        rbc_data.ad_count_max = 0;
        plt_data.ad_count_max = 0;
    }


    void Pulse_Statistical_Process( DATA_SAMPLING* data,unsigned char* pWbcDataBuf,long data_len )
    {
        int iCount = 0; 
        int jCount = -1;
        int index = 0;
        int flg = -1;
        float tmp = 0.0;

        int iPulse12 = 0;
        int    iPulse23 = 0;
        int    iPulse31 = 0;

        DATA_SAMPLING stack_data;

        int iPeakPos;

        int Data_iPulse1 = 0;
        int Data_iPulse2 = 0;
        int Data_iPulse3 = 0;

        Copy_Sample_Data ((char*)data,(char*)&stack_data,sizeof( DATA_SAMPLING ) );



        if( data_len != 0 )
        {
            for( iCount = 0;iCount < data_len ;iCount++ )
            {
                //2012-08-25
                if(iCount == 3145728)
                    Data_iPulse1 = stack_data.add_res;
                else if(iCount == 6291456)
                    Data_iPulse2 = stack_data.add_res - Data_iPulse1;
                else if(iCount == 9437184)
                    Data_iPulse3 = stack_data.add_res - Data_iPulse2 - Data_iPulse1;

                if(pWbcDataBuf[iCount] < 2)
                    continue;

                if( stack_data.samp_prc_flg[1] == 0x0000 )
                    if( iCount < 0x0003 )
                    {
                        if( iCount == 0x0002 )
                        {
                            stack_data.samp_prc_flg[1] = 0x0001;    
                        }
                        else
                        {
                            continue;    
                        }
                    }

                        if( (unsigned char )pWbcDataBuf[iCount] > (unsigned char )pWbcDataBuf[iCount - 1] )
                        {
                            if( (unsigned char )pWbcDataBuf[iCount - 1] > (unsigned char )pWbcDataBuf[iCount - 2] )
                                if( ((unsigned char )pWbcDataBuf[iCount] - (unsigned char )pWbcDataBuf[iCount - 2]) > 0x0003 )
                                {
                                    if( stack_data.samp_prc_flg[0] == 0x0000 )
                                    {
                                        stack_data.samp_prc_flg[2]    = (unsigned short)pWbcDataBuf[iCount - 2];//脉冲开始点值
                                        stack_data.samp_prc_flg[3] = 0x0002;//脉冲宽度
                                        stack_data.samp_prc_flg[11] = stack_data.samp_prc_flg[3];//上升缘脉冲点个数
                                        stack_data.samp_prc_flg[0]  = 0x0001;//脉冲识别状态标志
                                        stack_data.samp_prc_flg[6]  = 0x0001;//脉冲结束标志
                                        stack_data.samp_prc_flg[7]  = 0x0000;//脉冲准备结束标志
                                        stack_data.samp_prc_flg[5]  = (unsigned short)pWbcDataBuf[iCount];//脉冲峰值点值
                                        stack_data.samp_prc_flg[4]  = iCount;//当前位置 
                                        iPeakPos = iCount;

                                    }    
                                }
                        }

                        if( stack_data.samp_prc_flg[0] != 0x0001 )//脉冲识别状态标志
                        {
                            continue;    
                        }
                        else
                        {    //峰值检测
                            if( (unsigned short)pWbcDataBuf[iCount] >= stack_data.samp_prc_flg[5] )  
                            {
                                if(  stack_data.samp_prc_flg[6] == 0x0001 )
                                {
                                    stack_data.samp_prc_flg[5]  =     (unsigned short)pWbcDataBuf[iCount];//脉冲峰值点值
                                    stack_data.samp_prc_flg[4]  = iCount;//当前位置 
                                    stack_data.samp_prc_flg[6]  = 0x0001;//脉冲结束标志
                                    stack_data.samp_prc_flg[7]  = 0x0000;//脉冲准备结束标志
                                    stack_data.samp_prc_flg[3]++;//脉冲宽度
                                    stack_data.samp_prc_flg[11] = stack_data.samp_prc_flg[3];//上升缘脉冲点个数
                                    iPeakPos = iCount;
                                    continue;
                                }

                            }    
                            //谷值检测
                            if( (unsigned char )pWbcDataBuf[iCount] <(unsigned char ) pWbcDataBuf[iCount - 1] )
                            {
                                if(  stack_data.samp_prc_flg[6] == 0x0001 )
                                {
                                    stack_data.samp_prc_flg[3]++;//脉冲宽度
                                    stack_data.samp_prc_flg[7] = 0x0000;    
                                    if((unsigned char ) pWbcDataBuf[iCount - 1] < (unsigned char )pWbcDataBuf[iCount - 2] )
                                    {
                                        stack_data.samp_prc_flg[7] = 0x0001;//脉冲准备结束标志 下降标志
                                    }
                                    continue;
                                }

                            }

                            if( (unsigned char )pWbcDataBuf[iCount] < (unsigned char )pWbcDataBuf[iCount - 1] )
                            {
                                continue;    
                            }
                            else //出现拐点
                            {
                                if( stack_data.samp_prc_flg[7] != 0x0001 )    
                                {
                                    continue;    
                                }
                                else
                                {
                                    stack_data.samp_prc_flg[0] = 0x0000;//脉冲识别状态标志
                                    stack_data.samp_prc_flg[6] = 0x0000;
                                    stack_data.samp_prc_flg[7] = 0x0000;
                                    stack_data.xy333 = ( unsigned short )pWbcDataBuf[iCount - 1];//脉冲结束点值

                                    if( stack_data.samp_prc_flg[2] <= 0x0032 )
                                    {                  
                                        if( stack_data.samp_prc_flg[2] <= 0x001e ) //1e
                                        {
                                            if( stack_data.samp_prc_flg[5] - stack_data.samp_prc_flg[2] <= 0x0000a )
                                            {
                                                jCount = 0;          
                                            }
                                            else
                                            {
                                                if( stack_data.samp_prc_flg[5] - stack_data.xy333 <= 0x000a )
                                                {
                                                    jCount = 0;                                                 
                                                }
                                                else
                                                {
                                                    jCount = 1;    
                                                }
                                            }                         
                                        }
                                        else
                                        {
                                            if( stack_data.samp_prc_flg[2] <= 0x0032 )     
                                            {
                                                if( stack_data.samp_prc_flg[5] - stack_data.samp_prc_flg[2] > 0x0014 )
                                                {
                                                    if( stack_data.samp_prc_flg[5] - stack_data.xy333 > 0x0010 )
                                                    {
                                                        jCount = 1;
                                                    }
                                                    else
                                                    {
                                                        if( stack_data.samp_prc_flg[5] - stack_data.samp_prc_flg[2]  <= 0x0010 )
                                                        {
                                                            jCount = 0;                              
                                                        }
                                                        else
                                                        {
                                                            if( stack_data.samp_prc_flg[5] - stack_data.xy333  <= 0x0014 )    
                                                            {
                                                                jCount = 0; 
                                                            }
                                                            else
                                                            {
                                                                jCount = 1;    
                                                            }
                                                        }     
                                                    }                            
                                                }
                                                else
                                                {
                                                    if( stack_data.samp_prc_flg[5] - stack_data.samp_prc_flg[2]  <= 0x0010 )
                                                    {
                                                        jCount = 0;
                                                    }
                                                    else
                                                    {
                                                        if( stack_data.samp_prc_flg[5] - stack_data.xy333  <= 0x0014 )    
                                                        {
                                                            jCount = 0;
                                                        }
                                                        else
                                                        {
                                                            jCount = 1;    
                                                        }
                                                    }                                 
                                                }                        
                                            }
                                            else
                                            {
                                                if( stack_data.samp_prc_flg[5] - stack_data.samp_prc_flg[2] <= 0x000a )
                                                { 
                                                    jCount = 0;
                                                }
                                                else
                                                {
                                                    if( stack_data.samp_prc_flg[5] - stack_data.xy333 <= 0x000a )
                                                    {
                                                        jCount = 0;
                                                    }
                                                    else
                                                    {
                                                        jCount = 1;    
                                                    }
                                                }    
                                            }
                                        }                                                                           
                                    }
                                    else
                                    {
                                        if( stack_data.samp_prc_flg[5] - stack_data.samp_prc_flg[2] <= 0x0016 )  
                                        {
                                            if( stack_data.samp_prc_flg[5] - stack_data.samp_prc_flg[2] <= 0x0012 ) 
                                            {
                                                jCount = 0;
                                            }
                                            else
                                            {
                                                if( stack_data.samp_prc_flg[5] - stack_data.xy333 <= 0x0016 )  
                                                {  
                                                    jCount = 0;    
                                                }
                                                else
                                                {
                                                    jCount = 1;    
                                                }
                                            }
                                        }
                                        else
                                        { 
                                            if( stack_data.samp_prc_flg[5] - stack_data.xy333 > 0x0012 ) 
                                            {
                                                jCount = 1;
                                            }
                                            else
                                            {
                                                if( stack_data.samp_prc_flg[5] - stack_data.samp_prc_flg[2] <= 0x0012 ) 
                                                {  
                                                    jCount = 0;
                                                } 
                                                else
                                                {
                                                    if( stack_data.samp_prc_flg[5] - stack_data.xy333 <= 0x0016 )  
                                                    {
                                                        jCount = 0;    
                                                    }
                                                    else
                                                    {
                                                        jCount = 1;    
                                                    }
                                                }
                                            } 
                                        }        
                                    }

                                }
                            }             
                        }
                        //上升斜率
                        tmp = (stack_data.samp_prc_flg[5] - stack_data.samp_prc_flg[2])/( stack_data.samp_prc_flg[11]*1.0 );
                        if((tmp<1.1)||(fabs(tmp - 1.1) < 0.0000001))
                        { 
                            jCount = 0;          
                        }
                        else
                        {    //下降斜率
                            tmp = (stack_data.samp_prc_flg[5] - stack_data.xy333)/((stack_data.samp_prc_flg[3] - stack_data.samp_prc_flg[11])*1.0) ;
                            if((tmp<1.1)||(fabs(tmp - 1.1) < 0.0000001))
                            {  
                                jCount = 0;  
                            }
                        }

                        if( stack_data.samp_prc_flg[5] <= 0x0046 )
                        {
                            if( stack_data.samp_prc_flg[5] <= 0x001e )
                            {
                                index = 2;
                            } 
                            else
                            {
                                if( stack_data.samp_prc_flg[5] > 0x0046 )
                                {
                                    index = 2;    
                                }
                                else
                                {
                                    index = 1;
                                }
                            }    
                        }
                        else
                        {
                            index = 0;
                        }

                        if( stack_data.samp_prc_flg[8 + index] <= stack_data.samp_prc_flg[3] )
                        {
                            flg    = 0;
                            jCount = 0;     
                        }
                        else
                        {
                            if( *(&(stack_data.xy335) + index) > stack_data.samp_prc_flg[3] ) ////
                            {
                                flg    = 0;
                                jCount = 0; 
                            }
                            else
                            {
                                flg    = 1;                 
                            }
                        }

                        if( stack_data.samp_prc_flg[2] >= 0x001a )
                        {
                            if( stack_data.xy333 >= 0x001a )  
                            { 
                                jCount = 0;    
                            }      
                        }

                        if(stack_data.graph_type == 2)
                            if(stack_data.samp_prc_flg[5] > 140 || stack_data.samp_prc_flg[5] < 10)
                                jCount = 0;

                        if( jCount != 1 )
                        {
                            if( (stack_data.samp_prc_flg[5] - stack_data.samp_prc_flg[2]) > 0x000a ) 
                                if( (stack_data.samp_prc_flg[5] - stack_data.xy333) < 0x001e ) 
                                    if( flg == 1 )
                                    {
                                        stack_data.samp_prc_flg[3]++;
                                        stack_data.samp_prc_flg[0] = 0x0001;
                                        stack_data.samp_prc_flg[6] = 0x0001;
                                        stack_data.samp_prc_flg[7] = 0x0001;

                                        continue;
                                    }
                                    stack_data.samp_prc_flg[0] = 0x0000;
                                    stack_data.samp_prc_flg[6] = 0x0000;
                                    stack_data.samp_prc_flg[7] = 0x0000;
                        }
                        else
                        {
                            stack_data.samp_prc_flg[0]    = 0x0000;
                            stack_data.samp_prc_flg[6]    = 0x0000;
                            stack_data.samp_prc_flg[7]    = 0x0000;
                            stack_data.graph_buf[stack_data.samp_prc_flg[5]]++;
                            stack_data.add_res++;
                        }
            }

            for( jCount = 0;jCount < 0x0100;jCount++ )
            {
                data->graph_buf[jCount] = stack_data.graph_buf[jCount];
            }

            if (s_modes.speciesMode == SPECIES_MODE_HUMAN)
            {
                if(stack_data.graph_type == 0)
                {
                    iPulse12 = abs(Data_iPulse1 - Data_iPulse2);
                    iPulse23 = abs(Data_iPulse2 - Data_iPulse3);
                    iPulse31 = abs(Data_iPulse3 - Data_iPulse1);                
                    if ((Data_iPulse1+Data_iPulse2+Data_iPulse3)<55000)
                    {    
                        if((iPulse12 > 1500)||(iPulse23 > 1500)||(iPulse31 > 1500))
                        {
                            if (Data_iPulse3 != 0)
                            {
                                RBC_err_id = 1;
                            }

                        }
                    }
                    if ((Data_iPulse1+Data_iPulse2+Data_iPulse3)>55000)
                    {    
                        if((iPulse12 > 3000)||(iPulse23 > 3000)||(iPulse31 > 3000))
                        {
                            if (Data_iPulse3 != 0)
                            {
                                RBC_err_id = 1;
                            }

                        }
                    }

#ifdef __MYTEST__
                    pulse_data[4] = stack_data.add_res;
                    pulse_data[5] = Data_iPulse1;
                    pulse_data[6] = Data_iPulse2;
                    pulse_data[7] = Data_iPulse3;
#endif

                }
                else if(stack_data.graph_type == 1)
                {
                    iPulse12 = abs(Data_iPulse1 - Data_iPulse2);
                    iPulse23 = abs(Data_iPulse2 - Data_iPulse3);
                    iPulse31 = abs(Data_iPulse3 - Data_iPulse1);

                    if ((Data_iPulse1+Data_iPulse2+Data_iPulse3)<25000)
                    {
                        if((iPulse12 > 1000)||(iPulse23 > 1000)||(iPulse31 > 1000))
                        {
                            if (Data_iPulse3 != 0)
                            {
                                WBC_err_id = 1;
                            }
                        }
                    }        

                    if (25000<(Data_iPulse1+Data_iPulse2+Data_iPulse3)<60000)
                    {
                        if((iPulse12 > 2000)||(iPulse23 > 2000)||(iPulse31 > 2000))
                        {
                            if (Data_iPulse3 != 0)
                            {
                                WBC_err_id = 1;
                            }
                        }
                    }


                    if ((Data_iPulse1+Data_iPulse2+Data_iPulse3)>60000)
                    {
                        if((iPulse12 > 4000)||(iPulse23 > 4000)||(iPulse31 > 4000))
                        {
                            if (Data_iPulse3 != 0)
                            {
                                WBC_err_id = 1;
                            }
                        }
                    }

#ifdef __MYTEST__
                    pulse_data[0] = stack_data.add_res;
                    pulse_data[1] = Data_iPulse1;
                    pulse_data[2] = Data_iPulse2;
                    pulse_data[3] = Data_iPulse3;
#endif
                } 
                else
                {
                    iPulse12 = abs(Data_iPulse1 - Data_iPulse2);
                    iPulse23 = abs(Data_iPulse2 - Data_iPulse3);
                    iPulse31 = abs(Data_iPulse3 - Data_iPulse1);
                    if ((Data_iPulse1+Data_iPulse2+Data_iPulse3)<4000)
                    {
                        if((iPulse12 > 400)||(iPulse23 > 400)||(iPulse31 > 400))
                        {
                            if (Data_iPulse3 != 0)
                            {
                                PLT_err_id = 1;
                            }
                        }
                    }
                    if (4000<(Data_iPulse1+Data_iPulse2+Data_iPulse3)<10000)
                    {
                        if((iPulse12 > 1000)||(iPulse23 > 1000)||(iPulse31 > 1000))
                        {
                            if (Data_iPulse3 != 0)
                            {
                                PLT_err_id = 1;
                            }
                        }
                    }
                    if (10000<(Data_iPulse1+Data_iPulse2+Data_iPulse3)<15000)
                    {
                        if((iPulse12 > 1800)||(iPulse23 > 1800)||(iPulse31 > 1800))
                        {
                            if (Data_iPulse3 != 0)
                            {
                                PLT_err_id = 1;
                            }
                        }
                    }
                    if ((Data_iPulse1+Data_iPulse2+Data_iPulse3)>15000)
                    {
                        if((iPulse12 > 3000)||(iPulse23 > 3000)||(iPulse31 > 3000))
                        {
                            if (Data_iPulse3 != 0)
                            {
                                PLT_err_id = 1;
                            }
                        }
                    }
#ifdef __MYTEST__
                    pulse_data[8] = stack_data.add_res;
                    pulse_data[9] = Data_iPulse1;
                    pulse_data[10] = Data_iPulse2;
                    pulse_data[11] = Data_iPulse3;
#endif

                }
            }

            if (s_modes.speciesMode != SPECIES_MODE_HUMAN)
            {
                if(stack_data.graph_type == 0)
                {
                    iPulse12 = abs(Data_iPulse1 - Data_iPulse2);
                    iPulse23 = abs(Data_iPulse2 - Data_iPulse3);
                    iPulse31 = abs(Data_iPulse3 - Data_iPulse1);                
                    if ((Data_iPulse1+Data_iPulse2+Data_iPulse3)<55000)
                    {    
                        if((iPulse12 > 1500)||(iPulse23 > 1500)||(iPulse31 > 1500))
                        {
                            if (Data_iPulse3 != 0)
                            {
                                RBC_err_id = 1;
                            }

                        }
                    }
                    if ((Data_iPulse1+Data_iPulse2+Data_iPulse3)>55000)
                    {    
                        if((iPulse12 > 3000)||(iPulse23 > 3000)||(iPulse31 > 3000))
                        {
                            if (Data_iPulse3 != 0)
                            {
                                RBC_err_id = 1;
                            }

                        }
                    }

#ifdef __MYTEST__
                    pulse_data[4] = stack_data.add_res;
                    pulse_data[5] = Data_iPulse1;
                    pulse_data[6] = Data_iPulse2;
                    pulse_data[7] = Data_iPulse3;
#endif

                }
                else if(stack_data.graph_type == 1)
                {
                    iPulse12 = abs(Data_iPulse1 - Data_iPulse2);
                    iPulse23 = abs(Data_iPulse2 - Data_iPulse3);
                    iPulse31 = abs(Data_iPulse3 - Data_iPulse1);

                    if ((Data_iPulse1+Data_iPulse2+Data_iPulse3)<25000)
                    {
                        if((iPulse12 > 1000)||(iPulse23 > 1000)||(iPulse31 > 1000))
                        {
                            if (Data_iPulse3 != 0)
                            {
                                WBC_err_id = 1;
                            }
                        }
                    }        

                    if (25000<(Data_iPulse1+Data_iPulse2+Data_iPulse3)<60000)
                    {
                        if((iPulse12 > 2000)||(iPulse23 > 2000)||(iPulse31 > 2000))
                        {
                            if (Data_iPulse3 != 0)
                            {
                                WBC_err_id = 1;
                            }
                        }
                    }


                    if ((Data_iPulse1+Data_iPulse2+Data_iPulse3)>60000)
                    {
                        if((iPulse12 > 4000)||(iPulse23 > 4000)||(iPulse31 > 4000))
                        {
                            if (Data_iPulse3 != 0)
                            {
                                WBC_err_id = 1;
                            }
                        }
                    }

#ifdef __MYTEST__
                    pulse_data[0] = stack_data.add_res;
                    pulse_data[1] = Data_iPulse1;
                    pulse_data[2] = Data_iPulse2;
                    pulse_data[3] = Data_iPulse3;
#endif
                } 
                else
                {
                    iPulse12 = abs(Data_iPulse1 - Data_iPulse2);
                    iPulse23 = abs(Data_iPulse2 - Data_iPulse3);
                    iPulse31 = abs(Data_iPulse3 - Data_iPulse1);
                    if ((Data_iPulse1+Data_iPulse2+Data_iPulse3)<4000)
                    {
                        if((iPulse12 > 400)||(iPulse23 > 400)||(iPulse31 > 400))
                        {
                            if (Data_iPulse3 != 0)
                            {
                                PLT_err_id = 1;
                            }
                        }
                    }
                    if (4000<(Data_iPulse1+Data_iPulse2+Data_iPulse3)<10000)
                    {
                        if((iPulse12 > 1000)||(iPulse23 > 1000)||(iPulse31 > 1000))
                        {
                            if (Data_iPulse3 != 0)
                            {
                                PLT_err_id = 1;
                            }
                        }
                    }
                    if (10000<(Data_iPulse1+Data_iPulse2+Data_iPulse3)<15000)
                    {
                        if((iPulse12 > 2000)||(iPulse23 > 2000)||(iPulse31 > 2000))
                        {
                            if (Data_iPulse3 != 0)
                            {
                                PLT_err_id = 1;
                            }
                        }
                    }
                    if ((Data_iPulse1+Data_iPulse2+Data_iPulse3)>15000)
                    {
                        if((iPulse12 > 3000)||(iPulse23 > 3000)||(iPulse31 > 3000))
                        {
                            if (Data_iPulse3 != 0)
                            {
                                PLT_err_id = 1;
                            }
                        }
                    }
#ifdef __MYTEST__
                    pulse_data[8] = stack_data.add_res;
                    pulse_data[9] = Data_iPulse1;
                    pulse_data[10] = Data_iPulse2;
                    pulse_data[11] = Data_iPulse3;
#endif

                }
            }




            data->add_res = stack_data.add_res;
            data->samp_prc_flg[0] = stack_data.samp_prc_flg[0];
            data->samp_prc_flg[6] = stack_data.samp_prc_flg[6];
            data->samp_prc_flg[7] = stack_data.samp_prc_flg[7];
            data->samp_prc_flg[4] = stack_data.samp_prc_flg[4];
            data->samp_prc_flg[5] = stack_data.samp_prc_flg[5];
            data->samp_prc_flg[3] = stack_data.samp_prc_flg[3];
            data->samp_prc_flg[11] = stack_data.samp_prc_flg[11];
            data->samp_prc_flg[2] = stack_data.samp_prc_flg[2];
        }
    }

    

void Cell_Classifying_Function( DATA_SAMPLING *pData )
{     
    DATA_SAMPLING       stat_data ;

    int                 max = 0;
    int                 min = 0;
    int                 max_index = 0;
    int                 min_index = 0;

    int                 ax;
    int                 dx;  
    int                 adjust_lym_count;
    int                 adjust_mid_index;
    int                 adjust_mid_count;

    int                 mid_sum_adjust = 0;
    int                 mid_mid_val = 0;

    int                 iCount = 0;
    int                 jCount = 0;
    int                 start_index   = 0;
    int                 end_index     = 0;
    int                 min_val_index = 0;

    int                 index = 0;
    int                 plt_index_1 = 0;
    int                 plt_index_2 = 0;
    int                 plt_division_time = 0;

    unsigned short int  plt_graph[256]; 


    float               sampl_res_sum = 0.0;
    float               val_tmp_1 = 0.0;
    float               val_tmp_2 = 0.0;
    double              tmp = 0.0;

    Copy_Sample_Data ((char*)pData,(char*)&stat_data,sizeof( DATA_SAMPLING ) );

    //0表示RBC，1表示WBC，2表示PLT
    if( stat_data.graph_type == 0x0000 || stat_data.graph_type == 0x0001 )
    {     
        stat_data.ad_count_max    = 0x0000 ;
        for( iCount = 0; iCount < stat_data.point_sum - 1 ;iCount++ ) //找出0--254最大脉冲数
        {
            if( stat_data.graph_buf[iCount] > stat_data.ad_count_max )
            {
                stat_data.ad_count_max     = stat_data.graph_buf[iCount];
            }    
        }
        if( stat_data.graph_type == 0x0001 )
        {
            if( stat_data.ad_count_max == 0 )    
            {
                SysTestResValBuf.wr_graph_gene = 0x0000; //图像因子    
            }
            else
            {
                SysTestResValBuf.wr_graph_gene = (int)((stat_data.graph_buf[0x00ff]/(stat_data.ad_count_max*1.0))*0x00ff);
            }
        }
        //f(255) = f(254)
        stat_data.graph_buf[0x00ff] = stat_data.graph_buf[0x00ff - 1];
        //8点平滑 归一化到255
        for( iCount = 0; iCount < stat_data.point_sum ;iCount++ )
        {
            if( iCount < 0x0008 )
            {
                sampl_res_sum = sampl_res_sum + (unsigned short int)stat_data.graph_buf[iCount];
                if( stat_data.ad_count_max == 0x0000 )
                {
                    stat_data.buf[iCount] = 0x00;             
                }    
                else
                {
                    stat_data.buf[iCount] = (unsigned char)(stat_data.graph_buf[iCount]*(0x00ff/(stat_data.ad_count_max*1.0)));
                }
            }    
            else //8点平滑算法
            {
                sampl_res_sum = sampl_res_sum + (unsigned short int)stat_data.graph_buf[iCount];
                sampl_res_sum = sampl_res_sum - (unsigned short int)stat_data.graph_buf[iCount - 8];
                stat_data.buf[iCount] = (unsigned char)(((sampl_res_sum*0x00ff)/8.0)/(stat_data.ad_count_max*1.0));    
            }
        }

        for( iCount = 4; iCount < stat_data.point_sum ;iCount++ )
        {
            stat_data.buf[iCount - 4] = stat_data.buf[iCount];    
        }

        for( iCount = stat_data.point_sum - 4; iCount < stat_data.point_sum ;iCount++ )
        {
            stat_data.buf[iCount] = stat_data.buf[stat_data.point_sum - 5];    
        }


        Copy_Sample_Data ((char*)&stat_data,(char*)pData,sizeof( DATA_SAMPLING ) );


        if( stat_data.graph_type != 0x0000 )
        {
            start_index   = 0x00b0;
            end_index     = 0x00ff;    
            min_val_index = 0x00ff;

            for( iCount = start_index;iCount <= end_index;iCount++ )
            {
                if( stat_data.buf[iCount] < 0x0002 )
                {
                    min_val_index = iCount ;
                    break;    
                }    
            }
            min_val_index = (int)(min_val_index*(102.0/75.0));
            if( min_val_index > 0x015e )
            {
                min_val_index = 0x015e;
            }
            if( min_val_index < 0x00f0 )
            {
                min_val_index = 0x00f0;
            }

            val_2522 = 0;
            int val_2524 = 0;

            for( iCount = 0;iCount < 0x000B;iCount++ )
            {

                if( val_34ad == 0 )
                {
                    if( conslt_array_1[iCount][1] > min_val_index )
                        if( conslt_array_1[iCount][0] <= min_val_index )
                        {    
                                lym_division = (int)((SetSysInfoData.lym_line - conslt_array_2[iCount][0])*(75.0/102.0)); 
                                mid_division = (int)((SetSysInfoData.mid_line - conslt_array_2[iCount][1])*(75.0/102.0));

                            val_2522 = conslt_array_2[iCount][0] ;
                            val_2524 = conslt_array_2[iCount][1] ;
                            break;
                        }           
                }
                else if( val_34ad == 1 )
                {
                    if( conslt_array_3[iCount][1] > min_val_index )
                        if( conslt_array_3[iCount][0] <= min_val_index )
                        {               
                                lym_division = (int)(((SetSysInfoData.lym_line - conslt_array_4[iCount][0])*(75.0/102.0))); 
                                mid_division = (int)(((SetSysInfoData.mid_line - conslt_array_4[iCount][1])*(75.0/102.0)));

                            val_2522 = conslt_array_4[iCount][0] ;
                            val_2524 = conslt_array_4[iCount][1] ;
                            break;
                        }  
                }
                else if( val_34ad == 2 )
                {
                    if( conslt_array_5[iCount][1] > min_val_index )
                        if( conslt_array_5[iCount][0] <= min_val_index )
                        {               
                                lym_division = (int)(((SetSysInfoData.lym_line - conslt_array_6[iCount][0])*(75.0/102.0))); 
                                mid_division = (int)(((SetSysInfoData.mid_line - conslt_array_6[iCount][1])*(75.0/102.0)));

                            val_2522 = conslt_array_6[iCount][0] ;
                            val_2524 = conslt_array_6[iCount][1] ;
                            break;
                        }
                }
            }

            max = 0;
            min = 0;
            max_index = 0;
            min_index = 0;

            for( iCount = 0;iCount <= lym_division ;iCount++ )
            {
                if( (unsigned int)stat_data.buf[iCount] >= max )
                {
                    max = (unsigned int)stat_data.buf[iCount];
                    max_index = iCount ;          
                }    
            }

            min = 0x00ff;
            for( iCount = max_index ;iCount <= lym_division ;iCount++ )
            {
                if( (unsigned int)stat_data.buf[iCount] <= min )    
                {
                    min = (unsigned int)stat_data.buf[iCount] ;
                    min_index = iCount;    
                }
            }
            min_val_index = 0;
            if((max - min) > 0x001e )
            {
                if((min_index - max_index) > 0x0002 )
                {
                    min_val_index = 0;
                    for( jCount = lym_division ;jCount > (lym_division - 13);jCount-- )
                    {
                        adjust_lym_count = 0;
                        for( iCount = jCount ;iCount > (max_index + 0x0002);iCount-- )
                        {
                            ax = ((unsigned int)stat_data.buf[jCount - 1]) -  ((unsigned int)stat_data.buf[jCount + 1]);
                            dx = ((unsigned int)stat_data.buf[iCount - 1]) -  ((unsigned int)stat_data.buf[iCount + 1]);
                            dx = dx - 10;
                            if( ax < dx )    
                            {
                                adjust_lym_count++;
                            }
                        }
                        if( adjust_lym_count < 0x0004 )
                        {
                            break;    
                        }
                        else
                        {
                            min_val_index++;
                        } 
                    }

                    if( min_val_index <= 0x0008 )
                    {
                        min_val_index = min_val_index - 0x0003;    
                    }
                    else
                    {
                        min_val_index = min_val_index - 0x0004;        
                    }

                    if( min_val_index > 0x000d )
                    {
                        min_val_index = 0x000d;
                    }

                    if( min_val_index <= 0x0000 )
                    {
                        min_val_index = 0x0000;
                    }    
                    lym_division = lym_division - min_val_index ;            
                } 
            }

            if( min_val_index != 0  )
            {
                mid_division = mid_division - min_val_index;    
                val_2522 = val_2522 + (int)((min_val_index*(102.0/75.0)) + 0.99);
                val_2524 = val_2524 + (int)((min_val_index*(102.0/75.0)) + 0.99);
            } 

            min = 0x00ff;      
            for( iCount = lym_division;iCount <= mid_division;iCount++ )
            {
                if( (unsigned int)stat_data.buf[iCount] <= min )
                {
                    min = (unsigned int)stat_data.buf[iCount];     
                }
            }

            max = 0x0000;  
            min_index = 0x00f5;
            for( iCount = mid_division;iCount <= 0x00f5;iCount++ )
            {
                if( (unsigned int)stat_data.buf[iCount] >= max )
                {
                    max = (unsigned int)stat_data.buf[iCount];
                    min_index = iCount;    
                }
            }

            ax = 0;
            adjust_mid_count = 0;
            if( (mid_division+1) < min_index)
            {
                for( iCount = mid_division+1;iCount < min_index;iCount++ )
                {
                    ax = (unsigned int)stat_data.buf[mid_division - 1] + (unsigned int)stat_data.buf[mid_division] + (unsigned char)stat_data.buf[mid_division + 1];
                    val_tmp_1 = ax/3.0;
                    val_tmp_2 = (stat_data.buf[iCount] - 1)*1.0;
                    if((val_tmp_1 <  val_tmp_2)||( fabs(val_tmp_1 - val_tmp_2) < 0.000001 ))
                    {
                        adjust_mid_count++;   
                    }
                }    
            }

            if( (max - min) > 0x000a )
            {
                if( adjust_mid_count < 0x0004 )    
                {           
                    adjust_mid_index = 0;            
                    min_val_index = mid_division;

                    for(iCount = mid_division;iCount > (lym_division + 10);iCount-- )
                    {
                        mid_sum_adjust = 0;
                        for( jCount = iCount - 2;jCount <= (iCount + 2);jCount++ )
                            mid_sum_adjust += (unsigned int)stat_data.buf[jCount];
                        mid_mid_val = (unsigned int)(mid_sum_adjust/5.0);
                        for( jCount = iCount;jCount >= (lym_division + 10);jCount-- )
                            if( (unsigned int)stat_data.buf[jCount] > (unsigned int)(mid_mid_val - 3) )  
                            {
                                mid_sum_adjust = 0x0FA0;
                            }
                            else
                            {
                                if( (unsigned int)stat_data.buf[jCount - 1] <= (unsigned int)(mid_mid_val - 3) )  
                                {
                                    mid_sum_adjust = 0x0bb8;                     
                                    adjust_mid_index = 1; 
                                    break;
                                }
                                else
                                {
                                    mid_sum_adjust = 0x0FA0;
                                }
                            }

                            if( mid_sum_adjust == 0x0FA0 )
                            {
                                min_val_index = iCount;                         
                                break;
                            }
                    }

                    if( adjust_mid_index == 1 )
                        min_val_index = min_val_index - 2;
                    if( mid_division < min_val_index )    
                        min_val_index = mid_division;
                    if( (lym_division + 8) > min_val_index )
                        min_val_index = lym_division + 8;

                    mid_sum_adjust = (int)(((mid_division - min_val_index)*(102.0/75.0)) + 0.99);    
                    val_2524 = mid_sum_adjust + val_2524;
                    mid_division = min_val_index;
                }
            }
            else
            {
                mid_division = mid_division - 4;   
            }
        }
    }
    else
    {
        if( stat_data.graph_type == 0x0002 )
        {
            //plt数据全部左移11个位置
            for( iCount = 0x0002;iCount < (stat_data.point_sum + 0x0002);iCount++ )
            {
                plt_data.graph_buf[iCount - 0x0002] = plt_data.graph_buf[iCount];     
            }    

            for( iCount = 0x0000;iCount < stat_data.point_sum ;iCount++ )
            {
                plt_graph[iCount] = plt_data.graph_buf[iCount];     
            }    

            plt_division_time = 8;
            sampl_res_sum = 0.0;

            for( iCount = 0x0000;iCount < stat_data.point_sum ;iCount++ )
            {
                if( iCount < plt_division_time )    
                {
                    sampl_res_sum = sampl_res_sum + (plt_graph[iCount]*1.0);
                    plt_graph[iCount + 128] = plt_graph[iCount];

                }
                else
                {
                    sampl_res_sum = sampl_res_sum + (plt_graph[iCount] - plt_graph[iCount - plt_division_time])*1.0;
                    plt_graph[iCount + 128] = (unsigned short int)( sampl_res_sum/(plt_division_time*1.0));    
                }

            }            

            for( iCount = 0x0000;iCount < stat_data.point_sum - 4;iCount++ )
            {
                plt_graph[iCount+128] = plt_graph[iCount + 128 + 4];
            }

            for( iCount = 0x007c;iCount < stat_data.point_sum;iCount++ )
            {
                plt_graph[iCount + 128] = plt_graph[0x007b + 128];
            }

            plt_data.ad_count_max = 0;
            for( iCount = 0x0000;iCount < 0x0040;iCount++ )
            {
                if( plt_graph[iCount + 128] > plt_data.ad_count_max )
                {
                    plt_data.ad_count_max = plt_graph[iCount + 128];
                }
            }

            for( iCount = 0x0000;iCount < stat_data.point_sum;iCount++ )
            {
                if( plt_graph[iCount + 128] > plt_data.ad_count_max )
                {
                    plt_graph[iCount + 128] = plt_data.ad_count_max ;
                }
            }

            plt_division_time = ( unsigned short int )stat_data.x;
            sampl_res_sum = 0;
            for( iCount = 0x0000;iCount < stat_data.point_sum;iCount++ )
            {
                if( iCount < plt_division_time )    
                {
                    sampl_res_sum = sampl_res_sum + (plt_graph[iCount + 128]*1.0);
                    if( plt_data.ad_count_max != 0 )
                    {
                        tmp = plt_graph[iCount + 128]*255.0;
                        tmp = tmp/(plt_data.ad_count_max*1.0);
                        plt_data.buf[iCount] = (unsigned char)tmp;    
                    }
                    else
                    {
                        plt_data.buf[iCount] = 0x00;
                    } 
                }
                else
                {
                    sampl_res_sum = sampl_res_sum + (plt_graph[iCount + 128] - plt_graph[iCount + 128 - plt_division_time])*1.0;
                    if( plt_data.ad_count_max != 0 )
                    {
                        tmp = sampl_res_sum*255.0;
                        tmp = tmp/(plt_division_time*plt_data.ad_count_max*1.0);
                        plt_data.buf[iCount] = (unsigned char)tmp;    
                    }
                    else
                    {
                        plt_data.buf[iCount] = 0x00;
                    }               
                } 

            }

            for( iCount = 0x0000;iCount < stat_data.point_sum - 2;iCount++ )
            {
                plt_data.buf[iCount] = plt_data.buf[iCount + 2];    
            }

            for( iCount = 0x007e;iCount < stat_data.point_sum;iCount++ )
            {
                plt_data.buf[iCount] = plt_data.buf[0x007d];    
            }       

            SysTestResValBuf.plt_division_end = 0x006b;
            max = 0;
            for( iCount = 0x0000;iCount <= 0x0035;iCount++ )
            {
                if( plt_data.buf[iCount] >= max )
                {
                    max = (int)plt_data.buf[iCount];
                    max_index = iCount;
                }
            }

            if( max_index < 0x000a )
            {
                max_index = 0x000a;    
            }

            if( (max*0.6) > (plt_data.buf[0x007e]*1.0) )
            {
                if( ((max*0.4) > (plt_data.buf[0x007e]*1.0)) || ((max*0.6) <= (plt_data.buf[0x007e]*1.0)) )
                {
                    if( ((max*0.35) > (plt_data.buf[0x007e]*1.0)) || ((max*0.4) <= (plt_data.buf[0x007e]*1.0)) )      
                    {
                        if( ((max*0.30) > (plt_data.buf[0x007e]*1.0)) || ((max*0.35) <= (plt_data.buf[0x007e]*1.0)) )    
                        {
                            if( ((max*0.25) > (plt_data.buf[0x007e]*1.0)) || ((max*0.30) <= (plt_data.buf[0x007e]*1.0)) )
                            {
                                if( ((max*0.20) > (plt_data.buf[0x007e]*1.0)) || ((max*0.25) <= (plt_data.buf[0x007e]*1.0)) )
                                {
                                    return;
                                }
                                else
                                {
                                    SysTestResValBuf.plt_division_end = SysTestResValBuf.plt_division_end - 4;
                                }    
                            }
                            else
                            {
                                SysTestResValBuf.plt_division_end = SysTestResValBuf.plt_division_end - 6;
                            }
                        }
                        else
                        {
                            SysTestResValBuf.plt_division_end = SysTestResValBuf.plt_division_end - 8;
                        }
                    }
                    else
                    {
                        SysTestResValBuf.plt_division_end = SysTestResValBuf.plt_division_end - 10;
                    }
                }
                else
                {
                    for( iCount = 0x007e;iCount > max_index;iCount-- )
                    {
                        if(((unsigned short int)plt_data.buf[iCount] >= ((unsigned short int)plt_data.buf[iCount-1] - 2)) || ((unsigned short int)plt_data.buf[iCount] >= ((unsigned short int)plt_data.buf[iCount-2] - 2)) )    
                        {
                            plt_index_1 = iCount; 
                        }
                        else
                        {
                            if((unsigned short int)plt_data.buf[iCount] >= ((unsigned short int)plt_data.buf[iCount-3] - 2) )
                            {
                                plt_index_1 = iCount; 
                            }
                            else
                            {
                                break;    
                            }
                        }
                    }

                    for( iCount = max_index;iCount < 0x007e;iCount++ )
                    {
                        if(((unsigned short int)plt_data.buf[iCount] >= ((unsigned short int)plt_data.buf[iCount+1] - 2)) || ((unsigned short int)plt_data.buf[iCount] >= ((unsigned short int)plt_data.buf[iCount+2] - 2)) )     
                        {
                            plt_index_2 = iCount;
                        }
                        else
                        {
                            if((unsigned short int)plt_data.buf[iCount] >= ((unsigned short int)plt_data.buf[iCount+3] - 2) )
                            {
                                plt_index_2 = iCount; 
                            }
                            else
                            {
                                break;    
                            }                     
                        }
                    } 

                    if( abs(plt_index_2 - plt_index_1) >= 0x0004 )
                    {
                        index = (int)(( plt_index_2 + plt_index_1)/2.0);    
                        index = index + 8;                   
                    }
                    else
                    {
                        index = (int)(( plt_index_2 + plt_index_1)/2.0);    
                        index = index + 10;
                    }    

                    for( iCount = index;iCount <= (SysTestResValBuf.plt_division_end - 0x000c);iCount++ )
                    {
                        if((unsigned short int)plt_data.buf[iCount] < ((unsigned short int)plt_data.buf[iCount+1] - 2) )    
                        {
                            index = iCount;      
                        }
                    }

                    if( (SysTestResValBuf.plt_division_end - 0x000c) >= index )
                    {
                        SysTestResValBuf.plt_division_end = index ;
                    }
                    else
                    {
                        SysTestResValBuf.plt_division_end = SysTestResValBuf.plt_division_end - 0x000c ;
                    }         

                    if( SysTestResValBuf.plt_division_end <= 0x0050 )
                    {
                        SysTestResValBuf.plt_division_end =  0x0050 ;    
                    }     
                }          
            }
            else
            {
                for( iCount = 0x007e;iCount > max_index;iCount-- )
                {
                    if( (unsigned short int)plt_data.buf[iCount] >= ((unsigned short int)plt_data.buf[iCount-1] - 6))
                    {
                        plt_index_1 = iCount;      
                    }
                    else
                    {
                        if( (unsigned short int)plt_data.buf[iCount] >= ((unsigned short int)plt_data.buf[iCount-2] - 6))
                        {
                            plt_index_1 = iCount;     
                        }
                        else
                        {
                            if( (unsigned short int)plt_data.buf[iCount] >= ((unsigned short int)plt_data.buf[iCount-3] - 6))
                            {
                                plt_index_1 = iCount;    
                            }
                            else
                            {
                                if( (unsigned short int)plt_data.buf[iCount] >= ((unsigned short int)plt_data.buf[iCount-4] - 6))
                                {
                                    plt_index_1 = iCount;    
                                }
                                else
                                {
                                    if( (unsigned short int)plt_data.buf[iCount] >= ((unsigned short int)plt_data.buf[iCount-5] - 6))
                                    {
                                        plt_index_1 = iCount;    
                                    }
                                    else
                                    {
                                        break;    
                                    }
                                }
                            }
                        }
                    }
                } 

                for( iCount = max_index;iCount < 0x007e;iCount++ )
                {        
                    if( (unsigned short int)plt_data.buf[iCount] >= ((unsigned short int)plt_data.buf[iCount+1] - 6) )
                    {
                        plt_index_2 = iCount;          
                    }
                    else
                    {
                        if( (unsigned short int)plt_data.buf[iCount] >= ((unsigned short int)plt_data.buf[iCount+2] - 6) )
                        {
                            plt_index_2 = iCount;        
                        }
                        else
                        {
                            if( (unsigned short int)plt_data.buf[iCount] >= ((unsigned short int)plt_data.buf[iCount+3] - 6) )
                            {
                                plt_index_2 = iCount;    
                            }
                            else
                            {
                                if( (unsigned short int)plt_data.buf[iCount] >= ((unsigned short int)plt_data.buf[iCount+4] - 6) )
                                {
                                    plt_index_2 = iCount;    
                                }
                                else
                                {
                                    if( (unsigned short int)plt_data.buf[iCount] >= ((unsigned short int)plt_data.buf[iCount+5] - 6) )
                                    {
                                        plt_index_2 = iCount;    
                                    }
                                    else
                                    {
                                        break;    
                                    }
                                }        
                            }    
                        }                    
                    }
                }

                if( abs( plt_index_2 - plt_index_1 ) >= 0x000a )
                {
                    index =(int)( abs(plt_index_2 + plt_index_1)/2.0 );     
                }
                else
                {
                    index = ( (int)(abs(plt_index_2 + plt_index_1)/2.0) + 5 );
                }

                for( iCount = index;iCount <= ( SysTestResValBuf.plt_division_end - 0x0016 );iCount++ )
                {
                    if( plt_data.buf[iCount] < ( plt_data.buf[iCount + 1] - 0x02 ) )
                    {
                        break;    
                    }
                }

                index = iCount ;        
                if( ( SysTestResValBuf.plt_division_end - 0x0016 ) < index )
                {
                    SysTestResValBuf.plt_division_end = SysTestResValBuf.plt_division_end - 0x0016; 
                }
                else
                {
                    SysTestResValBuf.plt_division_end = index ;     
                }

                if( SysTestResValBuf.plt_division_end <= 0x0030 )
                {
                    SysTestResValBuf.plt_division_end = 0x0030;    
                }
            }
        }
    }

}




void Wbc_Result_And_Graph_Data_Process()
{
    int  wbc;
    int  wbc_y;
    int  lym_p;
    int  mid_p;
    int  gran_p;
    int  lym_v;
    int  mid_v;
    int  gran_v;


    int  graph_paint_max_val = 0;

    float lym_p_res;
    float mid_p_res;

    int   iCount  = 0;
    float add_res = 0;

    unsigned char      final_res = 0x00;
    unsigned short int res = 0;
    unsigned short int max = 0;

    Cell_Classifying_Function( &wbc_data );

    for( iCount = 0;iCount < wbc_data.point_sum;iCount++ )
    {
        SysADBufData.WbcHisGraph[iCount] = wbc_data.buf[iCount];    
    }

    if(val_34ad == 0)
    {
        wbc = (int)((wbc_data.add_res*310)/57119.0*1.3101); 
        wbc_y = wbc;


        if( wbc > 0x00fa ) //250
        {
            wbc = (int)(((((wbc - 250)*0.1)/300.0) + 1.18)*wbc );    
        }  

        wbc = (int)((wbc*syscalval.cl_WBC));
    }

    if(val_34ad == 1)
    {
        wbc = (int)((wbc_data.add_res*310)/57119.0*1.3101);
        wbc_y = wbc;


        if( wbc > 0x00fa ) //250
        {
            wbc = (int)(((((wbc - 250)*0.1)/300.0) + 1.18)*wbc );    
        } 

        wbc = (int)((wbc*syscalval.cl_WBC));
    }

    if( val_34ad == 2 )
    {
        wbc = (int)((((wbc_data.add_res*310)/57119.0)*0.9103)*2.648);
        wbc_y = wbc;

        if( wbc > 0x00fa ) //250
        {
            wbc = (int)(((((wbc - 250)*0.1)/300.0) + 1.18)*wbc );    
        } 

        wbc = (int)((wbc*syscalval.cl_WBC));
    }   

    if( (wbc < 0) || ( wbc > 0x03e7 ) )
    {
        wbc = 0xd8f0;    
    }

    if( (wbc < 1) && ( Alg::t200 == 1) )
    {
        //wbc = 0xd8f0;
        for( iCount = 0;iCount < wbc_data.point_sum;iCount++ )
        {
            SysADBufData.WbcHisGraph[iCount] = 0x00 ;    
        }    
    }

    const unsigned short int val_34dd = 0;
    const unsigned short int val_0092 = 0;
    if( ((wbc > 5) && (wbc != 0xd8f0)) && ((val_34dd == 0) || ((val_34dd == 1))|| ( val_0092 == 0 ) ))
    {
        add_res = 0.0;
        for( iCount = 0;iCount <= lym_division;iCount++ )
        {
            add_res = add_res + wbc_data.graph_buf[iCount];    
        } 

        lym_p_res = ((add_res*1000)/wbc_data.add_res);
        lym_p_res = lym_p_res* results_coefficient.LYM_5;
        lym_p = (int)lym_p_res;
        lym_p = (int)(lym_p * SetSysInfoData.lym);

        if( (lym_p < 0) || ( lym_p > 0x03e8 ) )
        {
            lym_p = 0xd8f0;
        }

        add_res = 0.0;
        for( iCount = lym_division + 1;iCount <= mid_division;iCount++ )
        {
            add_res = add_res + wbc_data.graph_buf[iCount];    
        }
        mid_p_res = (add_res*1000)/wbc_data.add_res;
        mid_p_res = mid_p_res*results_coefficient.MID_5;
        mid_p=(int)mid_p_res;
        mid_p=(int)(mid_p * SetSysInfoData.mid);

        if( (mid_p < 0) || ( mid_p > 0x03e8 )   )
        {
            mid_p = 0xd8f0;
        }

        gran_p = (1000 - mid_p - lym_p);
        if( gran_p < 0 )
        {
            gran_p = 0xd8f0;      
        }

        if( lym_p == 0xd8f0 ) 
        {
            lym_v = 0xd8f0;    
        } 
        else
        {
            add_res = 0.0;
            for( iCount = 0;iCount <= lym_division;iCount++ )
            {
                add_res = add_res + wbc_data.graph_buf[iCount];    
            }
            lym_v=(int)((add_res/wbc_data.add_res)*wbc + 0.5);    
            lym_v=(int)(lym_v*results_coefficient.LYM_3);        
        }    

        if( (lym_v < 0) || (lym_v > 0x03e7) )
        {
            lym_v = 0xd8f0;    
        }
        add_res = 0.0;
        for( iCount = lym_division + 1;iCount <= mid_division;iCount++ )
        {
            add_res = add_res + wbc_data.graph_buf[iCount];    
        }
        mid_v=(int)((add_res/wbc_data.add_res)*wbc + 0.5);    
        mid_v = (int)(mid_v*results_coefficient.MID_3);

        if((mid_v < 0) || (mid_v > 0x03e7))
        {
            mid_v = 0xd8f0;
        }

        gran_v = wbc-lym_v-mid_v ;
        if( (gran_v < 0) || (gran_v > 0x03e7) )
        {
            gran_v = 0xd8f0;    
        }    
    }
    else
    {
        lym_v  = 0xd8f0;
        mid_v  = 0xd8f0;
        gran_v = 0xd8f0;

        lym_p  =    0xd8f0;
        mid_p  = 0xd8f0;
        gran_p = 0xd8f0;              
    }

    for( iCount = 0;iCount <= lym_division;iCount++ )
    {
        if( wbc_data.buf[iCount] != 0x00 )
        {
            SysTestResValBuf.wbc_division_begin = iCount ;
            break;
        }    
    }     

    SysTestResValBuf.wbc_division_begin = SysTestResValBuf.wbc_division_begin + 2;
    if( SysTestResValBuf.plt_division_begin < 0x000a )
    {
        SysTestResValBuf.plt_division_begin = 0x000a ;    
    }

    SysTestResValBuf.lym_division_begin = lym_division;
    SysTestResValBuf.mid_division_begin = mid_division ;
    SysTestResValBuf.wbc_division_end   = wbc_data.point_sum - 1 ;

    if( wbc == 0xd8f0 )
    {
        graph_paint_max_val = 0; 
    }
    else
    {
        if( wbc <= 0x0005 )
        {
            if( (wbc <= 5) && (wbc > 0) )
            {
                graph_paint_max_val =     wbc*0x000c;
            }
        }
        else
        {
            graph_paint_max_val = 0x0050;
        }    
    }

    max = (unsigned short) SysADBufData.WbcHisGraph[0];
    for( iCount = 0;iCount < wbc_data.point_sum;iCount++ )
    {
        if((unsigned short)SysADBufData.WbcHisGraph[iCount] > max )    
        {
            max = (unsigned short)SysADBufData.WbcHisGraph[iCount];
        }
    }    

    if( max != 0 )
    {
        SysTestResValBuf.wr_graph_gene = (int)((SysTestResValBuf.wr_graph_gene*graph_paint_max_val)/(max*1.0));     
    }

    //2012-04-26
    for( iCount = 1;iCount <= wbc_data.point_sum;iCount++ )
    {
        mainWindowData.Point_WBC[iCount] = 0x00;
        if( (max != 0) && (wbc != 0xd8f0) && (wbc != 0) )
        {
            res = (short int)((wbc_data.buf[iCount-1]*graph_paint_max_val)/max);
            final_res = (unsigned char)res;
            mainWindowData.Point_WBC[iCount] = final_res; 
        }
        else
        {
            mainWindowData.Point_WBC[iCount] = final_res;     
        }

    }   

    if( wbc < 5 ) 
    {
        lym_v  = 0xd8f0;
        mid_v  = 0xd8f0;
        gran_v = 0xd8f0;

        lym_p  =    0xd8f0;
        mid_p  = 0xd8f0;
        gran_p = 0xd8f0;        

        if( wbc < 2 )
        {
            wbc  = 0x0000;
            for( iCount = 0;iCount < wbc_data.point_sum;iCount++ )
                mainWindowData.Point_WBC[iCount] = 0x00; 
        }       
    }


    SysTestResValBuf.wbc   = wbc;
    SysTestResValBuf.plym  = lym_p;
    SysTestResValBuf.pmid  = mid_p; 
    SysTestResValBuf.pgran = gran_p; 
    SysTestResValBuf.vlym  = lym_v; 
    SysTestResValBuf.vmid  = mid_v; 
    SysTestResValBuf.vgran = gran_v; 

}




int  SEARCHDISTRIBUTINGWIDTH( int begin_index, int end_index ,DATA_SAMPLING *pData )
{
    int            max = 0;
    int            iCount = 0;
    int            max_index = 0;
    int            l_min_index = -1;
    int            r_min_index = -1;
    int            ex_max = 0;

    DATA_SAMPLING  stackcopy;

    Copy_Sample_Data ((char*)pData,(char*)&stackcopy,sizeof( DATA_SAMPLING ));    

    for( iCount = begin_index;iCount < end_index ;iCount++ )
    {
        if( stackcopy.buf[iCount] > max )
        {
            max = (int)stackcopy.buf[iCount];
            max_index = iCount ;
        }    
    }

    if( stackcopy.graph_type == 0 )
    {
        ex_max    = (int)(max * 0.6065);
    }  
    if( stackcopy.graph_type == 2 )
    {
        ex_max = (int)(max/5.0);     
    }

    for( iCount = max_index;iCount >= begin_index ;iCount-- )
    {
        if( stackcopy.buf[iCount] <= ex_max )
        {
            l_min_index = iCount ;
            break;    
        }
    }

    for( iCount = max_index;iCount < end_index;iCount++ )
    {
        if( (int)stackcopy.buf[iCount] <= ex_max )    
        {
            r_min_index = iCount;    
            break;
        }
    }

    if( stackcopy.graph_type == 2 )
    {    
        if( r_min_index == -1 )    
        {
            r_min_index = (int)((end_index*2*2*2)/10.0);    
        }
    }

    if( l_min_index > 0 )
    {
        if( r_min_index > 0 )
        {
            return ( r_min_index - l_min_index );
        }
    }

    return -1;
}



void Rbc_Result_And_Graph_Data_Process()
{
    int iCount  = 0;
    int res_add = 0;
    int rbc = 0;
    int mcv = 0;
    int hct;
    int rdw_cv;
    int rdw_sd;
    int mcv_ajust = 0;

    int max = 0;
    int width = 0;
    int graph_max_val = 0;

    float hct_res = 0.0;    double rbc_add_res = 0.0;
    double rbc_add_res_copy = 0.0;

    Cell_Classifying_Function(&rbc_data);     
    for( iCount = 0x0032;iCount > 0x000a; iCount-- )
    {
        if( (rbc_data.buf[iCount] <= rbc_data.buf[iCount - 1]) || (rbc_data.buf[iCount - 1] <= rbc_data.buf[iCount - 2]) )    
        {
            SysTestResValBuf.rbc_division_begin = iCount - 5;
            break;
        }
        else
        {
            if( rbc_data.buf[iCount - 2] < rbc_data.buf[iCount - 3] )    
            {
                SysTestResValBuf.rbc_division_begin = iCount - 5;
                break;
            }
        }
    }

    if( SysTestResValBuf.rbc_division_begin < 0x000A )
    {
        SysTestResValBuf.rbc_division_begin = 0x000A;
    }
    if( SysTestResValBuf.rbc_division_begin > 0x0023 )
    {
        SysTestResValBuf.rbc_division_begin = 0x0023;    
    }
    SysTestResValBuf.rbc_division_begin = 0x000a;    

    for( iCount = rbc_data.point_sum - 1 ;iCount > SysTestResValBuf.rbc_division_begin ;iCount-- )
    {
        if( rbc_data.buf[iCount] != 0 )
        {
            SysTestResValBuf.rbc_division_end =     iCount ;
            break;
        }    
    }

    if( SysTestResValBuf.rbc_division_end > 0x00f0 )
    {
        SysTestResValBuf.rbc_division_end = 0x00f0;
    }

    for( iCount = 0;iCount < SysTestResValBuf.rbc_division_begin;iCount++ )
    {
        res_add = res_add + rbc_data.graph_buf[iCount];      
    }

    rbc_data.add_res = rbc_data.add_res - res_add;
    if( val_34ad == 0 )
    {
        rbc = (int)( ((rbc_data.add_res*30.240)/2564.1) * 1.51 );

        rbc = (int)( rbc*( syscalval.cl_RBC ) );
    }  
    else if( val_34ad == 1 )
    {
        rbc = (int)( ((rbc_data.add_res*30.240)/2564.1) * 1.51 );

        rbc = (int)( rbc*( syscalval.cl_RBC ) );
    }
    else if( val_34ad == 2 )
    {       
        rbc = (int)( (((rbc_data.add_res*30.240)/2564.1)*1.51 )*1.4789);

        rbc = (int)( rbc*( syscalval.cl_RBC ) ); 
    }

    if( rbc < 0 || rbc > 0x07d0 )
      {
        rbc = 0xd8f0;    
      }
  
      if( rbc <= 2 )
      if( Alg::t200 == 0 )
      {
        rbc = 0;
        for( iCount = 0;iCount < 0x0100;iCount++ )
        {
             SysADBufData.RbcHisGraph[iCount] = 0x00;
        }    
      }
  
      if( rbc <= 0x00C8 )
      {
        if( rbc > 0x00C8 || rbc <= 0x0096 )
        {
         if( rbc > 0x0096 || rbc <= 0x0064 )
         {
         if( rbc > 0x0064 || rbc < 0x000a )
         {
         if( rbc < 0x000a || rbc == 0xd8f0 )
         {
             graph_max_val =    0;      
         }    
         }
         else
         {
          graph_max_val =    rbc >> 1;
         }
         }
         else
         {
             graph_max_val = 0x003c;    
         }
        }
        else
        {
          graph_max_val = 0x0046;    
        }      
      }
      else
      {
        graph_max_val = 0x0050;    
      }
  
      for( iCount = 0;iCount < 0x0100;iCount++ )
      {
        if( rbc_data.buf[iCount] >= max )
        {
          max = rbc_data.buf[iCount];    
        }    
      }

        //????í?D?êy?Y
        for( iCount = 0;iCount < 0x0100;iCount++ )
        { 
            if( rbc && (max != 0) && (rbc != 0xd8f0) )
            {
                SysADBufData.RbcHisGraph[iCount] = (unsigned char)((rbc_data.buf[iCount]*graph_max_val)/(max*1.0));       
            }
            else
            {
                SysADBufData.RbcHisGraph[iCount] = 0x00;
            }
        }


        if( rbc_data.add_res != 0 )
        {
            rbc_add_res = 0.0 ;
            for( iCount = SysTestResValBuf.rbc_division_begin ;iCount < SysTestResValBuf.rbc_division_end;iCount++ )
            {
                rbc_add_res = rbc_add_res + ( rbc_data.graph_buf[iCount]*( iCount + 10 )*1.00) ;
            }

            rbc_add_res_copy = rbc_add_res; 

            rbc_add_res = rbc_add_res_copy;
            rbc_add_res = rbc_add_res*9.5 ;
            rbc_add_res = rbc_add_res*syscalval.cl_MCV;
            rbc_add_res = rbc_add_res/(rbc_data.add_res*1.0);
            mcv = (int)rbc_add_res;

            mcv_ajust = 0;
            if( (mcv >= 0x0334) || (mcv < 0x030C) )
            {
                if( (mcv >= 0x030C) || (mcv < 0x02DA) )
                {
                    if( (mcv >= 0x02DA) || (mcv < 0x02a8) )
                    {
                        if( (mcv >= 0x02a8) || (mcv < 0x0258) )
                        {
                            if(mcv < 0x0258)
                            {
                                mcv_ajust = 50;      
                            }    
                        }
                        else
                        {
                            mcv_ajust = 40; 
                        }
                    }
                    else
                    {
                        mcv_ajust = 30;     
                    }        
                }
                else
                {
                    mcv_ajust = 20;
                }
            }
            else
            {
                mcv_ajust = 10;
            }

            if( (mcv < 0) || ( mcv > 0x09c4  ) || ( rbc < 0x000a) || (rbc == 0xd8f0))
            {
                mcv = 0xd8f0;
            }
            if((mcv == 0xd8f0)&&(( rbc < 0x000a) || (rbc == 0xd8f0)))     
            {
                hct_res = 0.0;
                hct = 0;       
            }
            else
            {      
                if(( mcv*rbc )/1000.0 < 1000.0)
                {
                hct_res = ( mcv*rbc )/1000.0;
                hct = (int)hct_res;
                hct = (int)(hct*results_coefficient.HCT);
                }

                if(( mcv*rbc )/1000.0 > 1000.0)
                {
                hct_res = ( mcv*rbc )/1500.0;
                hct = (int)hct_res;
                hct = (int)(hct*results_coefficient.HCT);
                }
                if( val_34ad == 2 )
                {
                    hct = (int)(hct_res*1.13);
                }
                hct = (int)hct_res;
                hct = (int)(hct*results_coefficient.HCT);
            }

            if( (hct < 0) || (hct > 0x03e7) )  ///////////2012-3-30
            {
                hct = 0xd8f0;    
            }

            if( (hct == 0) || (hct == 0xd8f0) || rbc < 0x000a )
            {
                rdw_sd = 0xd8f0;    
                rdw_cv = 0xd8f0;           
            }
            else
            {
                width   = SEARCHDISTRIBUTINGWIDTH( SysTestResValBuf.rbc_division_begin,SysTestResValBuf.rbc_division_end,&rbc_data );
                rdw_cv  = (int)(((((width*rbc_data.add_res)/(rbc_add_res_copy*1.0))/2.0)*100.0)*10.0);
                width   = SEARCHDISTRIBUTINGWIDTH( SysTestResValBuf.rbc_division_begin,SysTestResValBuf.rbc_division_end,&rbc_data );
                rdw_sd  = (int)((((width*50.0)/43.0)*1.6)*10.0);
                rdw_cv = (int)(rdw_cv*results_coefficient.RDW_CV);
                rdw_sd = (int)(rdw_sd*results_coefficient.RDW_SD);
            }

            if( (rdw_cv < 0) || (rdw_cv > 0x03E7) )
            {
                rdw_cv = 0xd8f0;    
            }
            if( (rdw_sd < 0) || (rdw_sd > 0x03E7) )
            {
                rdw_sd = 0xd8f0;    
            }   
            if( ( rbc < 0x000a) || (rbc == 0xd8f0) )
            {
                rdw_sd = 0xd8f0;    
                rdw_cv = 0xd8f0;
                mcv    = 0xd8f0;   

                SysTestResValBuf.hct = hct;
                SysTestResValBuf.rbc = rbc;
                SysTestResValBuf.mcv = mcv;
                SysTestResValBuf.rdw_cv = rdw_cv;
                SysTestResValBuf.rdw_sd = rdw_sd;    

            }      
        }
        else
        {
            SysTestResValBuf.hct = 0;
            SysTestResValBuf.rbc = 0;
            SysTestResValBuf.mcv = 0;
            SysTestResValBuf.rdw_cv = 0;
            SysTestResValBuf.rdw_sd = 0;

            for( iCount = 0;iCount < rbc_data.point_sum;iCount++ )
                mainWindowData.Point_RBC[iCount] = 0x00 ;    
            return;     
        }


        for( iCount = 0;iCount < rbc_data.point_sum;iCount++ )
            mainWindowData.Point_RBC[iCount] = SysADBufData.RbcHisGraph[iCount] ;   


        if( val_34ad == 2 )
        {
            if ((mcv > 0) && (mcv != 0xd8f0))
            {
                mcv = (int)(mcv*1.36);  
            }

            if ((hct > 0) && (hct != 0xd8f0))
            {
                hct = (int)(hct*1.36);  
            }
        }
        SysTestResValBuf.hct = hct;  
        SysTestResValBuf.rbc = rbc;
        SysTestResValBuf.mcv = mcv;
        SysTestResValBuf.rdw_cv = rdw_cv;
        SysTestResValBuf.rdw_sd = rdw_sd;

        return;     
}



int Hgb_Result_Process()
{
    int     hgb = 0;
    int     HgbBufResult = 0;
    int     HgbBkBufResult = 0;

    double  HgbCoff = 0.0;
    double  HgbCoffRes = 0.0;
    double  HgbConsult  = 0.0;
    double  HgbRes = 0.0;

    DmaBuf* dmaBuf = Dma::getDmaBuf();
    HgbBkBufResult = dmaBuf->hgbBkVoltage;    
    HgbBufResult = dmaBuf->hgbAdVoltage;
    qDebug() << "Alg Hgb_Result_Process" << HgbBufResult << HgbBkBufResult;

    val_3564 = 0; 

    if( (HgbBkBufResult < 2000) || ( HgbBufResult <= 0 ) || (HgbBkBufResult >= 3920) )
    {
        if( (HgbBkBufResult < 160) || ( HgbBufResult <= 0 ) || (HgbBkBufResult >= 3920) ) 
        {
            val_3564 = 1;      
        }    
        else
        {
            val_3564 = 2;      
        }
#ifdef __MYTEST__
        printf("HgbBkBufResult = %d, HgbBufResult = %d.\n", HgbBkBufResult, HgbBufResult);
        printf("SysADBufData.HgbBkBuf = %d, SysADBufData.HgbAdBuf = %d.\n", SysADBufData.HgbBkBuf, SysADBufData.HgbAdBuf);
#endif
        hgb = 0xd8f0;
    }
    else
    {
        double val_0466 = 602.14658906969;
        double val_046e = 606.78425388824;
        if( val_34ad != 2 )
        { 
            HgbConsult = val_046e;
        }    
        else
        {
            HgbConsult = val_0466;
        }

        HgbCoff = (1.0*HgbBkBufResult)/(HgbBufResult*1.0);
        HgbCoffRes = log10( HgbCoff );
        HgbRes = HgbCoffRes*HgbConsult;

        if( fabs(HgbRes - 0.000001) < 0.000001 )
        {
            hgb = 0;
        }
        else
        {
            double val_0476 = 500.0;
            if( (HgbRes < val_0476) || ( fabs( HgbRes - val_0476 ) < 0.000001 ))
            {
                hgb = (int)HgbRes;
            }
            else
            {
                hgb = 0xd8f0;    
            }
        }    

        if( hgb <= 5 )
            if( Alg::t200 == 0 ) 
            {
                hgb = 0;    
            }    
    }
    return hgb;
}



void Plt_Result_And_Graph_Data_Process()
{
    int iCount = 0;
    int plt = 0;
    int pdw = 0;
    int mpv = 0;
    int pct = 0;
    int plcr = 0;  
    int hgb = 0;
    int mchc = 0;
    int mch  = 0;

    int graph_paint_max_val = 0;
    int max;

    int width = 0;
    int sum_add_res = 0;

    int ResAdd1;
    int ResAdd2;

    double tmp = 0.0;
    double add_res = 0.0;
    double PlcrResAdd = 0.0;

    Cell_Classifying_Function(&plt_data); 
    for( iCount = 0;iCount < plt_data.point_sum;iCount++ )
    {
        SysADBufData.PltHisGraph[iCount] = (unsigned char)plt_data.buf[ iCount ];    
    } 

    for( iCount = 0;iCount < SysTestResValBuf.plt_division_end;iCount++ )
    {
        if( SysADBufData.PltHisGraph[iCount] != 0 )    
        {
            SysTestResValBuf.plt_division_begin = iCount;
            break;
        }
    }    

    sum_add_res = 0;
    for( iCount = 0;iCount < SysTestResValBuf.plt_division_end;iCount++ )
    {
        sum_add_res = sum_add_res + plt_data.graph_buf[ iCount ];    
    }

    add_res = 0.0;
    for( iCount = 0;iCount < SysTestResValBuf.plt_division_end;iCount++ )
    {
        tmp = plt_data.graph_buf[ iCount ]*iCount*1.00;
        add_res = add_res + tmp;    
    }

    if( val_34ad == 0 )
    {
        tmp = sum_add_res*0.30240;
        tmp = tmp/2.5641;
        tmp = tmp*1.3763;
        plt = (int)tmp;

        plt = (int)(plt*syscalval.cl_PLT);
    } 
    else if( val_34ad == 1 )
    {
        tmp = sum_add_res*0.30240;
        tmp = tmp/2.5641;
        tmp = tmp*1.3763;
        plt = (int)tmp;

        plt = (int)(plt*syscalval.cl_PLT);
    } 
    else if( val_34ad == 2 )
    {
        tmp = sum_add_res*0.30240;
        tmp = tmp/2.5641;
        tmp = ((tmp*1.3745)*1.968);
        plt = (int)tmp;

        plt = (int)(plt*syscalval.cl_PLT);
    }  

    if( plt < 0x0000 )
    {
        plt = 0xd8f0;    
    }
    else
    {
        if( plt <= 0x0bb8 )    
        {
                if(SysTestResValBuf.wbc < 5 || SysTestResValBuf.rbc < 10) //2014-5-16
                {
                    if( plt <= 0x0013 ) 
                    {
                        plt = 0;
                    }
                    else
                    {
                        plt = plt - 0x0014;    
                    }
                }
        }
        else
        {
            plt = 0xd8f0;    
        }
    }

    if( plt == 0xd8f0 )
    {
        graph_paint_max_val = 0;
    }
    else
    {
        if( plt > 0 )
        {
            if( plt <= 0x003c )
            {
                graph_paint_max_val = plt + 0x000a;    
            }
            else
            {
                graph_paint_max_val = 0x0046;    
            }
        }
        else
        {
            graph_paint_max_val = 0;    
        }    
    }

    max = 0;
    for( iCount = 0;iCount < 0x0075;iCount++ )
    {
        if( SysADBufData.PltHisGraph[ iCount ] >= max )
        {
            max = (int)SysADBufData.PltHisGraph[ iCount ];    
        }    
    }

    for( iCount = 0;iCount < plt_data.point_sum;iCount++ )
    {
        if( SysADBufData.PltHisGraph[ iCount ] >= max )
        {
            SysADBufData.PltHisGraph[ iCount ] = max;
        }    
    }  

    for( iCount = 0;iCount < plt_data.point_sum;iCount++ )
    {
        if( max != 0)
        {
            mainWindowData.Point_PLT[ iCount ] = (unsigned char)((SysADBufData.PltHisGraph[ iCount ]*graph_paint_max_val/(max*1.0)));       
        }
        else
        {
            mainWindowData.Point_PLT[ iCount ] = 0x00;
        }
    }  

    if( !plt )
    {
        for( iCount = 0;iCount < plt_data.point_sum;iCount++ )
            mainWindowData.Point_PLT[ iCount ] = 0x00;
    }


    if( (plt == 0) || (plt == 0xd8f0))
    {
        pdw     = 0xd8f0;
    }
    else
    {
        width   = SEARCHDISTRIBUTINGWIDTH(SysTestResValBuf.plt_division_begin,SysTestResValBuf.plt_division_end,&plt_data);
        pdw     = (int)( width*2.57 );  
        pdw     = (int)(pdw*results_coefficient.PDW);      

    }

    if( pdw < 0 || pdw > 0x012c  )
    {
        pdw     = 0xd8f0;    
    }

    if( (plt == 0) || (plt == 0xd8f0) || (sum_add_res == 0) )
    {
        plcr = 0xd8f0;    
    }
    else
    {
        ResAdd1 = 0;
        ResAdd2 = 0;    

        for( iCount = SysTestResValBuf.plt_division_begin;iCount < SysTestResValBuf.plt_division_end;iCount++ )
        {
            ResAdd1 = ResAdd1 + (int)SysADBufData.PltHisGraph[iCount];    
        }  

        for( iCount = 0x0034;iCount < SysTestResValBuf.plt_division_end;iCount++ )
        {
            ResAdd2 = ResAdd2 + (int)SysADBufData.PltHisGraph[iCount];    
        }

        PlcrResAdd = ResAdd2/(ResAdd1*1.0);
        plcr = (int)(PlcrResAdd*100.0*10.0);  
        plcr = (int)(plcr*results_coefficient.PLCR);
    }

    if( (plcr < 0) || (plcr > 0x03e7) )
    {
        plcr = 0xd8f0;         
    }

    if( (plt == 0) || (plt == 0xd8f0) || (sum_add_res == 0) )
    {
        mpv = 0xd8f0;
    }
    else
    {
        mpv = (int)(((add_res*2.75)/(sum_add_res*1.0))*0.8);
        mpv  = (int)(mpv*results_coefficient.MPV);
    } 

    if( (mpv < 0) || (mpv > 0x012c) )
    {
        mpv = 0xd8f0;    
    } 

    pct = (int)((mpv*plt)/1000.0);
    pct=(int)(pct* results_coefficient.PCT);
    if( pct < 0 || pct > 0x03e7 || mpv == 0xd8f0 )
    {
        pct = 0xd8f0;        
    }

    if( Alg::t204 == 6 )
    {
        hgb = 0x0086;
    }
    else
    {
        const unsigned short int val_34dd = 0;
        if( val_34dd == 0 )
        {
            //μ÷ó??ó?ú????HGB
            hgb = Hgb_Result_Process();      
            hgb = (int)(hgb*(syscalval.cl_HGB));
        }
    }

    if( (hgb < 0) || (hgb > 0x01F4) )
    {
        hgb = 0xd8f0;    
    }

    if((hgb == 0xd8f0) || (SysTestResValBuf.hct == 0) || (SysTestResValBuf.hct == 0xd8f0)  )
    {
        mchc = 0xd8f0;
    }
    else
    {
        mchc = (int)((hgb*1000.0)/(SysTestResValBuf.hct*1.0));
        mchc =(int)(mchc *results_coefficient.MCHC);
        if( (mchc < 0) || ( mchc > 0x270f ) )
        {
            mchc = 0xd8f0;
        }
    }

    if( (SysTestResValBuf.rbc == 0) || (SysTestResValBuf.rbc == 0xd8f0) || (hgb == 0xd8f0) || (SysTestResValBuf.rbc < 0x000a) )
    {
        mch = 0xd8f0;    
    }
    else
    {
        mch = (int)((hgb*1000.0)/SysTestResValBuf.rbc);
        mch = (int)(mch*results_coefficient.MCH);
        if( (mch < 0) || ( mch > 0x270f ) )
        {
            mch = 0xd8f0;
        }        
    }

    if( val_34ad == 2 )
    {
        if ((hgb != 0)&&(hgb != 0xd8f0))
        {
                hgb = (int)(hgb*2.671);
        }
        
        if ((mch != 0)&&(mch != 0xd8f0))
        {
                mch = (int)(mch*2.66);
        }
        
        if ((mchc != 0)&&(mchc != 0xd8f0))
        {
                mchc = (int)(mchc*2.61);
        }

    }    

    SysTestResValBuf.pdw  = pdw;
    SysTestResValBuf.plcr = plcr;
    SysTestResValBuf.mpv  = mpv;
    SysTestResValBuf.pct  = pct;
    SysTestResValBuf.mch  = mch;
    SysTestResValBuf.plt  = plt;
    SysTestResValBuf.mchc = mchc;
    SysTestResValBuf.hgb  = hgb;
}

    // 算法初始化
    bool init()
    {
        qDebug() << "Alg init";

        // 算法结果初始化
        Alg::Init_Sys_Sampling_Data();
        Alg::Init_Consultion_Template_Data();
        Alg::init_SysresData();
        Alg::Init_SysInfo();
        Alg::Init_SysCalVal();

        return true;
    }

    //
    // 算法输入
    //
    void setModes(const Modes& modes)
    {
        s_modes = modes;
    }

    void setSysInfo(float lym, float mid, int lym_line, int mid_line)
    {
        SetSysInfoData.lym = lym;
        SetSysInfoData.mid = mid;
        SetSysInfoData.lym_line = lym_line;
        SetSysInfoData.mid_line = mid_line;
    }

    void setSysEvtBuf(unsigned short t200, unsigned short t204)
    {
        Alg::t200 = t200;
        Alg::t204 = t204;
    }

    void setCal(float cl_WBC, float cl_RBC, float cl_HGB, float cl_MCV, float cl_PLT)
    {
        syscalval.cl_WBC = cl_WBC;
        syscalval.cl_RBC = cl_RBC;
        syscalval.cl_HGB = cl_HGB;
        syscalval.cl_MCV = cl_MCV;
        syscalval.cl_PLT = cl_PLT;
    }

    void setMaintanceVal(int L1HIGH, int G1LOW, int L2HIGH, int G2LOW, int R1, int R2, int R3, int R4, int WBC, int RBC)
    {
        maintenance_val.maintenanceVal[0] = L1HIGH;
        maintenance_val.maintenanceVal[1] = G1LOW;
        maintenance_val.maintenanceVal[2] = L2HIGH;
        maintenance_val.maintenanceVal[3] = G2LOW;
        maintenance_val.maintenanceVal[4] = R1;
        maintenance_val.maintenanceVal[5] = R2;
        maintenance_val.maintenanceVal[6] = R3;
        maintenance_val.maintenanceVal[7] = R4;
        maintenance_val.maintenanceVal[8] = WBC;
        maintenance_val.maintenanceVal[9] = RBC;
    }

    // 算法模拟
    void simulate()
    {
        qsrand(QTime::currentTime().msecsTo(QTime(0, 0, 0)));
        float random = (qrand() % 10) * 0.1;

        SysTestResValBuf.wbc = 1.0 + random;
        SysTestResValBuf.plym = 2.0 + random;
        SysTestResValBuf.pmid = 3.0 + random;
        SysTestResValBuf.pgran = 4.0 + random;
        SysTestResValBuf.vlym = 5.0 + random;
        SysTestResValBuf.vmid = 6.0 + random;
        SysTestResValBuf.vgran = 7.0 + random;

        SysTestResValBuf.rbc = 8.0 + random;
        SysTestResValBuf.mcv = 9.0 + random;
        SysTestResValBuf.hct = 10.0 + random;
        SysTestResValBuf.rdw_cv = 11.0 + random;
        SysTestResValBuf.rdw_sd = 12.0 + random;

        SysTestResValBuf.plt = 13.0 + random;
        SysTestResValBuf.mpv = 14.0 + random;
        SysTestResValBuf.pdw = 15.0 + random;
        SysTestResValBuf.pct = 16.0 + random;
        SysTestResValBuf.plcr = 17.0 + random;

        SysTestResValBuf.hgb = 18.0 + random;
        SysTestResValBuf.mch = 19.0 + random;
        SysTestResValBuf.mchc = 20.0 + random;
    }

    // 算法计算
    void calculate()
    {
        // 脉冲识别（输入：原始脉冲；输出：DATA_SAMPLING对象）
        DmaBuf* dmaBuf = Dma::getDmaBuf();
        if (dmaBuf)
        {
            Alg::calculate(dmaBuf->pWbcSamplingBuf, dmaBuf->wbcSamplingBufLen, dmaBuf->pRbcSamplingBuf, dmaBuf->rbcSamplingBufLen, 
                           dmaBuf->pPltSamplingBuf, dmaBuf->pltSamplingBufLen, dmaBuf->hgbAdVoltage, dmaBuf->hgbBkVoltage);
        }
        else
        {
            qWarning() << "Alg calculate getDmaBuf fail";
        }
    }

    void calculate(char* wbcDataBuf, long wbcDataLen, char* rbcDataBuf, long rbcDataLen, 
                   char* pltDataBuf, long pltDataLen, int hgbAdVoltage, unsigned int hgbBkVoltage)
    {
        qDebug() << "Alg calculate";

        // 脉冲识别
        Pulse_Statistical_Process(&wbc_data, (unsigned char*)wbcDataBuf, wbcDataLen);
        Pulse_Statistical_Process(&rbc_data, (unsigned char*)rbcDataBuf, rbcDataLen);
        Pulse_Statistical_Process(&plt_data, (unsigned char*)pltDataBuf, pltDataLen);

        // 参数计算，直方图处理
        Wbc_Result_And_Graph_Data_Process(); 
        Rbc_Result_And_Graph_Data_Process();          
        Plt_Result_And_Graph_Data_Process();

        int iCount = 0;
        int almRmCount = 0;

        int almst = 0;
        int almed = 0;

        float scaleGene = 0.0;
        int scaleVal = 0x0020;

        float acctmp1 = 0.0; 
        float acctmp2 = 0.0; 

        float addSum = 0.0;
        float alermaddSum = 0.0;

        if( SysTestResValBuf.wbc > 5 )        
        {
            addSum = 0.0;
            for( iCount = 0;iCount < 0x00ff;iCount++ )
                addSum = addSum + mainWindowData.Point_WBC[iCount] * 1.0;
            addSum = addSum + SysTestResValBuf.wr_graph_gene * 1.0;
            if((addSum > 4.0) || (fabs(addSum-4.0) < 0.000001))
            {
                scaleGene = 75.0/102.0;
                almst = (int)((scaleGene*scaleVal) - 2.0);
                almed = (int)((scaleGene*scaleVal) + 3.0);
                alermaddSum = 0.0;
                for( iCount = almst;iCount < almed;iCount++ )
                    alermaddSum = alermaddSum + mainWindowData.Point_WBC[iCount] * 1.0;            
                acctmp1 = maintenance_val.maintenanceVal[4]/1000.0;
                acctmp2 = alermaddSum/addSum;
                if((acctmp2 > acctmp1 ) || (fabs(acctmp1 - acctmp2) < 0.000001))
                {
                    __SetBit(1,1,&(SysTestResValBuf.abnormity));
                    almRmCount++;
                }

                if( val_34ad == 0 )
                {
                    scaleGene = 75.0/102.0;
                    almst = (int)((maintenance_val.maintenanceVal[0] - val_2522)*scaleGene - 2.0);
                    almed = (int)((maintenance_val.maintenanceVal[0] - val_2522)*scaleGene + 3.0);             
                }
                else if( val_34ad == 1 )
                {
                    scaleGene = 75.0/102.0;
                    almst = (int)((90.0 - val_2522)*scaleGene - 2.0);
                    almed = (int)((90.0 - val_2522)*scaleGene + 3.0);             
                } 
                else if( val_34ad == 2 )
                {
                    scaleGene = 75.0/102.0;
                    almst = (int)((maintenance_val.maintenanceVal[2] - val_2522)*scaleGene - 2.0);
                    almed = (int)((maintenance_val.maintenanceVal[2] - val_2522)*scaleGene + 3.0);             
                }           
                alermaddSum = 0.0; 
                for( iCount = almst;iCount < almed;iCount++ )
                    alermaddSum = alermaddSum + mainWindowData.Point_WBC[iCount] * 1.0;   
                acctmp1 = maintenance_val.maintenanceVal[5]/1000.0;
                acctmp2 = alermaddSum/addSum;
                if((acctmp2 > acctmp1 ) || (fabs(acctmp1 - acctmp2) < 0.000001))
                {
                    __SetBit(1,2,&(SysTestResValBuf.abnormity));    
                    almRmCount++; 
                }

                if( val_34ad == 0 )
                {
                    scaleGene = 75.0/102.0;
                    almst = (int)((maintenance_val.maintenanceVal[1] - val_2522)*scaleGene - 2.0);
                    almed = (int)((maintenance_val.maintenanceVal[1] - val_2522)*scaleGene + 3.0);             
                }
                else if( val_34ad == 1 )
                {
                    scaleGene = 75.0/102.0;
                    almst = (int)((125.0 - val_2522)*scaleGene - 2.0);
                    almed = (int)((125.0 - val_2522)*scaleGene + 3.0);             
                } 
                else if( val_34ad == 2 )
                {
                    scaleGene = 75.0/102.0;
                    almst = (int)((maintenance_val.maintenanceVal[3] - val_2522)*scaleGene - 2.0);
                    almed = (int)((maintenance_val.maintenanceVal[3] - val_2522)*scaleGene + 3.0);             
                }           
                alermaddSum = 0.0; 
                for( iCount = almst;iCount < almed;iCount++ )
                    alermaddSum = alermaddSum + mainWindowData.Point_WBC[iCount] * 1.0;   
                acctmp1 = maintenance_val.maintenanceVal[6]/1000.0;
                acctmp2 = alermaddSum/addSum;
                if((acctmp2 > acctmp1 ) || (fabs(acctmp1 - acctmp2) < 0.000001))
                {
                    __SetBit(1,3,&(SysTestResValBuf.abnormity));            
                    almRmCount++; 
                }                   

                alermaddSum = SysTestResValBuf.wr_graph_gene * 1.0;
                acctmp1 = maintenance_val.maintenanceVal[7]/1000.0;
                acctmp2 = alermaddSum/addSum;
                if((acctmp2 > acctmp1 ) || (fabs(acctmp1 - acctmp2) < 0.000001))
                {
                    __SetBit(1,4,&(SysTestResValBuf.abnormity));  
                    almRmCount++; 
                }

                if( almRmCount >= 2 )
                {
                    __SetBit(1,0,&(SysTestResValBuf.abnormity));  
                } 
            }

        }

        qDebug() << "Alg calculate end";
    }


    //
    // 算法输出
    //

    // 通道故障
    bool wbcClog()
    {
        return (0 < WBC_err_id);
    }

    bool rbcClog()
    {
        return (0 < RBC_err_id || 0 < PLT_err_id);
    }
    
    bool hgbError()
    {
        return (1 == val_3564);
    }

    bool hgbBubble()
    {
        return (2 == val_3564);
    }

    int wr_graph_gene()
    {
        return SysTestResValBuf.wr_graph_gene;
    }

    // 算法结果
    HistInfo wbcHist()
    {
        HistInfo histInfo;

        histInfo.dataLen = 256;
        for (int i = 0; i < histInfo.dataLen; i++)
        {
            histInfo.datas[i] = mainWindowData.Point_WBC[i];
        }

        histInfo.lineLen = 4;
        histInfo.lines[0] = SysTestResValBuf.wbc_division_begin;
        histInfo.lines[1] = SysTestResValBuf.lym_division_begin;
        histInfo.lines[2] = SysTestResValBuf.mid_division_begin;
        histInfo.lines[3] = SysTestResValBuf.wbc_division_end;

        return histInfo;
    }

    HistInfo rbcHist()
    {
        HistInfo histInfo;

        histInfo.dataLen = 256;
        for (int i = 0; i < histInfo.dataLen; i++)
        {
            histInfo.datas[i] = mainWindowData.Point_RBC[i];
        }

        histInfo.lineLen = 2;
        histInfo.lines[0] = SysTestResValBuf.rbc_division_begin;
        histInfo.lines[1] = SysTestResValBuf.rbc_division_end;

        return histInfo;
    }

    HistInfo pltHist()
    {
        HistInfo histInfo;

        histInfo.dataLen = 128;
        for (int i = 0; i < histInfo.dataLen; i++)
        {
            histInfo.datas[i] = mainWindowData.Point_PLT[i];
        }

        histInfo.lineLen = 2;
        histInfo.lines[0] = SysTestResValBuf.plt_division_begin;
        histInfo.lines[1] = SysTestResValBuf.plt_division_end;

        return histInfo;
    }

    ParaList paraResult()
    {
        ParaList paraList;

        {
            int value = SysTestResValBuf.wbc;
            int flag = (((0xd8f0 == value) || (value < 0)) ? PARA_STAR_FLAG : PARA_NORMAL_FLAG);
            paraList.appendPara(PARA_WBC, value / 10.0, flag);
        }
        {
            int value = SysTestResValBuf.plym;
            int flag = (((0xd8f0 == value) || (value < 0)) ? PARA_STAR_FLAG : PARA_NORMAL_FLAG);
            paraList.appendPara(PARA_LYM_PER, value / 10.0, flag);
        }
        {
            int value = SysTestResValBuf.pmid;
            int flag = (((0xd8f0 == value) || (value < 0)) ? PARA_STAR_FLAG : PARA_NORMAL_FLAG);
            paraList.appendPara(PARA_MID_PER, value / 10.0, flag);
        }
        {
            int value = SysTestResValBuf.pgran;
            int flag = (((0xd8f0 == value) || (value < 0)) ? PARA_STAR_FLAG : PARA_NORMAL_FLAG);
            paraList.appendPara(PARA_GRAN_PER, value / 10, flag);
        }
        {
            int value = SysTestResValBuf.vlym;
            int flag = (((0xd8f0 == value) || (value < 0)) ? PARA_STAR_FLAG : PARA_NORMAL_FLAG);
            paraList.appendPara(PARA_LYM_NUM, value / 10.0, flag);
        }
        {
            int value = SysTestResValBuf.vmid;
            int flag = (((0xd8f0 == value) || (value < 0)) ? PARA_STAR_FLAG : PARA_NORMAL_FLAG);
            paraList.appendPara(PARA_MID_NUM, value / 10.0, flag);
        }
        {
            int value = SysTestResValBuf.vgran;
            int flag = (((0xd8f0 == value) || (value < 0)) ? PARA_STAR_FLAG : PARA_NORMAL_FLAG);
            paraList.appendPara(PARA_GRAN_NUM, value / 10.0, flag);
        }


        {
            int value = SysTestResValBuf.rbc;
            int flag = (((0xd8f0 == value) || (value < 0)) ? PARA_STAR_FLAG : PARA_NORMAL_FLAG);
            paraList.appendPara(PARA_RBC, value / 100.0, flag);
        }
        {
            int value = SysTestResValBuf.hct;
            int flag = (((0xd8f0 == value) || (value < 0)) ? PARA_STAR_FLAG : PARA_NORMAL_FLAG);
            paraList.appendPara(PARA_HCT, value / 10.0, flag);
        }
        {
            int value = SysTestResValBuf.mcv;
            int flag = (((0xd8f0 == value) || (value < 0)) ? PARA_STAR_FLAG : PARA_NORMAL_FLAG);
            paraList.appendPara(PARA_MCV, value / 10.0, flag);
        }
        {
            int value = SysTestResValBuf.mch;
            int flag = (((0xd8f0 == value) || (value < 0)) ? PARA_STAR_FLAG : PARA_NORMAL_FLAG);
            paraList.appendPara(PARA_MCH, value / 10.0, flag);
        }
        {
            int value = SysTestResValBuf.mchc;
            int flag = (((0xd8f0 == value) || (value < 0)) ? PARA_STAR_FLAG : PARA_NORMAL_FLAG);
            paraList.appendPara(PARA_MCHC, value / 1.0, flag);
        }
        {
            int value = SysTestResValBuf.rdw_sd;
            int flag = (((0xd8f0 == value) || (value < 0)) ? PARA_STAR_FLAG : PARA_NORMAL_FLAG);
            paraList.appendPara(PARA_RDW_SD, value / 10.0, flag);
        }
        {
            int value = SysTestResValBuf.rdw_cv;
            int flag = (((0xd8f0 == value) || (value < 0)) ? PARA_STAR_FLAG : PARA_NORMAL_FLAG);
            paraList.appendPara(PARA_RDW_CV, value / 10.0, flag);
        }


        {
            int value = SysTestResValBuf.plt;
            int flag = (((0xd8f0 == value) || (value < 0)) ? PARA_STAR_FLAG : PARA_NORMAL_FLAG);
            paraList.appendPara(PARA_PLT, value / 1.0, flag);
        }
        {
            int value = SysTestResValBuf.mpv;
            int flag = (((0xd8f0 == value) || (value < 0)) ? PARA_STAR_FLAG : PARA_NORMAL_FLAG);
            paraList.appendPara(PARA_MPV, value / 10.0, flag);
        }
        {
            int value = SysTestResValBuf.pdw;
            int flag = (((0xd8f0 == value) || (value < 0)) ? PARA_STAR_FLAG : PARA_NORMAL_FLAG);
            paraList.appendPara(PARA_PDW, value / 10.0, flag);
        }
        {
            int value = SysTestResValBuf.pct;
            int flag = (((0xd8f0 == value) || (value < 0)) ? PARA_STAR_FLAG : PARA_NORMAL_FLAG);
            paraList.appendPara(PARA_PCT, value / 100.0, flag);
        }
        {
            int value = SysTestResValBuf.plcr;
            int flag = (((0xd8f0 == value) || (value < 0)) ? PARA_STAR_FLAG : PARA_NORMAL_FLAG);
            paraList.appendPara(PARA_PLCR, value / 10.0, flag);
        }


        {
            int value = SysTestResValBuf.hgb;
            int flag = (((0xd8f0 == value) || (value < 0)) ? PARA_STAR_FLAG : PARA_NORMAL_FLAG);
            paraList.appendPara(PARA_HGB, value / 1.0, flag);
        }

        return paraList;
    }
}