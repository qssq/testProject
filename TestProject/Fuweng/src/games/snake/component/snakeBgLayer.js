/**
 * Created by gongxun on 17/3/4.
 */

var SnakeBgLayer = cc.Layer.extend({
    ctor : function(){
        this._super();

        var bgSprite = new cc.Sprite("res/snake/bgcell.png");
        var texture = bgSprite.getTexture();
        texture.setTexParameters(gl.LINEAR, gl.LINEAR, gl.REPEAT, gl.REPEAT);
        bgSprite.setTextureRect(cc.rect(0, 0, 10000, 5000));
        bgSprite.setPosition(cc.p( 0, 0));
        bgSprite.setAnchorPoint(cc.p(0, 0));
        this.addChild(bgSprite);
    },

    onEnter : function(){
        this._super();
    }
});