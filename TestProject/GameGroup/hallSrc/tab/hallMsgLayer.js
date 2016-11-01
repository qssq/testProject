/**
 * Created by gongxun on 16/10/9.
 */

var HallMsgLayer = GameBaseLayer.extend({
    ctor: function () {
        this._super();
        this.loadCocostudio("hallRes/ccs/HallMsgLayer.json");

        ccui.helper.seekWidgetByName(this.ccsNode, "ListView_content").setScrollBarEnabled(false);

        ccui.helper.seekWidgetByName(this.ccsNode, "Panel_item").addTouchEventListener(function(sender, type){
            if (type == ccui.Widget.TOUCH_ENDED) {
                mo.gameScene.pushLayer(new HallPrivateChatLayer());
            }
        }, this);

        ccui.helper.seekWidgetByName(this.ccsNode, "Panel_item1").addTouchEventListener(function(sender, type){
            if (type == ccui.Widget.TOUCH_ENDED) {
                mo.gameScene.pushLayer(new HallClubLayer());
            }
        }, this);
    }
});