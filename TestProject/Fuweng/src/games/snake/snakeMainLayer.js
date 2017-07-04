/**
 * Created by gongxun on 17/3/4.
 */

var SnakeMainLayer = cc.Layer.extend({
    mSnakeBgLayer : null,
    mBlocks : null,
    ctor : function(){
        this._super();

        this.loadComponent();

        this.test();
    },

    loadComponent : function(){
        this.mSnakeBgLayer = new SnakeBgLayer();
        this.addChild(this.mSnakeBgLayer);
    },

    test : function(){
        //chumo
        cc.eventManager.addListener({
            event: cc.EventListener.TOUCH_ALL_AT_ONCE,
            onTouchesBegan : function(touches, event){

                return false;
            }
        }, this);


        this.mBlocks = [];
        var head = new cc.Sprite("res/snake/skin_2_head.png");
        head.setPosition(cc.p(0, 0));
        this.addChild(head);
        this.mBlocks.push(head);

        this.scheduleUpdate();
    },

    update : function(dt){
        this._super();

        this.updateSnake(dt);
    },

    updateSnake : function(dt){
        var head = this.mBlocks[0];
        var pos = head.getPosition();
        this.setPosition(cc.p(-pos.x + mo.curSize.x / 2, -pos.y + mo.curSize.y / 2));
    }
});