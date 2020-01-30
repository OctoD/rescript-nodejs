// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Http = require("http");
var Caml_option = require("bs-platform/lib/js/caml_option.js");

var IncomingMessage = { };

var ServerResponse = { };

var Server = { };

function createServer(incomingMessage, serverResponse, maxHeaderSize, requestListener) {
  return Http.createServer({
              IncomingMessage: incomingMessage !== undefined ? Caml_option.valFromOption(incomingMessage) : null,
              ServerResponse: serverResponse !== undefined ? Caml_option.valFromOption(serverResponse) : null,
              maxHeaderSize: maxHeaderSize
            }, requestListener);
}

exports.IncomingMessage = IncomingMessage;
exports.ServerResponse = ServerResponse;
exports.Server = Server;
exports.createServer = createServer;
/* http Not a pure module */