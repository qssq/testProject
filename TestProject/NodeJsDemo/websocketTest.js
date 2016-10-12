//websocket

var WebSocketServer = require('ws').Server
  , wss = new WebSocketServer({port: 8080});

var wsId = 0;
var wsArray = new Array();

var getMsgJson = function(isMy, msg){
	var msgJson = {};
	msgJson.isMy = isMy;
	msgJson.msg = msg;

  	var result = JSON.stringify(msgJson);
  	console.log("json:" + result);
  	return result;
};

wss.on('connection', function(ws) {
	wsArray.push(ws);
	console.log("connect user id = " + wsId++);

    ws.on('message', function(message) {
        console.log('received: %s', message);

        for (var i = 0; i < wsArray.length; i++) {
        	wsArray[i].send(getMsgJson(wsArray[i] == ws, message));
        }
    });

    ws.on('onclose', function(evt){

    });

    ws.send('welconme chatnet');
});