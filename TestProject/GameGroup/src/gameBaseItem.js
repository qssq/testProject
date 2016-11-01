/**
 * Created by gongxun on 16/10/17.
 */

var GameBaseItem = ccui.Layout.extend({
    ccsNode : null,

    ctor: function () {
        this._super();
    },
    onExit: function () {
        this._super();
    },
    loadCocostudio : function(file){
        var json = ccs.load(file);
        this.ccsNode = json.node;
        this.addChild(this.ccsNode);
    },
    getIsPop : function(){
        return true;
    },

    setItemSize : function(size){
        this.setContentSize(size);

        var Panel_center = ccui.helper.seekWidgetByName(this.ccsNode, "Panel");
        Panel_center.setContentSize(size);
        ccui.helper.doLayout(Panel_center);
    }
});