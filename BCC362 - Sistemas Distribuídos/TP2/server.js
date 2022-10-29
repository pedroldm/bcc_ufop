const mqtt = require("mqtt");
const Request = require("./request");
const Response = require("./response");
const {v4: uuidv4} = require('uuid');
require("dotenv").config();

if (process.argv.length < 3) throw 'É necessário informar a identificação do servidor!';
const serverId = parseInt(process.argv[2]);
if (isNaN(serverId) || serverId > 5 || serverId <= 0) throw 'A identificação do servidor deve ser um INT entre 1 e!';

let currentRequest = new Request();
let response = new Response();

var mqttClient = mqtt.connect(process.env.MQTTBROKER);

mqttClient.on("connect", function () {
    mqttClient.subscribe(process.env.MQTTREQUESTTOPIC);
    console.log(`Servidor ${serverId} conectado ao broker ${process.env.MQTTBROKER} no tópico ${process.env.MQTTREQUESTTOPIC}!`);
});

mqttClient.on("message", function(topic, message) {
    let messageObject = JSON.parse(message.toString());

    if (checkObjectResponse(messageObject, new Request())) {
        currentRequest = messageObject;
        if (checkResponsibility(messageObject)) {
            if (messageObject.requestKind) {
                array[messageObject.varIndex] = messageObject.value;
            }
            let response = new Response(serverId, messageObject.clientId, messageObject.varIndex, array[messageObject.varIndex]);
            mqttClient.publish(process.env.MQTTREQUESTTOPIC, JSON.stringify(response));
        } else {
            checkResponseExists(messageObject);
        }
    }
});

function checkObjectResponse(a, b){
    var aKeys = Object.keys(a).sort();
    var bKeys = Object.keys(b).sort();
    return JSON.stringify(aKeys) === JSON.stringify(bKeys);
}

function checkResponsibility(messageObject) {
    return (((serverId - 1) * 20 < messageObject.varIndex && serverId * 20 >= messageObject.varIndex) || array[messageObject.varIndex] != undefined);
}

function checkResponseExists(messageObject) {
    setTimeOut(() => {
        
    }, 5000);
}