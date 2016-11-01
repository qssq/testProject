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

    onEnter : function(){
        this._super();
        this.openWebSocket();
    },

    onEidtBoxSend : function(text){
        if (text != "") {
            cc.log("1111111111111111111 send Text:" + text);
            //this.ListView_content.pushBackCustomItem(new HallChatText(Math.random() > 0.5, text));
            //this.ListView_content.jumpToBottom();

            this.mWebSocketClient.send(this.getStrForJson({type:"chatmsg", content:text}));


            this.mInputBox.setString("");
            this.closeFaceLayer(false);
        }
    },

    onRecvText : function(text, isMy){
        this.ListView_content.pushBackCustomItem(new HallChatText(isMy, text));
        this.ListView_content.jumpToBottom();
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
    },

    mWebSocketClient :null,

    onExit : function(){
        if (this.mWebSocketClient){
            this.mWebSocketClient.close();
        }
        this._super();
    },

    setTopWidgetHeight : function(topWidgetHetght){
        if (topWidgetHetght) {
            var Panel_bg2 = ccui.helper.seekWidgetByName(this.ccsNode, "Panel_bg2");
            var ListView_content = ccui.helper.seekWidgetByName(this.ccsNode, "ListView_content");

            var size = cc.size(mo.curSize.x, mo.curSize.y - 100 - topWidgetHetght);
            Panel_bg2.setContentSize(size);
            ListView_content.setContentSize(size);
        }
    },

    getJsonForStr:function(str){
        return JSON.parse(str);
    },

    getStrForJson:function(json){
        return JSON.stringify(json);
    },

    openWebSocket : function(){
        var userId = 0;
        var that = this;
        this.mWebSocketClient = new WebSocket("ws://192.168.0.102:8080/");

        this.mWebSocketClient.onopen = function(evt) {
            cc.log("Send Text WS was opened.");

            that.mWebSocketClient.send(that.getStrForJson({type:"login"}));
        };

        this.mWebSocketClient.onmessage = function(evt) {
            var textStr = "response text msg: " + evt.data;
            cc.log(textStr);

            var json = that.getJsonForStr(evt.data);
            if (json.type == "login"){
                userId = json.content;
                cc.log("login userid:" + userId);
            } else if (json.type == "chatmsg"){
                cc.log("chat msg content:" + json.content + "id" + json.userid);

                that.onRecvText(json.content, json.userid == userId);
            }
        };

        this.mWebSocketClient.onerror = function(evt) {
            cc.log("_wsiSendText Error was fired");
            if (cc.sys.isObjectValid(that)) {
                cc.log("an error was fired");
            } else {
                cc.log("WebSocket test layer was destroyed!");
            }
        };

        this.mWebSocketClient.onclose = function(evt) {
            cc.log("mWebSocketClient websocket instance closed.");
        };
    }
});





