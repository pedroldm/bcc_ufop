const mqtt = require("mqtt");
const Request = require("./request");
const Response = require("./response");
const {v4: uuidv4} = require('uuid');
require("dotenv").config();

let serverId = uuidv4();
let bannedServers = [];
let responseArray = [];
let responseModel = new Response();
let requestModel = new Request();

var mqttClient = mqtt.connect(process.env.BROKER);

mqttClient.on("connect", function () {
    mqttClient.subscribe(process.env.REQUESTTOPIC);
    mqttClient.subscribe(process.env.DISCUSSTOPIC);
    mqttClient.subscribe(process.env.BACKUPTOPIC);
    console.log(`Servidor ${serverId} conectado ao broker ${process.env.BROKER} no tópico ${process.env.REQUESTTOPIC}!`);
    console.log(`Servidor ${serverId} conectado ao broker ${process.env.BROKER} no tópico ${process.env.DISCUSSTOPIC}!`);
    console.log(`Servidor ${serverId} conectado ao broker ${process.env.BROKER} no tópico ${process.env.BACKUPTOPIC}!`);
    setInterval(function () {
        let hrTime = process.hrtime()
        let currentTime = hrTime[0] * 1000000 + hrTime[1] / 1000;
        mqttClient.publish(process.env.BACKUPTOPIC, `{"time" : ${currentTime}}`);
    }, 2000);
});

mqttClient.on("message", function(topic, message) {
    let messageObject = JSON.parse(message.toString());
    if (topic == process.env.REQUESTTOPIC && compareKeys(requestModel, messageObject)) {
        mqttClient.publish(process.env.DISCUSSTOPIC, message);
        sendResponse();
    }
    else if (topic == process.env.DISCUSSTOPIC && compareKeys(messageObject, responseModel)) {
        let messageObject = JSON.parse(message.toString());
        responseArray.push(messageObject);
    }
});

function sendResponse() {
    setTimeout(() => {
        responseCounter = {}; 
        responseArray.forEach(function (resp) {
            if (bannedServers.includes(resp.serverId)) return;
            if (responseCounter.hasOwnProperty(resp.result)) responseCounter[resp.result]++;
            else responseCounter[resp.result] = 1;
        });

        let correctAnswer = {"answer" : 0, "frequency" : 0}
        let count = 0;
        for (const r in responseCounter) {
            if (count < responseCounter[r]) {
                count = responseCounter[r];
                correctAnswer.answer = r;
                correctAnswer.frequency = responseCounter[r];
            }
        }

        console.log(responseArray);
        console.log(`A resposta para FIB(${responseArray[0].valueRequested}) é ${correctAnswer.answer}! ${correctAnswer.frequency} de ${responseArray.length - bannedServers.length} servidores responderam corretamente.`);

        responseArray.forEach(function (resp) {
            if(resp.result != correctAnswer.answer) {
                console.log(`Servidor ${resp.serverId} BANIDO por resposta incorreta!`);
                bannedServers.push(resp.serverId);
            }
        });

        let response = new Response(serverId, responseArray[0].valueRequested, correctAnswer.answer);
        mqttClient.publish(process.env.REQUESTTOPIC, JSON.stringify(response));
        responseArray = [];
    }, 10000);
}

function compareKeys(a, b) {
    var aKeys = Object.keys(a).sort();
    var bKeys = Object.keys(b).sort();
    return JSON.stringify(aKeys) === JSON.stringify(bKeys);
}