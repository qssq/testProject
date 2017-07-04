/**
 * Created by gongxun on 17/7/3.
 */

var ChessTableStatus = function() {
    var that = {};

    //牌桌映像
    that.mTableStatus = null;

    //自己是否是红色
    that.myIsRed = null;
    //自己的颜色
    that.myFlower = null;

    that.init = function () {
        that.kwxAutoRobot = new KwxAutoRobot();
    };

    //设置牌桌映像
    that.setTableStatus = function (tableStatus) {
        that.mTableStatus = tableStatus;

        //1红 2黑
        that.myFlower = that.mTableStatus.mySeat == 1 ? 1 : 2;
        that.myIsRed = that.myFlower == 1;

        that.updateUI();

        that.updateTableStatus();
    };

    that.updateUI = function(){
        //游戏状态
        mo.chessTable.mChessUILayer.setStep(that.mTableStatus.step);

        //用户信息
        var userInfos = [null, null];
        for(var i = 0; i < 2; i++){
            var logicSeat = that.getLogicForView(i, that.mTableStatus.mySeat - 1);
            userInfos[i] = that.mTableStatus["seatUser" + (logicSeat + 1)];
        }
        mo.chessTable.updateUserInfos(userInfos);

        //当前该谁出牌
        if (that.mTableStatus.step == 1){
            mo.chessTable.setCurrentViewSeat(that.getViewForLogic(that.mTableStatus.nowSeat - 1, that.mTableStatus.mySeat - 1));
        }
    };

    that.updateTableStatus = function(){
        if (that.mTableStatus.step == 1){

            //更新牌桌
            mo.chessTable.mChessFlagLayer.updateChess(that.mTableStatus.qzs);
        }
    };

    that.sendAction = function(qz1, qz2){
        if (that.mTableStatus.step == 1){
            mo.gameMsgManager.sendActionCCPlay(0, qz1, qz2);
        }
    };

    that.sendActionReady = function(){
        mo.gameMsgManager.sendActionCCPlay(1, null, null);
    };

    that.getLogicForView = function(view, myLogicSeat){
        var logic = (view + 2 + myLogicSeat) % 2;
        return logic;
    };

    that.getViewForLogic = function(logic, myLogicSeat){
        var view = (logic + 2 - myLogicSeat) % 2;
        return view;
    };


    return that;
};

mo.chessTableStatus = new ChessTableStatus();