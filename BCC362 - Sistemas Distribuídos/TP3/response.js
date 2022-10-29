class Response {
    constructor (serverId, valueRequested, result, fromClient = true) {
        this.serverId = serverId;
        this.valueRequested = valueRequested;
        this.result = result;
        this.fromClient = fromClient
    }
}

module.exports = Response;