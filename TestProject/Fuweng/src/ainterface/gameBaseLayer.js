/**
 * Created by gongxun on 16/11/18.
 */

var GameBaseLayer = cc.Layer.extend({
    ccsNode : null,
    mTimestamp : null,
    mActionScale : 1,
    mActionScaleStart : 1.1,
    ctor: function () {
        this._super();
        this.mTimestamp = mo.gameHelper.getMillisecond();
    },

    onExit: function () {
        ccs.armatureDataManager.clear();
        ccs.sceneReader.clear();
        ccs.actionManager.clear();
        ccs.uiReader.clear();
        this._super();
    },

    loadCocostudio : function(file){
        var json = ccs.load(file);
        this.ccsNode = json.node;
        this.addChild(this.ccsNode);
        this.resetSize(this.ccsNode);
    },

    resetSize: function (node) {
        var Panel_center = ccui.helper.seekWidgetByName(node, "Panel");
        Panel_center.setContentSize(mo.curSize.x, mo.curSize.y);
        ccui.helper.doLayout(Panel_center);
    },

    showAction : function(node){
        node.setScale(0);
        node.runAction(cc.sequence(cc.scaleTo(0.3, this.mActionScaleStart), cc.scaleTo(0.1, this.mActionScale)));
    },

    closeAction : function(node){
        var isClose = false;

        //拦截
        var currenttime = mo.gameHelper.getMillisecond();
        if (currenttime - this.mTimestamp < 500){
            isClose = false;
        }else{
            this.mTimestamp = currenttime;

            var that = this;
            node.runAction(cc.sequence(cc.scaleTo(0.3, this.mActionScaleStart), cc.scaleTo(0.1, 0), cc.callFunc(function(){
                that.removeFromParent();
            })));

            isClose = true;
        }

        return isClose;
    }
});