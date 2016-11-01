/**
 * Created by gongxun on 16/10/14.
 */

var HallPrivateChatLayer = GameBaseLayer.extend({
    mChatLayer : null,
    ctor: function () {
        this._super();

        this.mChatLayer = new HallChatLayer();
        this.addChild(this.mChatLayer);
        this.mChatLayer.setTopWidgetHeight(100);

        this.loadCocostudio("hallRes/ccs/HallPrivateChatLayer.json");

        //关闭
        ccui.helper.seekWidgetByName(this.ccsNode, "Button_exit").addTouchEventListener(function(sender, type){
            if (type == ccui.Widget.TOUCH_ENDED) {
                mo.gameScene.popLayer();
            }
        }, this);
    }
});