/**
 * Created by gongxun on 17/7/3.
 */

var TableStatsWzqHandler = function(){
    var that = new GameResponseBase();

    that.handle = function (binary, msgid) {
        that.loadMessage(binary, msgid);

    };

    return that;
};