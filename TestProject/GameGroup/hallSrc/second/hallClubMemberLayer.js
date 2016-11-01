/**
 * Created by gongxun on 16/10/17.
 */

var HallClubMemberLayer = GameBaseLayer.extend({
    TextField_clubName: null,
    ListView_content : null,
    ctor: function () {
        this._super();
        this.loadCocostudio("hallRes/ccs/HallClubMemberLayer.json");

        this.ListView_content = ccui.helper.seekWidgetByName(this.ccsNode, "ListView_content");
        this.ListView_content.setScrollBarEnabled(false);

        //关闭
        ccui.helper.seekWidgetByName(this.ccsNode, "Button_exit").addTouchEventListener(function (sender, type) {
            if (type == ccui.Widget.TOUCH_ENDED) {
                mo.gameScene.popLayer();
            }
        }, this);
    },

    onEnter : function(){
        this._super();

        var items = new Array();
        for(var i = 0; i < 10; i++){
            var item = {head:"hallRes/ccs/chat/common_male_head@2x.png", nick:"老王", lastTime:"1天之前"};
            items.push(item);
        }

        for(var i = 0; i < items.length; i++){
            this.ListView_content.pushBackCustomItem(new HallClubMemberItem(items[i].head, items[i].nick, items[i].lastTime));
        }
    }
});













