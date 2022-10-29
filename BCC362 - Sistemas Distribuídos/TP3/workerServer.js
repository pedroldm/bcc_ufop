const mqtt = require("mqtt");
const Request = require("./request");
const Response = require("./response");
const {v4: uuidv4} = require('uuid');
require("dotenv").config();

let serverId = uuidv4();
let requestModel = new Request();

var mqttClient = mqtt.connect(process.env.BROKER);

mqttClient.on("connect", function () {
    mqttClient.subscribe(process.env.DISCUSSTOPIC);
    console.log(`Servidor ${serverId} conectado ao broker ${process.env.BROKER} no tópico ${process.env.DISCUSSTOPIC}!`);
});

mqttClient.on("message", function(topic, message) {
    let messageObject = JSON.parse(message.toString());

    if (compareKeys(requestModel, messageObject)) {
        let result = 0;

        if (0.01 > Math.random()) 
            result = Math.floor(Math.random() * (1000000 - 1 + 1) + 1);
        else 
            result = fib(messageObject.value);

        let response = new Response(serverId, messageObject.value, result, false);
        console.log(response);
        mqttClient.publish(process.env.DISCUSSTOPIC, JSON.stringify(response));
    }
});

function fib(n){
    let arr = [0, 1];
    for (let i = 2; i < n + 1; i++){
      arr.push(arr[i - 2] + arr[i -1])
    }
   return arr[n]
}

function compareKeys(a, b) {
    var aKeys = Object.keys(a).sort();
    var bKeys = Object.keys(b).sort();
    return JSON.stringify(aKeys) === JSON.stringify(bKeys);
}