/**
 * Created by gongxun on 16/10/9.
 */

var HallScene = cc.Scene.extend({
    mChildLayers : null,
    mTimestamp : null,
    onEnter:function () {
        this._super();
        var layer = new HallMainLayer();
        this.addChild(layer);
        mo.gameScene = this;

        this.mChildLayers = new Array();
        this.mChildLayers.push(layer);

        this.mTimestamp = mo.hallDefines.getMillisecond();
    },

    pushLayer : function(layer){
        var currenttime = mo.hallDefines.getMillisecond();
        if (currenttime - 500 < this.mTimestamp){
            return;
        }
        this.mTimestamp = currenttime;

        var layer1 = this.mChildLayers[this.mChildLayers.length - 1];
        this.addChild(layer);
        this.mChildLayers.push(layer);

        layer1.stopAllActions();
        layer.stopAllActions();
        layer.setPosition(cc.p(mo.curSize.x, 0));

        layer1.runAction(cc.sequence(cc.moveTo(0.2, cc.p(-mo.curSize.x / 2, 0))));
        layer.runAction(cc.sequence(cc.moveTo(0.2, cc.p(0, 0))));
    },

    popLayer : function(){
        var currenttime = mo.hallDefines.getMillisecond();
        if (currenttime - 500 < this.mTimestamp){
            return;
        }
        this.mTimestamp = currenttime;

        if (this.mChildLayers.length > 1){
            var layer = this.mChildLayers.pop();
            var layer1 = this.mChildLayers[this.mChildLayers.length - 1];

            layer1.stopAllActions();
            layer.stopAllActions();
            layer1.setPosition(cc.p(-mo.curSize.x / 2, 0));

            layer1.runAction(cc.sequence(cc.moveTo(0.2, cc.p(0, 0))));
            layer.runAction(cc.sequence(cc.moveTo(0.2, cc.p(mo.curSize.x, 0)), cc.callFunc(function(){
                this.removeChild(layer);
            }, this)));
        }
    }
});