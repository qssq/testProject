/**
 * Created by gongxun on 16/10/14.
 */

var HallClubLayer = GameBaseLayer.extend({
    mChatLayer : null,
    ctor: function () {
        this._super();

        this.mChatLayer = new HallChatLayer();
        this.addChild(this.mChatLayer);
        this.mChatLayer.setTopWidgetHeight(360);

        this.loadCocostudio("hallRes/ccs/HallClubLayer.json");

        //关闭
        ccui.helper.seekWidgetByName(this.ccsNode, "Button_exit").addTouchEventListener(function(sender, type){
            if (type == ccui.Widget.TOUCH_ENDED) {
                mo.gameScene.popLayer();
            }
        }, this);

        //俱乐部详细
        ccui.helper.seekWidgetByName(this.ccsNode, "Button_clupInfo").addTouchEventListener(function(sender, type){
            if (type == ccui.Widget.TOUCH_ENDED) {
                mo.gameScene.pushLayer(new HallClubInfoLayer(1));
            }
        }, this);

        //创建牌局
        ccui.helper.seekWidgetByName(this.ccsNode, "Image_tableBg").addTouchEventListener(function(sender, type){
            if (type == ccui.Widget.TOUCH_BEGAN){
                sender.setColor(cc.color(150, 150, 150));
            } else if (type == ccui.Widget.TOUCH_ENDED) {
                sender.setColor(cc.color(255, 255, 255));
            } else {
                sender.setColor(cc.color(255, 255, 255));
            }
        }, this);
    }
});