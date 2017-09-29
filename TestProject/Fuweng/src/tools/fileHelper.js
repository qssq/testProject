/**
 * Created by gongxun on 16/10/28.
 */

var FileHelper = function(){
    var that = {};

    that.setItem = function(key, value){
        cc.sys.localStorage.setItem(key, value);
    };

    that.getItem = function(key){
        return cc.sys.localStorage.getItem(key);
    };

    that.removeItem = function(key){
        cc.sys.localStorage.removeItem(key);
    };

    that.removeAllItem = function(){
        cc.sys.localStorage.clear();
    };

    that.getLoginInfo = function(){
        var uid = that.getItem("logininfo");
        return uid;
    };

    that.setLoginInfo = function(uid){
        that.setItem("logininfo", uid);
    };

    //设置本地断线重连超时 让下次手动登录
    that.setAccessTokenAndLoginNameTimeOut = function(){
        var timeKey = "reconReconneceTime";
        that.setItem(timeKey, mo.gameHelper.getTimestamp() - 43200);
    };

    //保存断线重连的数据 2个小时 登录成功之后刷新
    that.setAccessTokenAndLoginName = function(accesstoken, loginName){
        //保存断线重连的数据 time accesstoken loginname
        var timeKey = "reconReconneceTime";
        var accesstokenKey = "reconReconneceAccessstoken";
        var loginNameKey = "reconReconneceLoginName";

        //秒
        var timestamp = mo.gameHelper.getTimestamp();

        that.setItem(timeKey, timestamp);
        that.setItem(accesstokenKey, accesstoken);
        that.setItem(loginNameKey, loginName);
    };

    //读取断线重连的数据
    that.getAccessTokenAndLoginName = function(func){
        var timeKey = "reconReconneceTime";
        var accesstokenKey = "reconReconneceAccessstoken";
        var loginNameKey = "reconReconneceLoginName";

        var timeLocal = that.getItem(timeKey);
        cc.log("timeLocal:" + timeLocal);

        //是否过期
        var isExpired = true;
        if (timeLocal != undefined){
            var jiange = mo.gameHelper.getTimestamp() - timeLocal;
            cc.log("间隔:" + jiange);
            isExpired = jiange > 43200;
        }

        func(isExpired, that.getItem(accesstokenKey), that.getItem(loginNameKey));
    };

    return that;
};

mo.fileHelper = new FileHelper();
