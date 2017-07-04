/**
 * Created by gongxun on 17/2/4.
 */

var MonopolyHelper = function(){
    var that = {};

    //地图比例
    that.mapScale = 64;

    //默认地图
    that.defaultMapPos = null;

    //当前地图块数
    that.currentMapBlockCount = null;

    that.init = function(){
        //defaultmap
        that.defaultMapPos = [];
        for (var i = 0; i < 44; i++){
            var temp = parseInt(i / 11);
            var yushu = i % 11;
            if (temp < 1){
                that.defaultMapPos.push(cc.p(yushu + 4, 15));
            }else if (temp < 2){
                that.defaultMapPos.push(cc.p(15, 15 - yushu));
            }else if (temp < 3){
                that.defaultMapPos.push(cc.p(15 - yushu, 4));
            }else if (temp < 4){
                that.defaultMapPos.push(cc.p(4, yushu + 4));
            }
        }

        that.currentMapBlockCount = 44;
    };

    //返回坐标
    that.getIndexPos = function(index){
        var realIndex = that.getIndex(index);
        var indexPos = that.defaultMapPos[realIndex];
        return cc.p(indexPos.x * that.mapScale, indexPos.y * that.mapScale);
    };

    //返回对应的索引
    that.getIndex = function(index){
        if (index >= 0){
            return index % that.currentMapBlockCount;
        }else{
            return that.currentMapBlockCount - 1 - (-index) % that.currentMapBlockCount;
        }
    };

    return that;
};

mo.monopolyHelper = new MonopolyHelper();