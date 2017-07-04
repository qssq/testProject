/**
 * Created by gongxun on 17/2/4.
 */

var PlayerLayer = cc.Layer.extend({
    mFile : null,
    mPlayerSprite : null,
    ctor : function(){
        this._super();

        this.mPlayerSprite = new cc.Sprite();
        this.mPlayerSprite.setAnchorPoint(cc.p(0, 0));
        this.addChild(this.mPlayerSprite);

        this.loadIndex(0);
    },

    loadIndex : function(index){
        if (index == 0){
            mFile = "res/role_boy_caogen.png";
        }else if (index == 1){
            mFile = "res/role_yellow_dot.png";
        }

        var texture = cc.textureCache.addImage(mFile);
        var frame = new cc.SpriteFrame(texture, cc.rect(64  * 5, 128 * 4, 64, 128));
        this.mPlayerSprite.setSpriteFrame(frame);
        this.mPlayerSprite.setPosition(mo.monopolyHelper.getIndexPos(0));
    },

    move : function(from, to, dis){
        var that = this;
        var speed = 2;
        var time = dis / speed;
        var animDelay = 0.1;
        var texture = cc.textureCache.addImage(mFile);

        that.mPlayerSprite.unscheduleAllCallbacks();
        that.mPlayerSprite.leftTime = 0;
        that.mPlayerSprite.animIndex = 0;
        that.mPlayerSprite.schedule(function (dt) {
            that.mPlayerSprite.leftTime += dt;
            if (that.mPlayerSprite.leftTime >= time){
                that.mPlayerSprite.leftTime = time;
                that.mPlayerSprite.unscheduleAllCallbacks();
            }

            //移动
            var currentIndex = from + dis * that.mPlayerSprite.leftTime / time;
            var lastIndex = parseInt(currentIndex);
            var nextIndex = Math.ceil(currentIndex);
            var offsetTemp = currentIndex - lastIndex;

            var lastPos = mo.monopolyHelper.getIndexPos(lastIndex);
            var nextPos = mo.monopolyHelper.getIndexPos(nextIndex);

            var pos = cc.p(0, 0);
            pos.x = lastPos.x + (nextPos.x - lastPos.x) * offsetTemp;
            pos.y = lastPos.y + (nextPos.y - lastPos.y) * offsetTemp;
            that.mPlayerSprite.setPosition(pos);

            //动画
            var animIndex = parseInt(that.mPlayerSprite.leftTime / animDelay) % 8;
            var framePos = that.getFramePos(lastIndex, animIndex);
            var frame = new cc.SpriteFrame(texture, cc.rect(framePos.x, framePos.y, 64, 128));
            that.mPlayerSprite.setSpriteFrame(frame);

            //结束
            if (that.mPlayerSprite.leftTime == time){
                var framePos = that.getFrameEndPos(lastIndex);
                var frame = new cc.SpriteFrame(texture, cc.rect(framePos.x, framePos.y, 64, 128));
                that.mPlayerSprite.setSpriteFrame(frame);
                mo.monopoly.playerMoveEnd();
            }
        }, 1 / 60);
    },

    getFramePos : function(lastIndex, animIndex){
        var result = cc.p(0, 0);
        var lastRealIndex = mo.monopolyHelper.getIndex(lastIndex);
        if (lastRealIndex < 11){
            result.y = 128 * 2;
        }else if (lastRealIndex < 22){
            result.y = 0;
        }else if (lastRealIndex < 33){
            result.y = 128;
        }else if (lastRealIndex < 44){
            result.y = 128 * 3;
        }

        result.x = animIndex * 64;
        return result;
    },

    getFrameEndPos : function(lastIndex){
        var result = cc.p(0, 4 * 128);
        var lastRealIndex = mo.monopolyHelper.getIndex(lastIndex);
        if (lastRealIndex < 11){
            result.x = 64 * 2;
        }else if (lastRealIndex < 22){
            result.x = 0;
        }else if (lastRealIndex < 33){
            result.x = 64;
        }else if (lastRealIndex < 44){
            result.x = 64 * 3;
        }
        return result;
    }
});