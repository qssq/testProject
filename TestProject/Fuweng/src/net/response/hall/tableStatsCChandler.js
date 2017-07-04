/**
 * Created by gongxun on 17/7/3.
 */

var TableStatsCCHandler = function(){
    var that = new GameResponseBase();

    that.handle = function (binary, msgid) {
        that.loadMessage(binary, msgid);

        mo.chessTableStatus.setTableStatus(that.msg);
    };

    return that;
};