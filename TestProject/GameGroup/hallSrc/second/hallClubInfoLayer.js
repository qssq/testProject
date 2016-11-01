/**
 * Created by gongxun on 16/10/14.
 */

var HallClubInfoLayer = GameBaseLayer.extend({
    mChatLayer : null,
    mType : null,
    ListView_content : null,
    ctor: function (type) {
        this._super();
        this.loadCocostudio("hallRes/ccs/HallClubInfoLayer.json");
        this.mType = type;

        this.ListView_content = ccui.helper.seekWidgetByName(this.ccsNode, "ListView_content");
        this.ListView_content.setScrollBarEnabled(false);

        //关闭
        ccui.helper.seekWidgetByName(this.ccsNode, "Button_exit").addTouchEventListener(function(sender, type){
            if (type == ccui.Widget.TOUCH_ENDED) {
                mo.gameScene.popLayer();
            }
        }, this);

        //成员
        ccui.helper.seekWidgetByName(this.ccsNode, "Panel_member").addTouchEventListener(function(sender, type){
            if (type == ccui.Widget.TOUCH_ENDED) {
                mo.gameScene.pushLayer(new HallClubMemberLayer());
            }
        }, this);
    },

    onEnter : function(){
        this._super();

        this.setInfoType(this.mType);
    },

    //0加入 1退出
    setInfoType : function(type){
        if (type == 0){
            ccui.helper.seekWidgetByName(this.ccsNode, "Panel_join").setVisible(true);
            var removeName = ["Panel_member", "Panel_delMsgHistory"];
            for(var i = 0; i < removeName.length; i++){
                var index = this.ListView_content.getIndex(ccui.helper.seekWidgetByName(this.ccsNode, removeName[i]));
                this.ListView_content.removeItem(index);
            }
        } else if (type == 1){
            ccui.helper.seekWidgetByName(this.ccsNode, "Panel_exit").setVisible(true);
        }
    }
});
