/**
 * Created by gongxun on 17/6/30.
 */

var ChessHelper = function(){
    var that = {};

    that.getChessPostion = function(col, row){
        var w = 80;
        var h = 80;

        var xAdd = 4;
        var yAdd = 58;

        return cc.p((col - 4) * w + xAdd, row * h + yAdd);
    };

    that.randomCardNum = function(){
        return parseInt(Math.random() * 7);
    };

    that.getRowColForPoint = function(point){
        var yAdd = 23;

        var result = {
            row : 0,
            col :0
        };

        for (var x = 0; x < 9; x++){
            if ((x + 1) * 80 > point.x){
                result.col = x;
                break;
            }
        }

        for (var y = 0; y < 10; y++){
            if ((y + 1) * 80 + yAdd > point.y){
                result.row = y;
                break;
            }
        }

        cc.log("end x:" + point.x + " y:" + point.y);
        cc.log("end col:" + result.col + " row:" + result.row);

        return result;
    };

    return that;
};

mo.chessHelper = new ChessHelper();