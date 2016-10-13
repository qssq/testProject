//gx
var WebSocketServer = require('ws').Server,
    wss = new WebSocketServer({ port: 8080 });

//在线用户
var onlineUsers = {};

var sessionId = 0;

var getJsonForStr = function(str) {
    return JSON.parse(str);
};

var getStrForJson = function(json) {
    return JSON.stringify(json);
};

//websocket
wss.on('connection', function(ws) {

    var user = {};
    var Handld = function() {
        var that = {};

        that.handMsg = function(msg) {
            if (msg.hasOwnProperty("type")) {
                var type = msg.type;
                console.log("type:" + type);

                if (type == "login") {
                    user.ws = ws;
                    user.id = sessionId++;
                    if (!onlineUsers.hasOwnProperty(user.id)) {
                        onlineUsers[user.id] = user;
                    }
                    ws.send(getStrForJson({ type: "login", content: user.id }));

                    console.log("用户登陆 id:" + user.id);
                } else if (type == "chatmsg") {
                    var chatMsg = msg.content;

                    for (var i in onlineUsers) {
                        if (onlineUsers.hasOwnProperty(i)) { //filter,只输出man的私有属性
                            onlineUsers[i].ws.send(getStrForJson({ type: "chatmsg", content: chatMsg, userid: user.id }));
                        };
                    }

                    console.log("用户id:" + user.id + " 发送消息:" + chatMsg);
                }
            }
        };

        return that;
    };
    var handld = new Handld();

    ws.send(getStrForJson({ test: "shide", demo: 123 }));

    //监听用户发布聊天内容
    ws.on('message', function(obj) {
        //向所有客户端广播发布的消息
        console.log("收到消息:" + obj);

        handld.handMsg(getJsonForStr(obj));
    });

    ws.on('close', function(evt) {
        console.log("用户id:" + user.id + "退出");
        if (onlineUsers.hasOwnProperty(user.id)) {
            //删除
            delete onlineUsers[user.id];
            console.log("用户id:" + user.id + "删除");
        }
    });
});
