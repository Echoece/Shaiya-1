const mssql = require("mssql")
const syntax = "Required syntax: `!ban mention`"
const roleId = "808120572486877234"

function updateStatus(userId) {
    const command = `UPDATE PS_UserData.dbo.Users_Master \
    SET Status = '-6' \
    WHERE Discord = '${userId}';`
    new mssql.Request().query(command, (err) => {
        if (err) {
            console.log(err)
            return 0
        }
    })
}

module.exports = {
    name: "ban",
    async execute(message, argv) {
        if (message.guild === null) {
            return
        }
        if (!message.member.roles.cache.has(roleId)) {
            return message.reply("permission denied.")
        }
        if (!argv[0] || argv[1]) {
            return message.reply(syntax)
        }
        try {
            let userId = await message.mentions.users.first().id
            if (updateStatus(userId) == 0) {
                return message.reply("cannot process request.")
            }
            return message.reply("request processed.")
        }
        catch (error) {
            return message.reply("cannot process request.")
        }
    }   
}
