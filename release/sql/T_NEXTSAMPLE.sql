Create TABLE T_NEXTSAMPLE(
[F_ID] integer PRIMARY KEY NOT NULL
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
  
);