const mqtt = require("mqtt");
const Request = require("./request");
const Response = require("./response");
const {v4: uuidv4} = require('uuid');
require("dotenv").config();

const clientId = uuidv4();
let requestAvailable = true;
let request = new Request();

var mqttClient = mqtt.connect(process.env.MQTTBROKER);

mqttClient.on("connect", function () {
    mqttClient.subscribe(process.env.MQTTREQUESTTOPIC);
    console.log(`Client ${clientId} conectado ao broker ${process.env.MQTTBROKER} no tópico ${process.env.MQTTREQUESTTOPIC}!`);

    setInterval(function () {
        if(requestAvailable) {
            request.clientId = clientId;
            request.requestKind = (0.5 < Math.random());
            request.varIndex = Math.floor(Math.random() * (100 - 1 + 1) + 1);
            request.value = Math.floor(Math.random() * (1000000 - 0 + 1) + 0);

            mqttClient.publish(process.env.MQTTREQUESTTOPIC, JSON.stringify(request));

            requestAvailable = false;
        }
    }, 3000);
});

mqttClient.on("message", function(topic, message) {
    let messageObject = JSON.parse(message.toString());

    if (checkObjectResponse(messageObject, new Response())) {
        if (messageObject.clientId == clientId && messageObject.varIndex == request.varIndex && messageObject.value == request.value) {
            console.log(`Requisição atendida pelo servidor ${messageObject.serverId}! [${request.varIndex}] = ${request.value}`);
            requestAvailable = true;
        }
    }
});

function checkObjectResponse(a, b){
    var aKeys = Object.keys(a).sort();
    var bKeys = Object.keys(b).sort();
    return JSON.stringify(aKeys) === JSON.stringify(bKeys);
}