USE [PS_GameData]
GO
/****** Object:  StoredProcedure [dbo].[usp_Save_Char_Name_E]    Script Date: 2/1/2021 5:28:36 PM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

ALTER Proc [dbo].[usp_Save_Char_Name_E]

@ServerID tinyint,
@CharID int,
@OldCharName nvarchar(18),
@NewCharName nvarchar(18)

AS

SET NOCOUNT ON

SET @OldCharName = LTRIM(RTRIM(REPLACE(@OldCharName, char(39), char(32))))
SET @NewCharName = LTRIM(RTRIM(REPLACE(@NewCharName, char(39), char(32))))

IF EXISTS (SELECT CharID FROM Chars WHERE CharName = @NewCharName AND Del = 0)
BEGIN
	RETURN -2
END

BEGIN TRANSACTION

UPDATE Chars SET CharName = @NewCharName, RenameCnt = RenameCnt - 1, OldCharName = @OldCharName 
WHERE CharID = @CharID AND Del = 0

IF @@ERROR <> 0
BEGIN
	GOTO ERROR_ROLLBACK
END

UPDATE Guilds SET MasterName = @NewCharName WHERE MasterCharID = @CharID

UPDATE FriendChars SET FriendName = @NewCharName WHERE FriendID = @CharID

UPDATE BanChars SET BanName = @NewCharName WHERE BanID = @CharID

INSERT INTO CharRenameLog(ServerID, CharID, CharName) VALUES(@ServerID, @CharID, @NewCharName)

COMMIT TRANSACTION
RETURN 1

ERROR_ROLLBACK:
RETURN -2

SET NOCOUNT OFF
