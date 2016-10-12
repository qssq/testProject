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

    ws.on('onclose', function(evt) {
        if (onlineUsers.hasOwnProperty(user.id)) {
            //删除
            delete onlineUsers[user.id];
        }
    });




    //    //监听新用户加入
    //    ws.on('login', function(obj) {
    //        //将新加入用户的唯一标识当作socket的名称，后面退出的时候会用到
    //        socket.name = obj.userid;

    //        //检查在线列表，如果不在里面就加入
    //        if (!onlineUsers.hasOwnProperty(obj.userid)) {
    //            onlineUsers[obj.userid] = obj.username;
    //            //在线人数+1
    //            onlineCount++;
    //        }

    //        //向所有客户端广播用户加入
    //        wss.emit('login', { onlineUsers: onlineUsers, onlineCount: onlineCount, user: obj });
    //        console.log(obj.username + '加入了聊天室');
    //    });

    //    //监听用户退出
    // socket.on('disconnect', function(){
    // 	//将退出的用户从在线列表中删除
    // 	if(onlineUsers.hasOwnProperty(socket.name)) {
    // 		//退出用户的信息
    // 		var obj = {userid:socket.name, username:onlineUsers[socket.name]};

    // 		//删除
    // 		delete onlineUsers[socket.name];
    // 		//在线人数-1
    // 		onlineCount--;

    // 		//向所有客户端广播用户退出
    // 		wss.emit('logout', {onlineUsers:onlineUsers, onlineCount:onlineCount, user:obj});
    // 		console.log(obj.username+'退出了聊天室');
    // 	}
    // });

});
