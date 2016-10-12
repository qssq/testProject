/**
 * Created by gongxun on 16/10/9.
 */

var HallScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new HallMainLayer();
        this.addChild(layer);
        mo.gameScene = this;

        //this.openWebSocket();
    },

    openWebSocket : function(){

        var getJsonForStr = function(str){
            return JSON.parse(str);
        };

        var getStrForJson = function(json){
            return JSON.stringify(json);
        };

        var json = {type:"login"};
        var temp1 = getStrForJson(json);
        var temp2 = getJsonForStr(temp1);
        cc.log(temp2);

        var userId = 0;


        var that = this;
        this.mWebSocketClient = new WebSocket("ws://192.168.0.102:8080/");

        this.mWebSocketClient.onopen = function(evt) {
            cc.log("Send Text WS was opened.");

            that.mWebSocketClient.send(getStrForJson({type:"login"}));
        };

        this.mWebSocketClient.onmessage = function(evt) {
            var textStr = "response text msg: " + evt.data;
            cc.log(textStr);

            var json = getJsonForStr(evt.data);
            if (json.type == "login"){
                userId = json.content;
                cc.log("login userid:" + userId);


                that.mWebSocketClient.send(getStrForJson({type:"chatmsg", content:"测试消息"}));
            } else if (json.type == "chatmsg"){
                cc.log("chat msg content:" + json.content + "id" + json.userid);
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