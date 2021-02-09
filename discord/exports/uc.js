const addon = require("../addons/zynk")

module.exports = {
    name: "uc",
    async execute(message) {
        if (message.guild === null) {
            return
        }
        if (!addon.getProcessIdEx("ps_game.exe")) {
            return message.reply("cannot process request.")
        }
        try {
            let result = await addon.userCount()
            message.channel.send("`User count: " + `${result}` + "`")
        }
        catch (error) {
            console.log(error)
            message.channel.send("`Error: server exploded`")
        }
    }
}
