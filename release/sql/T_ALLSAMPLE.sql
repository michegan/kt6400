Begin Transaction;
Create  TABLE MAIN.[Temp_491878528](
[F_ID] integer NOT NULL
,[F_SID] nvarchar(20)
,[F_WORKMODE] integer
,[F_SAMPLEMODE] integer
,[F_SPECIESMODE] integer
,[F_BLOODMODE] integer
,[F_ANALYSISMODE] integer
,[F_PREPROCESSMODE] integer
,[F_SENDER] nvarchar(16)
,[F_SEND_TIME] datetime
,[F_TESTER] nvarchar(16)
,[F_TEST_TIME] datetime
,[F_CHECKER] nvarchar(16)
,[F_CHECK_TIME] datetime
,[F_PID] nvarchar(16)
,[F_NAME] nvarchar(16)
,[F_GENDER] nvarchar(16)
,[F_AGE] nvarchar(16)
,[F_DEPARTMENT] nvarchar(16)
,[F_BED_NO] nvarchar(16)
,[F_COMMENT] nvarchar(256)
,[F_WBC] float
,[F_WBC_FLAG] integer
,[F_WBC_LOW] float
,[F_WBC_HIGH] float
,[F_LYM_PER] float
,[F_LYM_PER_FLAG] integer
,[F_LYM_PER_LOW] float
,[F_LYM_PER_HIGH] float
,[F_MID_PER] float
,[F_MID_PER_FLAG] integer
,[F_MID_PER_LOW] float
,[F_MID_PER_HIGH] float
,[F_GRAN_PER] float
,[F_GRAN_PER_FLAG] interg
,[F_GRAN_PER_LOW] float
,[F_GRAN_PER_HIGH] float
,[F_LYM_NUM] float
,[F_LYM_NUM_FLAG] integer
,[F_LYM_NUM_LOW] float
,[F_LYM_NUM_HIGH] float
,[F_MID_NUM] float
,[F_MID_NUM_FLAG] integer
,[F_MID_NUM_LOW] float
,[F_MID_NUM_HIGH] float
,[F_GRAN_NUM] float
,[F_GRAN_NUM_FLAG] integer
,[F_GRAN_NUM_LOW] float
,[F_GRAN_NUM_HIGH] float
,[F_RBC] float
,[F_RBC_FLAG] integer
,[F_RBC_LOW] float
,[F_RBC_HIGH] float
,[F_HGB] float
,[F_HGB_FLAG] integer
,[F_HGB_LOW] float
,[F_HGB_HIGH] float
,[F_HCT] float
,[F_HCT_FLAG] integer
,[F_HCT_LOW] float
,[F_HCT_HIGH] float
,[F_MCH] float
,[F_MCH_FLAG] integer
,[F_MCH_LOW] float
,[F_MCH_HIGH] float
,[F_MCV] float
,[F_MCV_FLAG] integer
,[F_MCV_LOW] float
,[F_MCV_HIGH] float
,[F_MCHC] float
,[F_MCHC_FLAG] integer
,[F_MCHC_LOW] float
,[F_MCHC_HIGH] float
,[F_RDW_SD] float
,[F_RDW_SD_FLAG] integer
,[F_RDW_SD_LOW] float
,[F_RDW_SD_HIGH] float
,[F_RDW_CV] float
,[F_RDW_CV_FLAG] integer
,[F_RDW_CV_LOW] float
,[F_RDW_CV_HIGH] float
,[F_PLT] float
,[F_PLT_FLAG] integer
,[F_PLT_LOW] float
,[F_PLT_HIGH] float
,[F_MPV] float
,[F_MPV_FLAG] integer
,[F_MPV_LOW] float
,[F_MPV_HIGH] float
,[F_PCT] float
,[F_PCT_FLAG] integer
,[F_PCT_LOW] float
,[F_PCT_HIGH] float
,[F_PDW] float
,[F_PDW_FLAG] integer
,[F_PDW_LOW] float
,[F_PDW_HIGH] float
,[F_PLCC] float
,[F_PLCC_FLAT] integer
,[F_PLCC_LOW] float
,[F_PLCC_HIGH] float
,[F_PLCR] float
,[F_PLCR_FLAG] 
,[F_PLCR_LOW] float
,[F_PLCR_HIGH] float
,[F_WBC_HIST] blob
,[F_RBC_HIST] blob
,[F_PLT_HIST] blob
,[F_WBC_LINE] blob
,[F_RBC_LINE] blob
,[F_PLT_LINE] blob
  
);
Insert Into MAIN.[Temp_491878528] ([F_ID],[F_SID],[F_WORKMODE],[F_SAMPLEMODE],[F_SPECIESMODE],[F_BLOODMODE],[F_ANALYSISMODE],[F_PREPROCESSMODE],[F_SENDER],[F_SEND_TIME],[F_TESTER],[F_TEST_TIME],[F_CHECKER],[F_CHECK_TIME],[F_PID],[F_NAME],[F_GENDER],[F_AGE],[F_DEPARTMENT],[F_BED_NO],[F_COMMENT],[F_WBC],[F_WBC_FLAG],[F_WBC_LOW],[F_WBC_HIGH],[F_LYM_PER],[F_LYM_PER_FLAG],[F_LYM_PER_LOW],[F_LYM_PER_HIGH],[F_MID_PER],[F_MID_PER_FLAG],[F_MID_PER_LOW],[F_MID_PER_HIGH],[F_GRAN_PER],[F_GRAN_PER_FLAG],[F_GRAN_PER_LOW],[F_GRAN_PER_HIGH],[F_LYM_NUM],[F_LYM_NUM_FLAG],[F_LYM_NUM_LOW],[F_LYM_NUM_HIGH],[F_MID_NUM],[F_MID_NUM_FLAG],[F_MID_NUM_LOW],[F_MID_NUM_HIGH],[F_GRAN_NUM],[F_GRAN_NUM_FLAG],[F_GRAN_NUM_LOW],[F_GRAN_NUM_HIGH],[F_RBC],[F_RBC_FLAG],[F_RBC_LOW],[F_RBC_HIGH],[F_HGB],[F_HGB_FLAG],[F_HGB_LOW],[F_HGB_HIGH],[F_HCT],[F_HCT_FLAG],[F_HCT_LOW],[F_HCT_HIGH],[F_MCH],[F_MCH_FLAG],[F_MCH_LOW],[F_MCH_HIGH],[F_MCV],[F_MCV_FLAG],[F_MCV_LOW],[F_MCV_HIGH],[F_MCHC],[F_MCHC_FLAG],[F_MCHC_LOW],[F_MCHC_HIGH],[F_RDW_SD],[F_RDW_SD_FLAG],[F_RDW_SD_LOW],[F_RDW_SD_HIGH],[F_RDW_CV],[F_RDW_CV_FLAG],[F_RDW_CV_LOW],[F_RDW_CV_HIGH],[F_PLT],[F_PLT_FLAG],[F_PLT_LOW],[F_PLT_HIGH],[F_MPV],[F_MPV_FLAG],[F_MPV_LOW],[F_MPV_HIGH],[F_PCT],[F_PCT_FLAG],[F_PCT_LOW],[F_PCT_HIGH],[F_PDW],[F_PDW_FLAG],[F_PDW_LOW],[F_PDW_HIGH],[F_PLCC],[F_PLCC_FLAT],[F_PLCC_LOW],[F_PLCC_HIGH],[F_PLCR],[F_PLCR_FLAG],[F_PLCR_LOW],[F_PLCR_HIGH],[F_WBC_HIST],[F_RBC_HIST],[F_PLT_HIST],[F_WBC_LINE],[F_RBC_LINE],[F_PLT_LINE]) 
 Select [F_ID],[F_SID],[F_WORKMODE],[F_SAMPLEMODE],[F_SPECIESMODE],[F_BLOODMODE],[F_ANALYSISMODE],[F_PREPROCESSMODE],[F_SENDER],[F_SEND_TIME],[F_TESTER],[F_TEST_TIME],[F_CHECKER],[F_CHECK_TIME],[F_PID],[F_NAME],[F_GENDER],[F_AGE],[F_DEPARTMENT],[F_BED_NO],[F_COMMENT],[F_WBC],[F_WBC_FLAG],[F_WBC_LOW],[F_WBC_HIGH],[F_LYM_PER],[F_LYM_PER_FLAG],[F_LYM_PER_LOW],[F_LYM_PER_HIGH],[F_MID_PER],[F_MID_PER_FLAG],[F_MID_PER_LOW],[F_MID_PER_HIGH],[F_GRAN_PER],[F_GRAN_PER_FLAG],[F_GRAN_PER_LOW],[F_GRAN_PER_HIGH],[F_LYM_NUM],[F_LYM_NUM_FLAG],[F_LYM_NUM_LOW],[F_LYM_NUM_HIGH],[F_MID_NUM],[F_MID_NUM_FLAG],[F_MID_NUM_LOW],[F_MID_NUM_HIGH],[F_GRAN_NUM],[F_GRAN_NUM_FLAG],[F_GRAN_NUM_LOW],[F_GRAN_NUM_HIGH],[F_RBC],[F_RBC_FLAG],[F_RBC_LOW],[F_RBC_HIGH],[F_HGB],[F_HGB_FLAG],[F_HGB_LOW],[F_HGB_HIGH],[F_HCT],[F_HCT_FLAG],[F_HCT_LOW],[F_HCT_HIGH],[F_MCH],[F_MCH_FLAG],[F_MCH_LOW],[F_MCH_HIGH],[F_MCV],[F_MCV_FLAG],[F_MCV_LOW],[F_MCV_HIGH],[F_MCHC],[F_MCHC_FLAG],[F_MCHC_LOW],[F_MCHC_HIGH],[F_RDW_SD],[F_RDW_SD_FLAG],[F_RDW_SD_LOW],[F_RDW_SD_HIGH],[F_RDW_CV],[F_RDW_CV_FLAG],[F_RDW_CV_LOW],[F_RDW_CV_HIGH],[F_PLT],[F_PLT_FLAG],[F_PLT_LOW],[F_PLT_HIGH],[F_MPV],[F_MPV_FLAG],[F_MPV_LOW],[F_MPV_HIGH],[F_PCT],[F_PCT_FLAG],[F_PCT_LOW],[F_PCT_HIGH],[F_PDW],[F_PDW_FLAG],[F_PDW_LOW],[F_PDW_HIGH],[F_PLCC],[F_PLCC_FLAT],[F_PLCC_LOW],[F_PLCC_HIGH],[F_PLCR],[F_PLCR_FLAG],[F_PLCR_LOW],[F_PLCR_HIGH],[F_WBC_HIST],[F_RBC_HIST],[F_PLT_HIST],[F_WBC_LINE],[F_RBC_LINE],[F_PLT_LINE] From MAIN.[T_ALLSAMPLE];
Drop Table MAIN.[T_ALLSAMPLE];
Alter Table MAIN.[Temp_491878528] Rename To [T_ALLSAMPLE];


Commit Transaction;