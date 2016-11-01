/**
 * Created by gongxun on 16/10/15.
 */

var HallCLubListLayer = GameBaseLayer.extend({
    Panel_addClup : null,
    ctor: function () {
        this._super();
        this.loadCocostudio("hallRes/ccs/HallClubListLayer.json");

        ccui.helper.seekWidgetByName(this.ccsNode, "ListView_content").setScrollBarEnabled(false);

        this.Panel_addClup = ccui.helper.seekWidgetByName(this.ccsNode, "Panel_addClup");

        //添加
        ccui.helper.seekWidgetByName(this.ccsNode, "Button_add").addTouchEventListener(function(sender, type){
            if (type == ccui.Widget.TOUCH_ENDED) {
                this.setShowAddClup(!this.Panel_addClup.isVisible());
            }
        }, this);

        //关闭添加
        this.Panel_addClup.addTouchEventListener(function(sender, type){
            if (type == ccui.Widget.TOUCH_ENDED) {
                this.setShowAddClup(false);
            }
        }, this);

        //创建圈子
        ccui.helper.seekWidgetByName(this.ccsNode, "Text_createClub").addTouchEventListener(function(sender, type){
            if (type == ccui.Widget.TOUCH_ENDED) {
                mo.gameScene.pushLayer(new HallCreateClubLayer());
                this.setShowAddClup(false);
            }
        }, this);

        //加入圈子
        ccui.helper.seekWidgetByName(this.ccsNode, "Text_joinClub").addTouchEventListener(function(sender, type){
            if (type == ccui.Widget.TOUCH_ENDED) {
                mo.gameScene.pushLayer(new HallJoinClubLayer());
                this.setShowAddClup(false);
            }
        }, this);

        //进入圈子
        ccui.helper.seekWidgetByName(this.ccsNode, "Panel_item0").addTouchEventListener(function(sender, type){
            if (type == ccui.Widget.TOUCH_ENDED) {
                mo.gameScene.pushLayer(new HallClubLayer());
                this.setShowAddClup(false);
            }
        }, this);

        this.setShowAddClup(false);
    },

    setShowAddClup : function(isShow){
        this.Panel_addClup.setVisible(isShow);
        if (isShow){
            ccui.helper.seekWidgetByName(this.ccsNode, "Button_add").loadTextures("hallRes/ccs/club/common_close_btn@2x.png", "hallRes/ccs/club/common_close_btn@2x.png");
        } else {
            ccui.helper.seekWidgetByName(this.ccsNode, "Button_add").loadTextures("hallRes/ccs/club/common_add_btn@2x.png", "hallRes/ccs/club/common_add_btn@2x.png");
        }
    }
});