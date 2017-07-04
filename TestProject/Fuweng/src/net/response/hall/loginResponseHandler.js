/**
 * Created by gongxun on 17/4/20.
 */

var LoginResponseHandler = function(){
    var that = new GameResponseBase();

    that.handle = function (binary, msgid) {
        that.loadMessage(binary, msgid);

        var code = that.msg.code;
        cc.log("login code :" + code);

        mo.eventHelper.dispatch_1("LoginResponse", code == 0);
    };

    return that;
};