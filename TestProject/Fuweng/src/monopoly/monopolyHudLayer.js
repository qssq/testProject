/**
 * Created by gongxun on 17/2/4.
 */

var MonopolyHudLayer = GameBaseLayer.extend({
    mStartIndex : null,
    ctor : function(){
        this._super();
        this.loadCocostudio("res/ccs/HudLayer.json");
        this.mStartIndex = 0;

        mo.seekWidgetByName(this.ccsNode, "Button_go").addTouchEventListener(function(sender, type){
            if (type == ccui.Widget.TOUCH_ENDED){
                var temp = parseInt(Math.random() * 18) + 1;
                mo.monopoly.playerMove(0, this.mStartIndex, this.mStartIndex + temp, temp);
                this.mStartIndex += temp;
            }
        }, this);
    },

    setMyControl : function(myControl){
        this.setVisible(myControl);
    }
});