const exec = require("child_process").execFile
const addon = require("../addons/zynk")
const roleId = "808120572486877234"

module.exports = {
    name: "bless",
    async execute(message, argv) {
        if (message.guild === null) {
            return
        }
        if (!message.member.roles.cache.has(roleId)) {
            return message.reply("permission denied.")
        }
        if (!addon.getProcessIdEx("ps_game.exe")) {
            return message.reply("cannot process request.")
        }
        if (!argv[0] || argv[1]) {
            return message.reply("invalid argument.")
        }
        if (!isNaN(argv[0]) ||
            argv[0].includes(".", 0) ||
            Number.isInteger(+argv[0])) {
            return message.reply("invalid argument.")
        }
        if (argv[0] === "enable") {
            try {
                await addon.blessOfGoddess(6000);
                exec("agent.exe", ["/enablekill"])
                message.channel.send("`Enabled Bless of Goddess`")
            }
            catch (error) {
                console.log(error)
                message.channel.send("`Error: server exploded`")
            }
        }
        else if (argv[0] === "disable") {
            try {
                await addon.blessOfGoddess(12000);
                exec("agent.exe", ["/disablekill"])
                message.channel.send("`Disabled Bless of Goddess`")
            }
            catch (error) {
                console.log(error)
                message.channel.send("`Error: server exploded`")
            }
        }
    }
}
