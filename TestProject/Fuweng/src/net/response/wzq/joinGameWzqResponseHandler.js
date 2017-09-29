/**
 * Created by gongxun on 17/7/2.
 */

var JoinGameWzqResponseHandler = function(){
    var that = new GameResponseBase();

    that.handle = function (binary, msgid) {
        that.loadMessage(binary, msgid);

        var code = that.msg.code;
        cc.log("join code :" + code);
    };

    return that;
};