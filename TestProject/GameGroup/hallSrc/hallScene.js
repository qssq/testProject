/**
 * Created by gongxun on 16/10/9.
 */

var HallScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new HallMainLayer();
        this.addChild(layer);
        mo.gameScene = this;
    }
});