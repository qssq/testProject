/**
 * Created by gongxun on 17/6/30.
 */

var GameWebSocket = function(){
    var that = {};

    that.magic = "GTV1";

    that.mWebSocketClient = null;

    //是否连接上了websocket
    that.mIsConnect = false;

    //是否用户手动关闭
    that.mUesClose = false;

    that.openWebSocket = function(ip, id){
        if (that.mIsConnect){
            // mo.showRoomMsgShow("已经连接");
            return;
        }

        // var websocketip = mo.gameHelper.webSocketIpReal;
        var websocketip = ip;
        cc.log("websocket ip:" + websocketip);
        that.mWebSocketClient = new WebSocket(websocketip);
        that.mWebSocketClient.binaryType = "arraybuffer";
        that.mIsConnect = true;


        that.mWebSocketClient.onopen = function(evt) {
            cc.log("websocket onopen");
            that.mIsConnect = true;
            that.mUesClose = false;

            mo.gameMsgManager.sendLogin(id, "xg");
        };

        that.mWebSocketClient.onmessage = function(evt) {
            // cc.log("websocket onmessage");

            var binary = new Uint8Array(evt.data);
            that.recvMsg(binary);
        };

        that.mWebSocketClient.onerror = function(evt) {
            cc.log("websocket onerror");
            // mo.showRoomMsgShow("websocket onerror");

            that.onClose();
            that.mIsConnect = false;
        };

        that.mWebSocketClient.onclose = function(evt) {
            cc.log("websocket onclose");
            // mo.showRoomMsgShow("websocket onclose");

            that.onClose();
            that.mIsConnect = false;
        };
    };

    that.setClose = function(){
        if (that.mWebSocketClient && that.mIsConnect){
            that.mUesClose = true;
            that.mWebSocketClient.close();
        }
    };

    that.reconnectClose = function(){
        if (that.mWebSocketClient && that.mIsConnect){
            that.mWebSocketClient.close();
        }else{
            mo.sceneHelper.intoLoginLayer();
        }
    };

    that.onClose = function(){
        //关闭login超时检测
        // mo.mainScene.closeLoginTimeout();

        mo.eventHelper.dispatch_1("LoginResponse", false);

        if (that.mIsConnect){
            //连接上后才触发
            mo.eventHelper.dispatch("websocketclose");
        }else{

        }
        that.mWebSocketClient = null;
    };

    //发送消息 msg:protobuf
    that.sendMsg = function(binary, msgId) {
        if (that.getFrequentlyCheck(msgId)){
            cc.log("消息:" + msgId + " 间隔");
            return false;
        }

        if (that.mWebSocketClient && this.mWebSocketClient.readyState == WebSocket.OPEN){
            //4 + 4 lenght + msgid
            var protobufBinary = that.codeData(binary);

            var lenght = 2 + binary.length;
            var numArray = new Array();
            // that.getByteStringForInt2(binary.length, numArray);
            that.getByteStringForInt2(msgId, numArray);

            var arrData = new Uint8Array(lenght);
            for (var i = 0; i < 2; i++) {
                arrData[i] = numArray[i];
            }
            for (var i = 2; i < lenght; i++){
                arrData[i] = protobufBinary[i - 2];
            }

            that.mWebSocketClient.send(arrData.buffer);
            cc.log("发送消息 msgId:" + msgId + "len:" + lenght);
            return true;
        }else{
            cc.log("websocket not open");
            return false;
        }

    };

    //接受消息
    that.recvMsg = function(binary){
        //4 + 4 lenght + msgid
        var msgLenght = binary.length - 2;
        var msgId = that.getIntForBinary(binary.subarray(0, 2));
        var protobufMsg = that.codeData(binary.subarray(2));

        cc.log("收到消息 msgId:" + msgId + " msglen:" + binary.length + " protobufLen:" + protobufMsg.length);
        mo.gameMsgManager.handleMsg(protobufMsg, msgId);
    };

    //关闭websocket
    that.closeSocket = function(){
        if (that.mWebSocketClient){
            that.mWebSocketClient.close();
        }
    };

    //不加密
    that.codeData = function(binary){
        var arrData = new Uint8Array(binary.length);

        for(var i = 0; i < binary.length; i++){
            arrData[i] = binary[i];
        }
        return arrData;
    };

    that.codeData2 = function(binary){
        var arrData = new Uint8Array(binary.length);

        var keyArray = [69, 123, 132, 104, 67, 95, 33, 74, 120, 131, 61, 101, 55, 101, 69, 44];
        var lenght = keyArray.length;
        var result = "";
        for(var i = 0; i < binary.length; i++){
            var temp = binary[i] ^ keyArray[i % lenght];
            arrData[i] = temp;
        }
        return arrData;
    };

    that.getByteStringForInt4 = function(num, numArray){
        var arrData = new ArrayBuffer(4);
        var dataView = new DataView(arrData);
        dataView.setUint32(0, num);

        for (var i = 0; i < 4; i++){
            numArray.push(dataView.getUint8(i));
        }
    };

    that.getByteStringForInt2 = function(num, numArray){
        var arrData = new ArrayBuffer(2);
        var dataView = new DataView(arrData);
        dataView.setUint16(0, num);

        for (var i = 0; i < 2; i++){
            numArray.push(dataView.getUint8(i));
        }
    };

    that.getInt2ForByteString = function(str){
        var char1 = str.charCodeAt(0);
        var char2 = str.charCodeAt(1);
        return char1 * 256 + char2;
    };

    that.getIntForBinary = function(binary){
        var result = 0;
        for (var i = 0; i < binary.length; i++){
            var pow = Math.pow(256, (binary.length - i - 1));
            result += pow * binary[i];
        }
        return result;
    };

    that.getStringForBinary = function (binary) {
        var result = "";
        for (var i = 0; i < binary.length; i++){
            result += String.fromCharCode(binary[i]);
        }
        return result;
    };

    that.getStringConvertToArray = function (strData) {
        if (!strData)
            return null;

        var arrData = new Uint8Array(strData.length);
        for (var i = 0; i < strData.length; i++) {
            arrData[i] = strData.charCodeAt(i);
        }
        return arrData;
    };

    that.getFrequentlyCheck = function(msgId){
        return false;
    };

    return that;
};

mo.gameWebsocket = new GameWebSocket();