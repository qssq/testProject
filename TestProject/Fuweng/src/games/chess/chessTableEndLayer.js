/**
 * Created by gongxun on 17/7/5.
 */

var ChessTableEndLayer = GameBaseLayer.extend({
    Panel_center : null,
    ctor: function () {
        this._super();
        this.loadCocostudio("res/ccs/ChessEndLayer.json");
        mo.gameHelper.fixIosText(this.ccsNode);
        this.Panel_center = mo.seekWidgetByName(this.ccsNode, "Panel_center");

        //继续
        mo.seekWidgetByName(this.ccsNode, "Button_jixu").addTouchEventListener(function(sender, type){
            if (type == ccui.Widget.TOUCH_ENDED){
                mo.chessTableStatus.sendActionReady();
            }
        }, this);

        //返回大厅
        mo.seekWidgetByName(this.ccsNode, "Button_return").addTouchEventListener(function(sender, type){
            if (type == ccui.Widget.TOUCH_ENDED){

            }
        }, this);
    },

    setEndInfo : function(endInfo){
        this.Panel_center.stopAllActions();
        this.Panel_center.setVisible(false);
        this.Panel_center.runAction(cc.sequence(
            cc.delayTime(3.0),
            cc.show()
        ));

        if (endInfo.winSeat == 0){
            mo.gameHelper.loadTextureImage(mo.seekWidgetByName(this.ccsNode, "Image_endShow"), "res/ccs/chess/end/draw.png");
        }else{
            mo.gameHelper.loadTextureImage(mo.seekWidgetByName(this.ccsNode, "Image_endShow"),
                endInfo.winSeat == endInfo.mySeat ? "res/ccs/chess/end/win.png" : "res/ccs/chess/end/fail.png");
        }

        for (var i = 0; i < 2; i++){
            var player = mo.seekWidgetByName(this.ccsNode, "Panel_player" + i);
            var logicSeat = mo.chessTableStatus.getLogicForView(i, endInfo.mySeat - 1) + 1;
            var seatUser = endInfo["seatUser" + logicSeat];

            mo.gameHelper.setTextString(mo.seekWidgetByName(player, "Text_uid"), seatUser.uid);
        }
    }
});