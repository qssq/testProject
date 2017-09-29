/**
 * Created by gongxun on 16/10/26.
 */

var GameMsgManager = function(){
    var that = new GameMsgBase();

    //分发包
    that.handleMsg = function(binary, msgId){
        var response = null;
        if (msgId == 1){
             response = new LoginResponseHandler();
        }

        //xq
        else if (msgId == 3){
            response = new JoinGameCCResponseHandler();
        }else if (msgId == 5){
            response = new ActionCCResponseHandler();
        }else if (msgId == 7){
            response = new TableStatsCCHandler();
        }else if (msgId == 9){
            response = new TableRoundEndEventCCHandler();
        }

        //wzq
        else if (msgId == 11){
            response = new JoinGameWzqResponseHandler();
        }else if (msgId == 13){
            response = new ActionWzqResponseHandler();
        }else if (msgId == 15){
            response = new TableStatsWzqHandler();
        }else if (msgId == 17){
            response = new TableRoundEndEventWzqHandler();
        }

        if (response != null){
            response.handle(binary, msgId);
        }
    };

    //发送登录
    that.sendLogin = function(uid, name){
        var msgid = 0;
        var Request = that.builder.build(hallRequest[msgid]);
        var request = new Request();
        request.uid = uid;
        request.name = name;

        mo.gameWebsocket.sendMsg(that.getPotobufMsg(request), msgid);
    };

    //创建房间
    that.sendJoinGameCC_create = function(){
        var msgid = 2;
        var Request = that.builder.build(hallRequest[msgid]);
        var request = new Request();
        request.code = 1;

        mo.gameWebsocket.sendMsg(that.getPotobufMsg(request), msgid);
    };

    //加入房间
    that.sendJoinGameCC_join = function(tableId){
        var msgid = 2;
        var Request = that.builder.build(hallRequest[msgid]);
        var request = new Request();
        request.code = 1;

        mo.gameWebsocket.sendMsg(that.getPotobufMsg(request), msgid);
    };

    //action
    that.sendActionCCPlay = function(code, qz1, qz2){
        var msgid = 4;
        var Request = that.builder.build(hallRequest[msgid]);
        var request = new Request();
        request.code = code;
        request.qz1 = qz1;
        request.qz2 = qz2;

        mo.gameWebsocket.sendMsg(that.getPotobufMsg(request), msgid);
    };

    //wzq
    //创建房间
    that.sendJoinGameWzq_create = function(){
        var msgid = 10;
        var Request = that.builder.build(hallRequest[msgid]);
        var request = new Request();
        request.code = 1;

        mo.gameWebsocket.sendMsg(that.getPotobufMsg(request), msgid);
    };

    //加入房间
    that.sendJoinGameWzq_join = function(tableId){
        var msgid = 10;
        var Request = that.builder.build(hallRequest[msgid]);
        var request = new Request();
        request.code = 1;

        mo.gameWebsocket.sendMsg(that.getPotobufMsg(request), msgid);
    };

    //action
    that.sendActionWzqPlay = function(code, qz1, qz2){
        var msgid = 12;
        var Request = that.builder.build(hallRequest[msgid]);
        var request = new Request();
        request.code = code;
        request.qz1 = qz1;
        request.qz2 = qz2;

        mo.gameWebsocket.sendMsg(that.getPotobufMsg(request), msgid);
    };

    return that;
};

mo.gameMsgManager = new GameMsgManager();