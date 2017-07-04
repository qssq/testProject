/**
 * Created by gongxun on 17/6/30.
 */

var ChessUILayer = GameBaseLayer.extend({
    Panel_status : null,
    Panel_room : null,
    Panel_ready : null,

    Panel_players : null,
    ctor : function () {
        this._super();
        this.loadCocostudio("res/ccs/ChessUI.json");
        mo.gameHelper.fixIosText(this.ccsNode);

        this.Panel_status = mo.seekWidgetByName(this.ccsNode, "Panel_status");
        this.Panel_room = mo.seekWidgetByName(this.ccsNode, "Panel_room");
        this.Panel_ready = mo.seekWidgetByName(this.ccsNode, "Panel_ready");

        //登录
        mo.seekWidgetByName(this.ccsNode, "Button_login").addTouchEventListener(function(sender, type){
            if (type == ccui.Widget.TOUCH_ENDED){
                var id = mo.seekWidgetByName(this.ccsNode, "TextField_input").getString();
                mo.gameWebsocket.openWebSocket("ws://192.168.1.106:3653", id);
            }
        }, this);

        //加入房间
        mo.seekWidgetByName(this.ccsNode, "Button_join").addTouchEventListener(function(sender, type){
            if (type == ccui.Widget.TOUCH_ENDED){
                mo.gameMsgManager.sendJoinGameCC_create();
            }
        }, this);

        //准备
        mo.seekWidgetByName(this.ccsNode, "Button_start").addTouchEventListener(function(sender, type){
            if (type == ccui.Widget.TOUCH_ENDED){
                mo.chessTableStatus.sendActionReady();
            }
        }, this);

        this.Panel_players = [];
        for (var i = 0; i < 2; i++){
            var Panel_player = mo.seekWidgetByName(this.ccsNode, "Panel_player" + i);
            Panel_player.setVisible(false);
            this.Panel_players.push(Panel_player);
        }
    },

    onEnter : function(){
        this._super();

        mo.eventHelper.add("LoginResponse", this, function(isLogin){
            if (isLogin){
                this.intoUIStatus(1);
            }else{
                this.intoUIStatus(0);
            }
        });

        this.intoUIStatus(0);
    },

    onExit : function(){
        this._super();
        mo.eventHelper.remove(this);
    },

    setStep : function(step) {
        if (step == 1){
            this.intoUIStatus(3);
        }else{
            var seatUserMy = mo.chessTableStatus.mTableStatus["seatUser" + mo.chessTableStatus.mTableStatus.mySeat];
            if (seatUserMy != null){
                var isReadyMy = seatUserMy.isReady;
                if (isReadyMy){
                    this.intoUIStatus(3);
                }else{

                    this.intoUIStatus(2);
                }
            }
        }
    },

    //0未连接服务器
    //1未加入房间
    //2进入房间没有准备
    //3准备开始游戏了
    intoUIStatus : function(status){
        if (status == 0){

            this.Panel_status.setVisible(true);
            this.Panel_room.setVisible(false);
            this.Panel_ready.setVisible(false);

        }else if (status == 1){

            this.Panel_status.setVisible(false);
            this.Panel_room.setVisible(true);
            this.Panel_ready.setVisible(false);

        }else if (status == 2){

            this.Panel_status.setVisible(false);
            this.Panel_room.setVisible(false);
            this.Panel_ready.setVisible(true);

        }else if (status == 3){

            this.Panel_status.setVisible(false);
            this.Panel_room.setVisible(false);
            this.Panel_ready.setVisible(false);

        }
    },

    //更新用户信息
    updateUserInfos : function(userInfos){
        for (var i = 0; i < 2; i++){
            var user = userInfos[i];
            var playerUI = this.Panel_players[i];

            if (user != null){
                playerUI.setVisible(true);

                mo.gameHelper.setTextString(mo.seekWidgetByName(playerUI, "Text_uid"), user.uid);
            }else{
                playerUI.setVisible(false);
            }
            var Panel_player = mo.seekWidgetByName(this.ccsNode, "Panel_player" + i);
            this.Panel_players.push(Panel_player);
        }
    },

    //当前该谁操作
    setCurrentViewSeat : function(seat){

        for (var i = 0; i < 2; i++){
            var playerUI = this.Panel_players[i];

            if (seat == i){
                playerUI.setBackGroundColor(cc.color(0, 128, 0));
            }else{
                playerUI.setBackGroundColor(cc.color(77, 77, 77));
            }
        }
    }
});