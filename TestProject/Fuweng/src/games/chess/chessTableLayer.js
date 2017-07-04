/**
 * Created by gongxun on 17/6/30.
 */

var ChessTableLayer = GameBaseLayer.extend({
    mChessFlagLayer : null,
    mChessUILayer : null,
    mCurrentViewSeat : null,
    ctor : function () {
        this._super();
        this.loadCocostudio("res/ccs/ChessTable.json");
        mo.chessTable = this;

        this.loadUI();
    },

    onEnter : function(){
        this._super();
    },

    onExit : function(){
        mo.chessTable = null;

        this._super();
    },

    loadUI : function(){
        //sprite
        cc.spriteFrameCache.addSpriteFrames("res/ccs/chess/flag/chess0.plist", "res/ccs/chess/flag/chess0.png");

        this.mChessFlagLayer = new ChessFlagLayer();
        this.addChild(this.mChessFlagLayer);

        this.mChessUILayer = new ChessUILayer();
        this.addChild(this.mChessUILayer);
        // this.mChessUILayer.setVisible(false);
    },

    updateUserInfos : function(userInfos){
        this.mChessUILayer.updateUserInfos(userInfos);
    },

    //当前操作的玩家
    setCurrentViewSeat : function(seat){
        this.mCurrentViewSeat = seat;

        this.mChessUILayer.setCurrentViewSeat(seat);

        this.mChessFlagLayer.setCurrentViewSeat(seat);
    }
});

mo.chessTable = null;