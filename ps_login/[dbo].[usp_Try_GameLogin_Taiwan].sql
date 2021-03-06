USE [PS_UserData]
GO
/****** Object:  StoredProcedure [dbo].[usp_Try_GameLogin_Taiwan]    Script Date: 2/4/2021 3:59:39 AM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

ALTER Proc [dbo].[usp_Try_GameLogin_Taiwan]

@UserID varchar(18),
@Password varchar(32),
@SessionID bigint,
@UserIP varchar(15),
@UserUID int = 0,
@LoginType smallint = 1, 
@LoginTime datetime = NULL

AS

SET NOCOUNT ON

DECLARE @Leave tinyint, @Status smallint, @Pw varchar(32)

SET @LoginTime = GETDATE()
SET @UserIP = LTRIM(RTRIM(@UserIP))

SELECT @UserUID = [UserUID], @Pw = Pw, @Status = [Status], @Leave = [Leave]
FROM Users_Master 
WHERE UserID = @UserID

IF @UserUID = 0
BEGIN
	SET @Status = -3
END

IF @Leave = 1
BEGIN
	SET @Status = -6
END

IF @Pw <> @Password
BEGIN
	SET @Status = -1
END

/*IF EXISTS (SELECT @UserIP FROM Users_Master WHERE Leave = 1)
BEGIN
	SET @Status = -6
END*/

SELECT @Status AS [Status], @UserUID AS UserUID

IF @Status = 0 OR @Status = 16 OR @Status = 32 OR @Status = 48 OR @Status = 64 OR @Status = 80
BEGIN
    UPDATE Users_Master SET Leave = 1, JoinDate = GETDATE() WHERE UserUID = @UserUID
	
	UPDATE Users_Master SET UserIP = @UserIP WHERE UserUID = @UserUID
	
    EXEC usp_Insert_LoginLog_E @SessionID = @SessionID, @UserUID = @UserUID, @UserIP = @UserIP, @LogType = 0, @LogTime = @LoginTime, @LoginType = @LoginType
END

SET NOCOUNT OFF
