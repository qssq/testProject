/**
 * Created by gongxun on 16/10/31.
 */

var GameMsgBase = function(){
    var that = {};

    that.builder = null;

    //初始化
    that.init = function()
    {
        try
        {
            if(cc.sys.isNative)
            {
                // var protoString = jsb.fileUtils.getStringFromFile("res/baseProto.txt");
                // protoString = Base64.encode(protoString);
                // cc.log(protoString + "");
                // protoString = Base64.decode(protoString);
                var protoString = Base64.decode(protobufFile64);
                // cc.log(protoString + "");
                that.builder = protobufjs.loadProto(protoString);
            }
            else
            {
                if (mo.gameHelper.projectCode != 2){
                    that.builder = protobufjs.loadProtoFile("res/msg.txt");
                }else{
                    that.builder = protobufjs.loadProtoFile("tools/baseProto.txt");
                }
            }
        }
        catch (e)
        {
            console.log("init protobuf error");
        }
    };

    //返回msg的str
    that.getPotobufMsg = function(protobuf){
        cc.log("send:" + JSON.stringify(protobuf));

        var buffer = protobuf.encode();
        var arrData = new Uint8Array(buffer.limit);
        for (var i = 0; i < buffer.limit; i++){
            arrData[i] = buffer.view[i];
        }
        return arrData;
    };

    return that;
};
