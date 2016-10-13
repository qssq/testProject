/**
 * Created by gongxun on 16/10/11.
 */

var HallChatFaceLayer = GameBaseLayer.extend({
    ctor: function () {
        this._super();
        this.loadCocostudio("hallRes/ccs/HallChatFaceLayer.json");

        this.setVisible(false);
        this.setPosition(cc.p(0, -300));

        //关闭
        ccui.helper.seekWidgetByName(this.ccsNode, "Panel_touch").addTouchEventListener(function(sender, type){
            if (type == ccui.Widget.TOUCH_ENDED) {
                this.getParent().closeFaceLayer(false);
            }
        }, this);

        //添加表情
        for(var i = 0; i < 7; i++){
            var faceItem = ccui.helper.seekWidgetByName(this.ccsNode, "Image_face" + i);
            faceItem.setTag(i);
            faceItem.addTouchEventListener(function(sender, type){
                if (type == ccui.Widget.TOUCH_ENDED) {
                    this.inserFace(sender.getTag());
                }
            }, this);
        }

        //删除字符
        ccui.helper.seekWidgetByName(this.ccsNode, "Button_del").addTouchEventListener(function(sender, type){
            if (type == ccui.Widget.TOUCH_ENDED) {
                this.delText();
            }
        }, this);

        //发送
        ccui.helper.seekWidgetByName(this.ccsNode, "Panel_send").addTouchEventListener(function(sender, type){
            if (type == ccui.Widget.TOUCH_ENDED) {
                var text = this.getParent().mInputBox.getString();
                this.getParent().onEidtBoxSend(text);
            }
        }, this);
    },

    openFace : function(){
        this.setVisible(true);
        this.stopAllActions();
        this.runAction(cc.sequence(cc.moveTo(0.2, cc.p(0, 0))));
    },

    closeFace : function(isQuick){
        this.stopAllActions();
        if (isQuick){
            this.setPosition(cc.p(0, -300));
            this.setVisible(false);
        } else {
            this.runAction(cc.sequence(cc.moveTo(0.2, cc.p(0, -300)), cc.callFunc(function(){
                this.setVisible(false);
            }, this)));
        }
    },

    inserFace : function(index){
        var text = this.getParent().mInputBox.getString();
        var tempStr = "00" + index;
        var faceNum = tempStr.substring(tempStr.length - 2, tempStr.length);
        text += "[e" + faceNum + "]";
        this.getParent().mInputBox.setString(text);
    },

    delText : function(){
        var text = this.getParent().mInputBox.getString();

        var newText = text.substring(0, text.length - 1);
        if (text.length >= 5){
            //是删除了字符
            if (text.charAt(text.length - 1) == "]"){
                if (text.substring(text.length - 5, text.length - 3) == "[e"){
                    newText = text.substring(0, text.length - 5);
                }
            }
        }

        this.getParent().mInputBox.setString(newText);
    }
});