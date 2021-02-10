const exec = require("child_process").execFile
const addon = require("../addons/zynk")
const roleId = "808120572486877234"

module.exports = {
    name: "nt",
    execute(message, argv) {
        if (message.guild === null) {
            return
        }
        if (!message.member.roles.cache.has(roleId)) {
            return message.reply("permission denied.")
        }
        if (!addon.getProcessIdEx("ps_game.exe")) {
            return message.reply("cannot process request.")
        }
        if (!argv[0] || 
            argv[0].length < 1 || 
            argv[0].length > 128) {
            return message.reply("invalid argument.")
        }
        else if (argv[0].includes("'") ||
                 argv[0].includes('"') ||
                 argv[0].includes(";") ||
                 argv[0].includes("*") ||
                 argv[0].includes("-")) {
            return message.reply("invalid argument.")
        }
        try {
            exec("agent.exe", ["/nt " + `${argv[0]}`])
        }
        catch (error) {
            console.log(error)
            message.reply("cannot process request.")
        }
    }
}
