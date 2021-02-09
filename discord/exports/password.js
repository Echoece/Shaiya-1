const mssql = require("mssql")
const syntax = "Required syntax: `!pwd username old-password new-password`"
var isHuman = false

async function createCaptcha() {
    let captcha = Math.random().toString(36).slice(2, 8)
    return captcha
}

function updatePassword(username, password) {
    const command = `UPDATE PS_UserData.dbo.Users_Master \
    SET Pw = '${password}' \
    WHERE UserID = '${username}';`
    new mssql.Request().query(command, (err) => {
        if (err) {
            console.log(err)
            return 0
        }
    })
}

module.exports = {
    name: "pwd",
    async execute(message, argv) {
        if (message.guild) {
            await message.delete()
            return message.reply("!pwd requires direct message.")
        }
        if (!argv[0] || 
            !argv[1] || 
            !argv[2] || argv[3]) {
            return message.author.send(syntax)
        }
        if (argv[2].length < 4 || 
            argv[2].length > 16 || 
            /[^A-Za-z0-9]/.test(argv[2])) {
            return message.author.send("Password requires 4 to 16 alphanumerics.")
        }
        const captcha = await createCaptcha()
        const msg = "Respond within 10 seconds using this code: " + "`" + `${captcha}` + "`"
        await message.author.send(msg)
        const filter = m => m.author.id === message.author.id
        await message.channel.awaitMessages(filter, {
            max: 1,
            time: 10000,
            errors: ['time'],
        })
        .then((collected) => {
            response = collected.first().content
            if (response === captcha) {
                isHuman = true
                return message.author.send("Processing request...")
            } 
            else if (response != captcha) {
                isHuman = false
                return message.author.send("Invalid code: " + "`" + `${response}` + "`")
            }
        })
        .catch(() => {
            isHuman = false
            message.author.send("Request expired.")
        })
        if (isHuman === false) {
            return
        }
        const command = `SELECT UserID, Pw \
        FROM PS_UserData.dbo.Users_Master \
        WHERE UserID = '${argv[0]}' \
        AND Pw = '${argv[1]}';`
        new mssql.Request().query(command, (err, result) => {
            if (err) { 
                console.log(err)
                return message.author.send("`Error: server exploded`")
            }
            if (result.rowsAffected == 0) {
                return message.author.send("Cannot process request.")
            }
            if (updatePassword(argv[0], argv[2]) == 0) {
                return message.author.send("`Error: server exploded`")
            }
            message.author.send("Request processed.")
        })
    }   
}
