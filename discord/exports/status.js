const addon = require("../addons/zynk")

module.exports = {
    name: "status",
    execute(message) {
        if (message.guild === null) {
            return
        }
        try {
            if (!addon.getProcessIdEx("ps_game.exe")) {
                message.channel.send("\\🔴")
            }
            else {
                message.channel.send("\\🟢")
            }
        }
        catch (error) {
            console.log(error)
            message.channel.send("`Error: server exploded`")
        }
    }
}
