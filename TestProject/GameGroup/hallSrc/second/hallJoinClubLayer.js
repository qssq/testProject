/**
 * Created by gongxun on 16/10/15.
 */

var HallJoinClubLayer = GameBaseLayer.extend({
    TextField_clubName : null,
    ctor: function () {
        this._super();
        this.loadCocostudio("hallRes/ccs/HallJoinClubLayer.json");

        this.ListView_content = ccui.helper.seekWidgetByName(this.ccsNode, "ListView_content");
        this.ListView_content.setScrollBarEnabled(false);

        //关闭
        ccui.helper.seekWidgetByName(this.ccsNode, "Button_exit").addTouchEventListener(function(sender, type){
            if (type == ccui.Widget.TOUCH_ENDED) {
                mo.gameScene.popLayer();
            }
        }, this);

        //搜索圈子
        ccui.helper.seekWidgetByName(this.ccsNode, "Button_search").addTouchEventListener(function(sender, type){
            if (type == ccui.Widget.TOUCH_ENDED) {
                mo.gameScene.pushLayer(new HallClubInfoLayer(0));
            }
        }, this);

        //input
        this.TextField_clubName = ccui.helper.seekWidgetByName(this.ccsNode, "TextField_clubName");
        //this.TextField_clubName.addEventListener(this.textFieldEvent, this);
    },

    textFieldEvent: function (textField, type) {
        if (cc.sys.os == "iOS"){
            switch (type) {
                case ccui.TextField.EVENT_ATTACH_WITH_IME:
                    this.ListView_content.stopAllActions();
                    this.ListView_content.runAction(cc.moveTo(0.225, cc.p(0, 250)));
                    break;
                case ccui.TextField.EVENT_DETACH_WITH_IME:
                    this.ListView_content.stopAllActions();
                    this.ListView_content.runAction(cc.moveTo(0.175, cc.p(0, 0)));
                    break;
                case ccui.TextField.EVENT_INSERT_TEXT:

                    break;
                case ccui.TextField.EVENT_DELETE_BACKWARD:

                    break;
                default:
                    break;
            }
        }
    }
});
