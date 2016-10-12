/**
 * Created by gongxun on 16/10/9.
 */

var GameBaseLayer = cc.Layer.extend({
    ccsNode : null,

    ctor: function () {
        this._super();
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
    getIsPop : function(){
        return true;
    },
    resetSize: function (node) {
        //node.setContentSize(mo.curSize.x, mo.curSize.y);
        //ccui.helper.doLayout(node);

        var Panel_center = ccui.helper.seekWidgetByName(node, "Panel");
        Panel_center.setContentSize(mo.curSize.x, mo.curSize.y);
        ccui.helper.doLayout(Panel_center);
    }
});