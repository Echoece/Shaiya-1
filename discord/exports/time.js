const exec = require("child_process").exec

module.exports = {
    name: "time",
    execute(message) {
        if (message.guild === null) {
            return
        }
        exec("python ./exports/time.py", (err, stdout) => {
            if (err) {
                console.log(err)
                return message.reply("cannot process request.")
            }
            message.channel.send("`" + `${stdout}` + "`")
        })
    }
}
