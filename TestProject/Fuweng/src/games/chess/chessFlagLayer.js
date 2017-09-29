/**
 * Created by gongxun on 17/6/30.
 */

var ChessFlagLayer = GameBaseLayer.extend({
    Panel_main : null,
    chessNode : null,
    chesss : null,
    mScale : null,
    mPositionY : null,
    mSelectQz1 : null,
    mSelectQz2 : null,

    mOptionSeat : null,
    ctor : function () {
        this._super();
        this.loadCocostudio("res/ccs/ChessFlag.json");

        this.chesss = [];

        this.Panel_main = mo.seekWidgetByName(this.ccsNode, "Panel_main");

        this.chessNode = new cc.Node();
        this.Panel_main.addChild(this.chessNode);

        this.changeTableScale();


    },

    onEnter : function(){
        this._super();

        var that = this;
        cc.eventManager.addListener({
            event: cc.EventListener.TOUCH_ONE_BY_ONE,
            swallowTouches: true,
            onTouchBegan: function(touch, event){
                //不该自己出牌
                if (that.mOptionSeat != 0){
                    return false;
                }

                //抬起或者打出手牌
                var location = touch.getLocation();
                location.x = location.x / that.mScale;
                location.y = (location.y - that.mPositionY) / that.mScale;
                return that.onTouchCardBegan(location);
            },
            onTouchMoved: function(touch, event){
                // var location = touch.getLocation();
                // location.x = location.x / that.mScale;
                // location.y = (location.y - that.mPositionY) / that.mScale;
                // that.onTouchCardMoved(location);
            },
            onTouchEnded: function(touch, event){
                // var location = touch.getLocation();
                // location.x = location.x / that.mScale;
                // location.y = (location.y - that.mPositionY) / that.mScale;
                // that.onTouchCardEnded(location);
            },
            onTouchCancelled : function(touch, event){
                that.onTouchCardCancelled();
            }
        }, this);
    },

    changeTableScale : function(){
        this.mScale = mo.curSize.x / 720;
        this.Panel_main.setScale(this.mScale);

        var showHeight = 823 * this.mScale;
        this.mPositionY = (mo.curSize.y - showHeight) / 2;
        this.Panel_main.setPositionY(this.mPositionY)
    },

    addChess : function(){
        var card = new ChessCard();
        this.chessNode.addChild(card);
        this.chesss.push(card);
    },

    updateChess : function(qizis){

        //多藏少补
        var chazhi = qizis.length - this.chesss.length;
        if (chazhi > 0){
            for (var i = 0; i < chazhi; i++){
                this.addChess();
            }
        }
        for (var i = 0; i < this.chesss.length; i++){
            this.chesss[i].setVisible(i < qizis.length);
        }

        //设置坐标
        var isRed = mo.chessTableStatus.myIsRed;
        for (var i = 0; i < qizis.length; i++){
            var qizi = qizis[i];
            var card = this.chesss[i];

            card.setCardNum(qizi.num);
            card.setCardKind(0, qizi.color);
            card.mRow = qizi.row;
            card.mCol = qizi.col;

            var x = isRed ? qizi.col : 8 - qizi.col;
            var y = isRed ? qizi.row : 9 - qizi.row;

            var position = mo.chessHelper.getChessPostion(x, y);
            card.setPosition(position);
        }

        this.onSelectCard(-1, -1);
    },

    onTouchCardBegan : function(point){
        cc.log("x:" + point.x + " y:" + point.y);
        var rect = cc.rect(0, 0, 720, 823);
        if (cc.rectContainsPoint(rect, point)){
            this.onTouchCardEnded(point);
            return true;
        }else{
            this.onSelectCard(-1, -1);
            return false;
        }
    },

    onTouchCardEnded : function(point){
        var rowcol = mo.chessHelper.getRowColForPoint(point);
        if (!mo.chessTableStatus.myIsRed){
            rowcol.row = 9 - rowcol.row;
            rowcol.col = 8 - rowcol.col;
        }
        cc.log("change col:" + rowcol.col + " row:" + rowcol.row);

        this.onSelectCard(rowcol.row, rowcol.col);
    },

    onTouchCardMoved : function(point){
    },

    onTouchCardCancelled : function(){
        this.onSelectCard(-1, -1);
    },

    onSelectCard : function(row, col){
        if (row == -1 && col == -1){
            this.mSelectQz1 = null;
            this.mSelectQz2 = null;
        }

        var selectChess = null;

        for (var i = 0; i < this.chesss.length; i++){
            var chess = this.chesss[i];
            if (chess.isVisible()){
                if (chess.mRow == row && chess.mCol == col){
                    selectChess = chess;
                }
                chess.setCardKind(0, chess.mFlower);
            }
        }

        if (this.mSelectQz1 == null && selectChess != null){
            this.mSelectQz1 = selectChess;

            //不能拿起别人的手牌
            if (mo.chessTableStatus.myFlower != selectChess.mFlower){
                this.onSelectCard(-1, -1);
            }else{
                selectChess.setCardKind(1, selectChess.mFlower);
            }

        }else if (this.mSelectQz1 != null){

            //准备发送
            var qz1 = {
                row : this.mSelectQz1.mRow,
                col : this.mSelectQz1.mCol,
                color : this.mSelectQz1.mFlower,
                num : this.mSelectQz1.mCardNum
            };

            var qz2 = {
                row : row,
                col : col,
                color : this.mSelectQz1.mFlower,
                num : this.mSelectQz1.mCardNum
            };

            mo.chessTableStatus.sendAction(qz1, qz2);

            this.onSelectCard(-1, -1);
        }
    },

    //设置当前操作玩家
    setCurrentViewSeat : function(seat){
        if (seat != this.mOptionSeat){
            this.onSelectCard(-1, -1);
        }

        this.mOptionSeat = seat;
    }
});