/**
 * Created by gongxun on 17/2/3.
 */

var TilemapLayer = cc.Layer.extend({
    ctor : function(){
        this._super();

        var map = new cc.TMXTiledMap("res/map/fuweng.tmx");
        this.addChild(map);
    }
});