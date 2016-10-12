/**
 * Created by gongxun on 16/10/9.
 */

var HallMsgLayer = GameBaseLayer.extend({
    ctor: function () {
        this._super();
        this.loadCocostudio("hallRes/ccs/HallMsgLayer.json");

        ccui.helper.seekWidgetByName(this.ccsNode, "Panel_item").addTouchEventListener(function(sender, type){
            if (type == ccui.Widget.TOUCH_ENDED) {
                mo.hallDefines.hallMainlLayer.addChild(new HallChatLayer());
            }
        }, this);
    }
});