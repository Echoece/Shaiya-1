USE [PS_UserData]
GO
/****** Object:  StoredProcedure [dbo].[usp_Try_GameLogout_R]    Script Date: 2/4/2021 8:14:42 PM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

ALTER Proc [dbo].[usp_Try_GameLogout_R]

@UserUID int,
@SessionID bigint,
@LogoutType smallint = 0,
@ErrType int = 0

AS

SET NOCOUNT ON

UPDATE UserLoginLog SET LogoutTime = GETDATE() WHERE UserUID = @UserUID AND SessionID = @SessionID

UPDATE Users_Master SET Leave = 0, LeaveDate = GETDATE() WHERE UserUID = @UserUID

SET NOCOUNT OFF
