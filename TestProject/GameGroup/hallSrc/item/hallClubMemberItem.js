/**
 * Created by gongxun on 16/10/17.
 */

var HallClubMemberItem = GameBaseItem.extend({
    ctor : function(head, nick, lastTime){
        this._super();

        this.loadCocostudio("hallRes/ccs/HallClubMemberItem.json");
        this.setItemSize(cc.size(mo.curSize.x, 110));

        this.setItemInfo(head, nick, lastTime);
    },

    setItemInfo : function(head, nick, lastTime){
        //head
        ccui.helper.seekWidgetByName(this.ccsNode, "Image_head").loadTexture(head);

        //nick
        ccui.helper.seekWidgetByName(this.ccsNode, "Text_nick").setString(nick);

        //time
        mo.gameHelper.setTextString(ccui.helper.seekWidgetByName(this.ccsNode, "Text_lastTime"), lastTime);
    }
});