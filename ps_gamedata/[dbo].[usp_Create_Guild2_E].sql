USE [PS_GameData]
GO
/****** Object:  StoredProcedure [dbo].[usp_Create_Guild2_E]    Script Date: 2/1/2021 4:49:05 PM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER OFF
GO

ALTER Proc [dbo].[usp_Create_Guild2_E]

@GuildID int,
@GuildName varchar(30),
@MasterUserID varchar(12),
@MasterCharID int,
@MasterName varchar(30),
@Country tinyint,
@Remark varchar(64) = NULL

AS

SET NOCOUNT ON

DECLARE @NameCnt int

SET @GuildName = LTRIM(RTRIM(REPLACE(@GuildName, char(39), char(32))))
SET @MasterName = LTRIM(RTRIM(REPLACE(@MasterName, char(39), char(32))))
SET @NameCnt = (SELECT ISNULL(COUNT(*), 0) FROM Guilds WHERE GuildName = @GuildName AND Del = 0)
SET @Remark = LTRIM(RTRIM(REPLACE(@Remark, char(39), char(32))))

IF @NameCnt <> 0
BEGIN
	RETURN -1
END

ELSE
BEGIN
	BEGIN TRAN
	INSERT INTO Guilds(GuildID, GuildName, MasterUserID, MasterCharID, MasterName, Country, TotalCount, GuildPoint, CreateDate)
	VALUES(@GuildID, @GuildName, @MasterUserID, @MasterCharID, @MasterName, @Country, 0, 0, GETDATE())

	IF @@ERROR <> 0
	BEGIN
		ROLLBACK TRAN
		RETURN -1
	END

	INSERT INTO GuildDetails(GuildID, Remark) VALUES(@GuildID, @Remark)

	IF @@ERROR <> 0
	BEGIN
		ROLLBACK TRAN
		RETURN -1
	END

	COMMIT TRAN
	RETURN 0
END

SET NOCOUNT OFF
