/**
 * Created by gongxun on 16/11/22.
 */

var GameBaseWidget = ccui.Layout.extend({
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
    }
});