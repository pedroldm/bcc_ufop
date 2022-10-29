const mqtt = require("mqtt");
const db = require("./db");
const Request = require("./request");
const {Client} = require('pg');
const {v4: uuidv4} = require('uuid');
require("dotenv").config();
const debug = true;

const subId = uuidv4();
let requestPile = [];
let isAvailable = true;

var mqttClient = mqtt.connect(process.env.MQTTBROKER);
const pgClient = new Client ( {
    host: process.env.PGHOST,
    user: process.env.PGUSER,
    port: process.env.PGPORT,
    password: process.env.PGPASSWORD,
    database: process.env.DATABASE
});
pgClient.connect();

mqttClient.on("connect", function () {
    mqttClient.subscribe(process.env.MQTTTOPIC);

    setInterval(function () {
        if(isAvailable) {
            let request = new Request(subId, true);
            mqttClient.publish(process.env.MQTTTOPIC, JSON.stringify(request));
        }
        isAvailable = false;
    }, Math.floor(Math.random() * 10000)) + 100000;
});

mqttClient.on("message", function(topic, message) {
    let messageObject = JSON.parse(message.toString());
    if(debug) console.log(messageObject);

    if (messageObject.requestKind) {
        requestPile.push(messageObject);
    }
    else if(!messageObject.requestKind) {
        requestPile.shift();
    }

    if (requestPile.length) {
        if (requestPile[0].subscriberId == subId && requestPile[0].requestKind) {
            db.consultPostgres(pgClient, debug);
            let release = new Request(subId, false);
            mqttClient.publish(process.env.MQTTTOPIC, JSON.stringify(release));
            isAvailable = true;
        }
    }
});
