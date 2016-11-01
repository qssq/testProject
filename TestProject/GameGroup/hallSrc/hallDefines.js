/**
 * Created by gongxun on 16/10/9.
 */

var HallDefines = function(){
    var that = [];

    that.gettimestamp = function(){
        var timestamp = Math.round(new Date().getTime()/1000);
        return timestamp;
    };

    that.getMillisecond = function(){
        return new Date().getTime();
    };

    return that;
};

mo.hallDefines = new HallDefines();