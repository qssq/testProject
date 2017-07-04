/**
 * Created by gongxun on 16/11/18.
 */

var MainScene = cc.Scene.extend({
    ctor : function(){
        this._super();
        mo.mainScene = this;

        //初始化
        mo.gameMsgManager.init();

    },

    onEnter : function() {
        this._super();
    },

    onExit : function(){
        this._super();
    }
});