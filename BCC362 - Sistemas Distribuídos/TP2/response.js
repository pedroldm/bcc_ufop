class Response {
    constructor (serverId, clientId, varIndex, value) {
        this.serverId = serverId;
        this.clientId = clientId;
        this.varIndex = varIndex;
        this.value = value;
    }
}

module.exports = Response;