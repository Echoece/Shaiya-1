const Discord = require("discord.js")
const client = new Discord.Client()
const fs = require("fs")
const mssql = require("mssql")
const addon = require("./addons/zynk")
const config = { 
    user: "Shaiya",
    password: "Shaiya123",
    server: "localhost",
    database: "master",
    options: {
        encrypt: false,
        enableArithAbort: true
    }
}

mssql.connect(config, err => { 
    if (err) {
        console.log(err)
    }
    console.log(`Zynk connected to ${config.database}!`)
})

mssql.on("error", err => {
    console.log(err)
})

client.commands = new Discord.Collection()
const js = fs.readdirSync("./exports/").filter(file => file.endsWith(".js"))
for (const file of js) {
    let command = require(`./exports/${file}`)
    client.commands.set(command.name, command)
}

client.on("message", message => {
    if (!message.content.startsWith("!") || message.author.bot) {
        return
    }
    if (message.content.startsWith("!nt")) {
        let argv = message.content.slice(4).split(1)
        client.commands.get("nt").execute(message, argv)
        return
    }
    var argv = message.content.slice(1).split(/ +/)
    var command = argv.shift().toLowerCase()
    if (client.commands.has(command)) {
        client.commands.get(command).execute(message, argv)
    }
})

client.once("ready", () => {
    console.log("Zynk online!")
    addon.setSeDebugPrivilege()
})

client.login("Njc3NDA5MzIwNTAxMjQ4MDUx.XkT0lw.h7gzRzFgjimpmY1foIctDekJR78")
