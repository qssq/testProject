/**
 * Created by gongxun on 17/2/4.
 */

var LoginLayer = GameBaseLayer.extend({
    TextField_ip : null,
    ctor : function(){
        this._super();
        this.loadCocostudio("res/ccs/LoginLayer.json");
        this.TextField_ip = mo.seekWidgetByName(this.ccsNode, "TextField_ip");

        mo.seekWidgetByName(this.ccsNode, "Button_login").addTouchEventListener(function(sender, type){
            if (type == ccui.Widget.TOUCH_ENDED){
                cc.log("ip:" + TextField_ip.getString());

                mo.sceneHelper.intoMainLayer();
            }
        }, this);

        this.TextField_ip.setString("192.168.0.110");
    }
});