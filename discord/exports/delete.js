const roleId = "808120572486877234"

module.exports = {
    name: "del",
    async execute(message, argv) {
        if (message.guild === null) {
            return
        }
        if (!message.member.roles.cache.has(roleId)) {
            return message.reply("permission denied.")
        }
        if (!argv[0] || argv[1]) {
            return message.reply("invalid argument.")
        }
        if (isNaN(argv[0]) ||
            argv[0].includes(".", 0) ||
            !Number.isInteger(+argv[0]) ||
            argv[0] < 1 ||
            argv[0] > 100) {
            return message.reply("invalid argument.")
        }
        await message.channel.messages.fetch({limit: argv[0]}).then(messages => {
            message.channel.bulkDelete(messages)
        })
    }
}
