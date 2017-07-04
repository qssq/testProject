/**
 * Created by gongxun on 17/6/30.
 */

var ChessCard = cc.Sprite.extend({
    mRow : null,
    mCol : null,
    mCardNum : null,
    mKind : null,
    mFlower : null,
    ctor : function () {
        this._super();

        this.mCardNum = -1;
    },

    setCardNum : function(num){
        if (num >= 0 && num <= 6){
            this.mCardNum = num;
        }else {
            this.mCardNum = 0;
        }
    },

    //kind 0:普通 1:抬起 flower 1:红 2:黑
    setCardKind : function(kind, flower){
        this.mKind = kind;
        this.mFlower = flower;

        this.setSpriteFrame(this.getImageFileName(this.mCardNum, this.mKind, this.mFlower - 1));
    },

    getImageFileName : function(num, kind, flower){
        var result = "";
        if (kind == 0){
            result += "chess0_";
        }else {
            result += "chessSel0_";
        }

        if (flower == 0){
            result += "0_";
        }else{
            result += "1_";
        }

        result += (num + ".png");

        return result;
    }
});