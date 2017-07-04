/**
 * Created by gongxun on 16/11/18.
 */

var GameHelper = function(){
    var that = [];

    that.version = "1.0.0";

    that.htmlHost = "http://60.205.169.204";

    that.isRead = false;

    that.isIosCheck = true;

    that.developerVersion = "2.0";

    // that.webSocketIp = "ws://192.168.0.222:5227/";
    that.webSocketIp = "ws://60.205.169.204:10086/";

    that.appStoreUrl = "https://itunes.apple.com/cn/app/qi-xin-ka-wu-xing/id1191724123";

    that.androidDownUrl = "https://itunes.apple.com/cn/app/qi-xin-ka-wu-xing/id1191724123";

    that.setTextString = function(text, content){
        // text.ignoreContentAdaptWithSize(false);
        // text.setTextAreaSize(cc.size(300,60));
        // text.setString("");
        // text.ignoreContentAdaptWithSize(true);
        text.setString(content);
        text.setContentSize(text.getAutoRenderSize());
    };

    that.loadTextureImage = function(image, file){
        image.ignoreContentAdaptWithSize(false);
        image.ignoreContentAdaptWithSize(true);
        image.loadTexture(file);
    };

    that.fixIosText = function(root){
        if (root){
            if (root.getName().substr(0, 5) === "Text_"){
                root.ignoreContentAdaptWithSize(true);
            }
            var arrayRootChildren = root.getChildren();
            var length = arrayRootChildren.length;
            for (var i = 0; i < length; i++) {
                var child = arrayRootChildren[i];
                that.fixIosText(child);
            }
        }
    };

    that.getTimestamp = function(){
        return Math.round(new Date().getTime()/1000);
    };

    that.getMillisecond = function(){
        return new Date().getTime();
    };

    //b是否包含s  s和b都是不重复的
    that.getContainArrayAndReturnLeft = function(bigArray, smallArray){
        var result = [];
        var isContain = true;
        for(var i = 0; i < bigArray.length; i++){
            var num = bigArray[i];

            var find = false;
            for (var j = 0; j < smallArray.length; j++){
                if (smallArray[i] == num){

                }else{

                }
            }
        }

        var temp = [];
        for (var i = 0; i < bigArray.length; i++){
            temp.push(bigArray[i]);
        }

        var isContain = true;
        for (var i = 0; i < smallArray.length; i++){
            var num = smallArray[i];
            var isFind = false;
            for (var j = 0; j < temp.length; j++){
                var tempNum = temp[j];
                if (tempNum == num){
                    isFind = true;
                    temp.splice(j, 1);
                    break;
                }
            }
            if (!isFind){
                isContain = false;
                break;
            }
        }

        if (isContain){
            return [true, temp];
        }else{
            return [false, []];
        }
    };

    //返回不重复的数组
    that.getUniqueArray = function(nums){
        var h = {};
        var arr = [];

        for(var i = 0; i < nums.length; i++){
            //对元素进行判断，看是否已经存在表中，如果存在则跳过，否则存入临时数组
            if(!h[nums[i]]){
                //存入hash表
                h[nums[i]] = true;
                //把当前数组元素存入到临时数组中
                arr.push(nums[i]);
            }
        }
        return arr;
    };

    //返回是否存在 存在返回索引 不存在返回null
    that.findValueForArray = function(array, value){
        var result = null;
        for (var i = 0; i < array.length; i++){
            if (value === array[i]){
                result = i;
                break;
            }
        }
        return result;
    };

    that.logDebug = function(content){
        cc.log(content);
    };

    that.getIsTouchEnd = function(type){
        if (type == ccui.Widget.TOUCH_ENDED){
            mo.soundHelper.playButtonClick();
            return true;
        }
        return false;
    };

    that.getIsTouchEndMenuOpen = function(type){
        if (type == ccui.Widget.TOUCH_ENDED){
            mo.soundHelper.playMenuOpenClick();
            return true;
        }
        return false;
    };

    that.getIsTouchEndMenuClose = function(type){
        if (type == ccui.Widget.TOUCH_ENDED){
            mo.soundHelper.playMenuCloseClick();
            return true;
        }
        return false;
    };


    //微信个人分享
    that.onWxInvite = function(gameName, tableId, pwd, title, description){
        if (!cc.sys.isNative || that.isIosCheck){
            mo.showRoomMsgShow("分享成功");
            return;
        }
        mo.nativeHelper.onWxInvite(gameName, tableId, pwd, title, description);
    };

    //微信朋友圈分享
    that.onWxShare = function(content){
        if (!cc.sys.isNative|| that.isIosCheck){
            mo.showRoomMsgShow("分享成功");
            return;
        }
        var fileName = "shareImage.png";
        mo.nativeHelper.onWxShare(content, fileName);
    };

    //加载图片
    that.loadImageForUrl = function(imageView, url){
        if (cc.sys.isNative){
            mo.nativeHelper.setImageUrr(imageView, url);
        }
    };

    //返回itemid对应的中文
    that.getItemIdForCHS = function(itemid){
        if (itemid == 20001){
            return "房卡";
        }else if (itemid == 20002){
            return "荣誉值";
        }else if (itemid == 20000){
            return "游戏点";
        }
        return "未知货币";
    };

    //返回当前是否是旋转状态
    that.getIsRotation = function(){
        if (mo.gameMainLayer != null){
            return mo.gameMainLayer.getCurrentIsRotation();
        }else{
            return false;
        }
    };

    //设置root的Text_text文字
    that.setRootTitleText = function(root, text){
        var textui = mo.seekWidgetByName(root, "Text_text");
        if (textui != null){
            that.setTextString(textui, text);
        }
    };

    //过滤玩家昵称
    that.getUserNickFilter = function(nick){
        var count = 5;
        var result = nick;
        if (nick.length > 5){
            result = result.substr(0, 5) + "..";
        }
        return result;
    };

    //返回手机类型
    that.getDeviceType = function(){
        cc.log("sys os:" + cc.sys.os);
        if (cc.sys.os == "iOS"){
            return 0;
        }else if (cc.sys.os == "Android"){
            return 1;
        }else {
            return 2;
        }
    };

    return that;
};

mo.gameHelper = new GameHelper();

//common
mo.seekWidgetByName = function(root, name){
    if (!root)
        return null;

    if (root.getName() === name)
        return root;

    var arrayRootChildren = root.getChildren();
    var length = arrayRootChildren.length;
    for (var i = 0; i < length; i++) {
        var child = arrayRootChildren[i];
        var res = mo.seekWidgetByName(child, name);
        if (res !== null)
            return res;
    }
    return null;
};