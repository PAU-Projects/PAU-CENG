USE [myTestDB]
GO
/****** Object:  StoredProcedure [dbo].[TranTest2]    Script Date: 15.12.2014 13:58:16 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
ALTER Proc [dbo].[TranTest2]
AS BEGIN TRAN 
INSERT INTO [t1]([id], [t1_value]) VALUES ('9', '9') 
IF @@ERROR <> 0 
	BEGIN 
		ROLLBACK TRAN 
		return 10
	END
UPDATE t1 SET id = '9' WHERE t1_value = '8' 
IF @@ERROR <> 0 
	BEGIN 
		ROLLBACK TRAN 
		return 11 
	END
COMMIT TRAN 
