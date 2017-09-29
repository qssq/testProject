/**
 * Created by gongxun on 17/7/4.
 */

var TableRoundEndEventWzqHandler = function(){
    var that = new GameResponseBase();

    that.handle = function (binary, msgid) {
        that.loadMessage(binary, msgid);

    };

    return that;
};