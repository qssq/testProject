/**
 * Created by gongxun on 17/7/4.
 */

var TableRoundEndEventCCHandler = function(){
    var that = new GameResponseBase();

    that.handle = function (binary, msgid) {
        that.loadMessage(binary, msgid);

        mo.chessTable.showEndLayer(that.msg);
    };

    return that;
};