const mqtt = require("mqtt");
const Request = require("./request");
const Response = require("./response");
const {v4: uuidv4} = require('uuid');
require("dotenv").config();

const clientId = uuidv4();
let requestAvailable = true;
let request = new Request();
let response = new Response();

var mqttClient = mqtt.connect(process.env.BROKER);

mqttClient.on("connect", function () {
    mqttClient.subscribe(process.env.REQUESTTOPIC);
    console.log(`Client ${clientId} conectado ao broker ${process.env.BROKER} no tópico ${process.env.REQUESTTOPIC}!`);

    setInterval(function () {
        if(requestAvailable) {
            request.clientId = clientId;
            request.value = Math.floor(Math.random() * (40 - 1 + 1) + 1);
            mqttClient.publish(process.env.REQUESTTOPIC, JSON.stringify(request));
            requestAvailable = false;
        }
    }, 3000);
});

mqttClient.on("message", function(topic, message) {
    let messageObject = JSON.parse(message.toString());
    console.log(messageObject);
    if(compareKeys(response, messageObject)) {
        requestAvailable = true;
    }
});

function compareKeys(a, b) {
    var aKeys = Object.keys(a).sort();
    var bKeys = Object.keys(b).sort();
    return JSON.stringify(aKeys) === JSON.stringify(bKeys);
  }