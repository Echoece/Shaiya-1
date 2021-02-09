const output = "`Direct Message`\n\
`!reg username password`\n\
`!pwd username old-password new-password`\n\n\
`Guild Message`\n\
`!hello`\n\
`!help`\n\
`!status`\n\
`!uc`\n\
`!time`"

module.exports = {
    name: "help",
    execute(message) {     
        if (message.guild === null) {
            return
        }
        message.channel.send(output)
    }
}
