class Request {
    constructor (clientId, varIndex, requestKind, value) {
        this.clientId = clientId;
        this.varIndex = varIndex;
        this.requestKind = requestKind;
        this.value = value;
    }
}

module.exports = Request;