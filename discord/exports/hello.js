module.exports = {
    name: "hello",
    execute(message) {
        if (message.guild === null) {
            return
        }
        message.channel.send("Hello, Discord!")
    }
}
