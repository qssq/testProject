/**
 * Created by gongxun on 16/10/27.
 */

var GameResponseBase = function(){
    var that = {};

    that.msg = null;

    that.loadMessage = function(binary, msgId){
        try {
            var messageBuilder = mo.gameMsgManager.builder.build(hallResponse[msgId]);
            that.msg = messageBuilder.decode(binary);
        } catch (e) {
            if (e.decoded) {
                that.msg = e.decoded;
            } else {
                that.msg = null;
                cc.log("解析protobuf失败 error:" + e.message.toString());
            }
        }
        that.log();
    };

    that.log = function(){
        var logMsg = that.logDebugString(that.msg);
        cc.log("收到的消息是:" + logMsg);
    };

    that.logDebugString = function(msg){
        var logMsg = "";
        for (var name in msg) {
            var value = msg[name];
            var type = typeof(value);
            if (type != "function"){
                logMsg += "[" + name + "]:" + value;
                if (type == "object"){
                    logMsg += that.logDebugString(value);
                }
            }
        }
        return logMsg;
    };

    return that;
};