/**
 * Created by gongxun on 15/10/12.
 */


console.log("test");

var ZjhResponse =
{
    2:"packet_zjh.LoginResponse",
    4:"packet_zjh.ZJHTableStats",
    6:"packet_zjh.LogoutResponse",
    8:"packet_zjh.JoinFreeZJHResponse",
    10:"packet_zjh.ForceExitTableResponse",
    12:"packet_zjh.AlterNicknameResponse",
    14:"packet_zjh.ZJHActionResponse",
    16:"packet_zjh.CommonError",
    18:"packet_zjh.ZJHRoundEndedEvent",
    22:"packet_zjh.ZJHTableUserResult"
};


var keys = Object.keys(ZjhResponse);

console.log(Object.keys(ZjhResponse).length + "");

var temp;
for(var i in ZjhResponse){//用javascript的for/in循环遍历对象的属性
    temp = i+":"+ZjhResponse[i]+"\n";
    console.log(temp);
}