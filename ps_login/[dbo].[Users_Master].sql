USE [PS_UserData]
GO
/****** Object:  Table [dbo].[Users_Master]    Script Date: 2/6/2021 10:08:50 AM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

SET ANSI_PADDING ON
GO

CREATE TABLE [dbo].[Users_Master](
	[UserUID] [int] IDENTITY(1,1) NOT NULL,
	[UserID] [varchar](18) NOT NULL,
	[Pw] [varchar](32) NOT NULL,
	[JoinDate] [smalldatetime] NOT NULL,
	[Admin] [bit] NOT NULL,
	[AdminLevel] [tinyint] NOT NULL,
	[Status] [smallint] NOT NULL,
	[Leave] [tinyint] NOT NULL,
	[LeaveDate] [smalldatetime] NULL,
	[UserType] [char](1) NOT NULL,
	[UserIP] [varchar](15) NULL,
	[Point] [int] NOT NULL,
	[Email] [varchar](32) NULL,
	[Discord] [varchar](32) NULL,
 CONSTRAINT [PK_Users_Master] PRIMARY KEY CLUSTERED 
(
	[UserUID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO

SET ANSI_PADDING OFF
GO

ALTER TABLE [dbo].[Users_Master] ADD  CONSTRAINT [DF_Users_Master_Pw]  DEFAULT ('') FOR [Pw]
GO

ALTER TABLE [dbo].[Users_Master] ADD  CONSTRAINT [DF_Users_Master_JoinDate]  DEFAULT (getdate()) FOR [JoinDate]
GO

ALTER TABLE [dbo].[Users_Master] ADD  CONSTRAINT [DF_Users_Master_Admin]  DEFAULT ((0)) FOR [Admin]
GO

ALTER TABLE [dbo].[Users_Master] ADD  CONSTRAINT [DF_Users_Master_AdminLevel]  DEFAULT ((0)) FOR [AdminLevel]
GO

ALTER TABLE [dbo].[Users_Master] ADD  CONSTRAINT [DF_Users_Master_Status]  DEFAULT ((0)) FOR [Status]
GO

ALTER TABLE [dbo].[Users_Master] ADD  CONSTRAINT [DF_Users_Master_Leave]  DEFAULT ((0)) FOR [Leave]
GO

ALTER TABLE [dbo].[Users_Master] ADD  CONSTRAINT [DF_Users_Master_LeaveDate]  DEFAULT (dateadd(year,(10),getdate())) FOR [LeaveDate]
GO

ALTER TABLE [dbo].[Users_Master] ADD  CONSTRAINT [DF_Users_Master_UserType]  DEFAULT ('N') FOR [UserType]
GO

ALTER TABLE [dbo].[Users_Master] ADD  CONSTRAINT [DF_Users_Master_Point]  DEFAULT ((0)) FOR [Point]
GO
