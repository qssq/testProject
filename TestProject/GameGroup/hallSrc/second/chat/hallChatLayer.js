/**
 * Created by gongxun on 16/10/9.
 */

var HallChatLayer = GameBaseLayer.extend({
    mInputBox : null,
    mInputLastText : "",
    ListView_content : null,
    mHallChatFaceLayer : null,
    Panel_move1 : null,
    ctor: function () {
        this._super();
        this.loadCocostudio("hallRes/ccs/HallChatLayer.json");

        this.Panel_move1 = ccui.helper.seekWidgetByName(this.ccsNode, "Panel_move1");

        //childs
        this.mHallChatFaceLayer = new HallChatFaceLayer();
        this.addChild(this.mHallChatFaceLayer);

        //ui
        this.ListView_content = ccui.helper.seekWidgetByName(this.ccsNode, "ListView_content");
        this.ListView_content.setScrollBarEnabled(false);

        //关闭
        ccui.helper.seekWidgetByName(this.ccsNode, "Button_exit").addTouchEventListener(function(sender, type){
            if (type == ccui.Widget.TOUCH_ENDED) {
                this.removeFromParent();
            }
        }, this);

        //打开表情选择
        ccui.helper.seekWidgetByName(this.ccsNode, "Button_emoticons").addTouchEventListener(function(sender, type){
            if (type == ccui.Widget.TOUCH_ENDED) {
                this.openFaceLayer();
            }
        }, this);

        //输入框
        var inputP = ccui.helper.seekWidgetByName(this.ccsNode, "Image_inputBg").getPosition();
        var inputS = ccui.helper.seekWidgetByName(this.ccsNode, "Image_inputBg").getContentSize();

        this.mInputBox = new cc.EditBox(inputS, new cc.Scale9Sprite("res/Transparent.png"));
        this.mInputBox.setString("");
        this.mInputBox.setPosition(inputP);
        this.mInputBox.setReturnType(cc.KEYBOARD_RETURNTYPE_SEND);
        this.mInputBox.setInputMode(cc.EDITBOX_INPUT_MODE_SINGLELINE);
        this.mInputBox.setFontColor(cc.color(0, 0, 0));
        this.mInputBox.setFontSize(30);
        this.mInputBox.setPlaceHolder("");
        this.mInputBox.setPlaceholderFontColor(cc.color(255, 255, 255));
        this.mInputBox.setDelegate(this);
        this.Panel_move1.addChild(this.mInputBox);
    },

    onEidtBoxSend : function(text){
        if (text != "") {
            cc.log("1111111111111111111 send Text:" + text);
            this.ListView_content.pushBackCustomItem(new HallChatText(Math.random() > 0.5, text));
            this.ListView_content.jumpToBottom();

            this.mInputBox.setString("");
            this.closeFaceLayer(false);
        }
    },

    editBoxEditingDidBegin: function (editBox) {
        cc.log("editBox DidBegin !");
        this.closeFaceLayer(true);
    },

    editBoxEditingDidEnd: function (editBox) {
        cc.log("editBox  DidEnd !");
    },

    editBoxTextChanged: function (editBox, text) {
        cc.log("editBox , TextChanged, text: " + text);
    },

    editBoxReturn: function (editBox) {
        cc.log("editBox  was returned !");
        this.onEidtBoxSend(editBox.getString());
    },

    openFaceLayer : function(){
        this.mHallChatFaceLayer.openFace();

        this.Panel_move1.stopAllActions();
        this.Panel_move1.runAction(cc.sequence(cc.moveTo(0.2, cc.p(0, 300))));
    },

    closeFaceLayer : function(isQuick){
        this.mHallChatFaceLayer.closeFace(isQuick);

        this.Panel_move1.stopAllActions();
        if (isQuick){
            this.Panel_move1.setPosition(cc.p(0, 0));
        } else {
            this.Panel_move1.runAction(cc.sequence(cc.moveTo(0.2, cc.p(0, 0))));
        }
    }

});





